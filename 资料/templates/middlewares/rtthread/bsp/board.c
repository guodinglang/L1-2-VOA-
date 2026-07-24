/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-24                  the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "includes.h"

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
/*
 * Please modify RT_HEAP_SIZE if you enable RT_USING_HEAP
 * the RT_HEAP_SIZE max value = (sram size - ZI size), 1024 means 1024 bytes
 */

#define SRAM1_SIZE 96
#define SRAM1_START (0x20000000)
#define SRAM1_END (SRAM1_START + SRAM1_SIZE * 1024) // 结束地址 = 0x20000000(基址)+ (RAM大小)

#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern int Image$$RW_IRAM1$$ZI$$Limit; // RW_IRAM1，需与链接脚本中运行时域名相对应
#define HEAP_BEGIN ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#endif

#define HEAP_END SRAM1_END

#endif

/**
 * This function will initial your board.
 */
void rt_hw_board_init(void)
{
  system_clock_config();

  BspBoard_Init();

  /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
  rt_components_board_init();
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
  rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif
}

#ifdef RT_USING_CONSOLE

static uint8_t ucUartBlock = 0;
static bool bEnable = true;

void rt_hw_console_SetBlockMode(rt_uint8_t ucState)
{
  ucUartBlock = ucState;
}

void rt_hw_console_enable(bool bNewState)
{
  bEnable = bNewState;
}

static int uart_init(void)
{
  return 1;
}
INIT_BOARD_EXPORT(uart_init);

void rt_hw_console_output(const char *str)
{
}

char rt_hw_console_getchar(void)
{
  return -1;
}

#endif
