#ifndef __APPTHREAD_H__
#define __APPTHREAD_H__

typedef struct
{
  char *name;
  void (*entry)(void *parameter);
  void *parameter;
  rt_uint32_t stack_size;
  rt_uint8_t priority;
  rt_uint32_t tick; // 假如有与这个线程同优先级的线程,这个线程最大的一次运行时间
} ThreadParam_S;

/*数字越小优先级越高(main线程等级默认为最大任务优先级/3,最大任务优先级在rtconfig.h中设置)*/
typedef enum
{
  ThreadPri_App = 0,
  ThreadPri_Base,
} ThreadPri_E;

void app_thread_entry(void *parameter);
void base_thread_entry(void *parameter);

void AppThread_Creat(void);
void AppThread_Base_Creat(void);

#endif /*AppThread.h*/
