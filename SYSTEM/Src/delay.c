/**
 * @file delay.c
 * @brief Manage delays
 */
#include "delay.h"

#if SYSTEM_SUPPORT_OS // 如果支持OS
u32 HAL_GetTick(void) {
  static u32 ticks = 0U;
  if (osKernelGetState() == osKernelRunning)
    return osKernelGetTickCount();
  /* 如果RTX5没有运行,采用以下方式 */
  for (u32 i = (SystemCoreClock >> 14U); i > 0U; i--) {
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
  }
  return ++ticks;
}
#else
static u32 fac_us = 0; // us延时倍乘数

/**
 * @brief 初始化延时函数
 * @param SYSCLK 系统时钟频率
 */
void delay_init(u8 SYSCLK) {
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK); // SysTick频率为HCLK
  fac_us = SYSCLK;
}
#endif

/**
 * @brief 延时nus
 * @param nus 需要延时的us数
 */
void delay_us(u32 nus) {
#if SYSTEM_SUPPORT_OS
  uc32 timeout = osKernelGetSysTimerFreq() / 1000000U * nus;
  u32 tcnt, told = osKernelGetSysTimerCount(); // 计数器值
  do {
    tcnt = osKernelGetSysTimerCount();
    tcnt = (tcnt > told) ? (tcnt - told) : (UINT32_MAX - told + tcnt); // 防溢出
  } while (tcnt < timeout);
#else
  u32 tnow, tcnt = 0;
  u32 reload = SysTick->LOAD; // LOAD的值
  u32 ticks = nus * fac_us;   // 需要的节拍数
  u32 told = SysTick->VAL;    // 刚进入时的计数器值
  while (1) {
    tnow = SysTick->VAL;
    if (tnow != told) {
      if (tnow < told) {
        tcnt += told - tnow; // SYSTICK是一个递减的计数器
      } else {
        tcnt += reload - tnow + told;
      }
      told = tnow;
      if (tcnt >= ticks)
        break; // 时间超过或等于要延迟的时间则退出
    }
  }
#endif
}

/**
 * @brief 延时nms
 * @param nus 需要延时的ms数
 */
void delay_ms(u32 nms) {
#if SYSTEM_SUPPORT_OS
  osDelay(nms);
#else
  for (u32 i = 0; i < nms; i++) {
    delay_us(1000);
  }
#endif
}
