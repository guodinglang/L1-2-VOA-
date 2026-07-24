#ifndef _TIMER_WHEEL_H_
#define _TIMER_WHEEL_H_

#include <stdint.h>
#include <stdbool.h>

#define TIMER_WHEEL_OPEN 1

/**
 * @brief 时间轮槽位数
 *        32个槽位，每个槽位1ms,一圈32ms
 *        可根据实际需求调整（需为2的幂,方便取模运算）
 */
#define SLOT_NUM 32

#define TICK_MS 1

typedef void (*timer_callback_t)(void *arg);

typedef struct
{
  timer_callback_t callback; // 回调函数指针
  void *arg;                 // 回调函数参数
  uint16_t round;            // 剩余轮数
  uint16_t delay;            // 延时
  uint16_t period;           // 周期,0表示一次性任务
  uint16_t id;               // 定时器ID,用于取消
  bool active;               // 是否激活
  bool ready;                // 是否就绪
} timer_t;

/**
 * @brief 时间轮结构体
 */
typedef struct
{
  bool lock;               // 锁,防止嵌套创建定时器导致周期定时器丢失
  timer_t slots[SLOT_NUM]; // 槽位数组,每个槽位一个定时器
  uint16_t current_slot;   // 当前指针位置
  uint32_t tick_count;     // 总tick计数(用于时间统计)
  uint16_t next_id;        // 下一个可用的定时器ID
} time_wheel_t;

extern time_wheel_t tw;

void time_wheel_init(time_wheel_t *tw);                                                                            // 初始化
uint16_t add_timer(time_wheel_t *tw, uint32_t delay_ms, uint32_t period_ms, timer_callback_t callback, void *arg); // 添加定时器(池/延时/周期/回调/参数)
void time_wheel_tick_isr(time_wheel_t *tw);                                                                        // 中断回调
void time_wheel_execute(time_wheel_t *tw);                                                                         // 线程回调
bool cancel_timer(time_wheel_t *tw, uint16_t id);                                                                  // 取消定时器
uint16_t find_timer_by_callbackinfo(time_wheel_t *tw, timer_callback_t callback, void *arg);                       // 通过回调信息匹配定时器
uint32_t get_tick_count(time_wheel_t *tw);                                                                         // 获取心跳

#endif
