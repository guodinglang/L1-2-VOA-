#include "includes.h"

rt_thread_t app_thread;  // 业务层
rt_thread_t base_thread; // 基础服务

rt_sem_t app_sem;
rt_sem_t base_sem;

const ThreadParam_S App_ThreadParam =
    {
        .name = "app",
        .entry = app_thread_entry,
        .parameter = RT_NULL,
        .stack_size = 2048,
        .priority = ThreadPri_App,
        .tick = 100,
};

const ThreadParam_S Base_ThreadParam =
    {
        .name = "base",
        .entry = base_thread_entry,
        .parameter = RT_NULL,
        .stack_size = 1024,
        .priority = ThreadPri_Base,
        .tick = 100,
};

void app_thread_entry(void *parameter)
{
  rt_tick_t ulTick;

  AppEth_Init();
  AppCmdLine_Init();
  AppDut_Init();
  AppDwin_Init();

  app_sem = rt_sem_create("app_sem", 0, RT_IPC_FLAG_FIFO);

  while (1)
  {
    if (rt_sem_take(app_sem, RT_WAITING_FOREVER) == RT_EOK)
    {
      ulTick = rt_tick_get();
      do
      {
        AppEth_Proc();

        {
          AppPort_MessageTrans();
          for (uint8_t i = 0; i < APPCMDLINE_PORTNUM; i++)
          {
            AppCmdLine_Proc((AppCmdLine_Port_E)i);
          }
        }

        AppDwin_Proc();
      } while ((rt_tick_get() - ulTick) < 5);
    }
  }
}

void base_thread_entry(void *parameter)
{
  CH9434_Init();
  AppPort_Wdt_Start();

  while (1)
  {
    BspKey_Proc();
    BspUart_Proc();
    BspBuzzer_Proc();
    CH9434_Polling();

    AppPort_Wdt_Feed();

    rt_sem_release(app_sem);

    rt_thread_delay(1);
  }
}

void AppThread_Creat(void)
{
  {
    app_thread = rt_thread_create(App_ThreadParam.name,
                                  App_ThreadParam.entry,
                                  App_ThreadParam.parameter,
                                  App_ThreadParam.stack_size,
                                  App_ThreadParam.priority,
                                  App_ThreadParam.tick);
    rt_thread_startup(app_thread);
  }
}

void AppThread_Base_Creat(void)
{
  base_thread = rt_thread_create(Base_ThreadParam.name,
                                 Base_ThreadParam.entry,
                                 Base_ThreadParam.parameter,
                                 Base_ThreadParam.stack_size,
                                 Base_ThreadParam.priority,
                                 Base_ThreadParam.tick);
  rt_thread_startup(base_thread);
}
