#include "timer_wheel.h"
#include <string.h>

time_wheel_t tw;

void time_wheel_init(time_wheel_t *tw)
{
  memset(tw->slots, 0, sizeof(tw->slots));
  tw->current_slot = 0;
  tw->tick_count = 0;
  tw->next_id = 1; // ID从1开始,0表示无效
}

static inline timer_t *calc_slot(time_wheel_t *tw, uint16_t *p_slot, uint32_t delay_ms, uint16_t *p_round)
{
  timer_t *t = NULL;
  uint16_t current_slot;

  if (p_slot)
  {
    current_slot = *p_slot;
  }
  else
  {
    current_slot = tw->current_slot;
  }

  /**
   * @brief 计算槽位和轮数
   *
   * 公式：slot = (current_slot + delay) % SLOT_NUM
   *       round = delay / SLOT_NUM
   *
   * 示例：current_slot=0, delay=20ms (SLOT_NUM=16)
   *       slot = (0 + 20) % 16 = 4
   *       round = 20 / 16 = 1
   *       表示：指针走完一圈（16ms）再走4个槽位后执行
   *       实际延迟 = 1*16 + 4 = 20ms ?
   */
  uint16_t slot = (current_slot + delay_ms) % SLOT_NUM;
  uint16_t round = delay_ms / SLOT_NUM;

  /**
   * @brief 修正边界情况
   *
   * 当delay是SLOT_NUM的整数倍时（如16、32...）
   * 计算出的slot = current_slot，round = delay/SLOT_NUM
   *
   * 例如：delay=16, current_slot=0
   *       slot = 0, round = 1
   *       需要等1圈（16ms）后执行 ?
   */
  if (round == 0 && slot == current_slot)
  {
    round = 1; // 防止任务在当前tick立即执行
  }

  /**
   * @brief 线性探测找空闲槽位
   *
   * 如果目标槽位被占用，尝试下一个槽位
   * 最多找一圈，找不到则返回失败
   *
   * 这是简化的冲突处理策略，适合任务数远小于槽位数的情况
   */
  for (int i = 0; i < SLOT_NUM; i++)
  {
    uint16_t check_slot = (slot + i) % SLOT_NUM;
    if (!tw->slots[check_slot].active)
    {
      t = &tw->slots[check_slot];
      break;
    }
  }

  *p_round = round;

  return t;
}

uint16_t add_timer(time_wheel_t *tw, uint32_t delay_ms, uint32_t period_ms,
                   timer_callback_t callback, void *arg)
{
  uint16_t round;

  if (callback == NULL)
    return 0;

  if (!delay_ms)
  {
    callback(arg); // 就地执行
    return 0;
  }

  if (tw->lock == true)
    return 0; // not today!

  timer_t *t = calc_slot(tw, 0, delay_ms, &round);

  if (t == NULL)
    return 0; // 无空闲槽位

  t->id = tw->next_id++;           // 分配唯一ID
  t->round = round;                // 剩余轮数
  t->delay = (uint16_t)delay_ms;   // 延时(ms)
  t->period = (uint16_t)period_ms; // 周期(ms)
  t->callback = callback;          // 回调函数
  t->arg = arg;                    // 回调参数
  t->active = true;                // 标记为激活
  t->ready = false;                // 标记为未就绪

  return t->id;
}

void time_wheel_tick_isr(time_wheel_t *tw)
{
#if (TIMER_WHEEL_OPEN == 1)
  uint16_t slot = tw->current_slot; // 当前槽位
  timer_t *t = &tw->slots[slot];    // 当前槽位的定时器

  if (t->active)
  {
    if (t->round > 0)
    {
      t->round--;
    }
    else
    {
      t->ready = true;
    }
  }
#else
  for (uint8_t i = 0; i < SLOT_NUM; i++)
  {
    if (tw->slots[i].active == false)
      continue;

    if (tw->slots[i].delay > 0)
    {
      tw->slots[i].delay--;
    }
    else
    {
      tw->slots[i].ready = true;
    }
  }
#endif

  tw->current_slot = (tw->current_slot + 1) % SLOT_NUM;
  tw->tick_count++;
}

void time_wheel_execute(time_wheel_t *tw)
{
  uint16_t round, delay;
  uint32_t tick_lost;
  tw->lock = true;

  for (int i = 0; i < SLOT_NUM; i++)
  {
    if (tw->slots[i].ready == false)
      continue;
    if (tw->slots[i].active == false)
      continue;
    if (!tw->slots[i].callback)
      continue;

    tick_lost = tw->tick_count;

    tw->slots[i].callback(tw->slots[i].arg);

    tw->slots[i].active = false;
    tw->slots[i].ready = false;

    if (tw->slots[i].period)
    {
      tick_lost = tw->tick_count - tick_lost;

      if (tw->slots[i].period >= tick_lost)
      {
        delay = tw->slots[i].period - tick_lost;
      }
      else
      {
        delay = 0;
      }

      timer_t *t = calc_slot(tw, 0, delay, &round);

      if (t)
      {
        t->id = tw->slots[i].id;             // 继承ID
        t->round = round;                    // 剩余轮数
        t->delay = delay;                    // 延时(ms)
        t->period = tw->slots[i].period;     // 周期(ms)
        t->callback = tw->slots[i].callback; // 回调函数
        t->arg = tw->slots[i].arg;           // 回调参数
        t->active = true;                    // 标记为激活
        t->ready = false;                    // 标记为未就绪
      }
    }
  }

  tw->lock = false;
}

bool cancel_timer(time_wheel_t *tw, uint16_t id)
{
  for (int i = 0; i < SLOT_NUM; i++)
  {
    if (tw->slots[i].active == false)
      continue;

    if (tw->slots[i].id == id)
    {
      tw->slots[i].active = false;
      return true;
    }
  }
  return false;
}

uint16_t find_timer_by_callbackinfo(time_wheel_t *tw, timer_callback_t callback, void *arg)
{
  for (int i = 0; i < SLOT_NUM; i++)
  {
    if (tw->slots[i].active == false)
      continue;

    if ((tw->slots[i].callback == callback) && (tw->slots[i].arg == arg))
    {
      return tw->slots[i].id;
    }
  }

  return 0;
}

uint32_t get_tick_count(time_wheel_t *tw)
{
  return tw->tick_count;
}
