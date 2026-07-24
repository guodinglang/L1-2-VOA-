#include "BspConfig.h"
#include "rtthread.h"

static struct rt_mutex BspConfigList[BSPCONFIG_MUTEX_NUM];
uint32_t uLMuteRdyFlag = 0;

void default_process(void)
{
}
// 确保成对使用
void EnterCritical(void)
{
}

void ExitCritical(void)
{
}

uint8_t BspConfig_MutexCreat(char *p_caName)
{
  if (!p_caName)
    return BSPCONFIG_MUTEX_NUM;

  for (uint8_t i = 0; i < BSPCONFIG_MUTEX_NUM; i++)
  {
    if (uLMuteRdyFlag & BV(i))
      continue;

    if (rt_mutex_init(&BspConfigList[i], (const char *)p_caName, RT_IPC_FLAG_FIFO) == RT_EOK)
    {
      uLMuteRdyFlag |= BV(i);

      return i;
    }
  }

  return BSPCONFIG_MUTEX_NUM;
}

bool BspConfig_MutexTake(uint8_t ucIdx)
{
  if (ucIdx >= BSPCONFIG_MUTEX_NUM)
    return false;

  if (rt_interrupt_get_nest() == 0u && rt_thread_self() != RT_NULL)
  {
    if (uLMuteRdyFlag & BV(ucIdx))
    {
      if (rt_mutex_take(&BspConfigList[ucIdx], RT_WAITING_FOREVER) == RT_EOK)
        return true;
    }
  }

  return false;
}

bool BspConfig_MutexRelease(uint8_t ucIdx)
{
  if (ucIdx >= BSPCONFIG_MUTEX_NUM)
    return false;

  if (rt_interrupt_get_nest() == 0u && rt_thread_self() != RT_NULL)
  {
    if (uLMuteRdyFlag & BV(ucIdx))
    {
      if (rt_mutex_release(&BspConfigList[ucIdx]) == RT_EOK)
        return true;
    }
  }

  return false;
}
