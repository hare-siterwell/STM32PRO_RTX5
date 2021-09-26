#ifndef __DELAY_H
#define __DELAY_H

#include "sys.h"

#if SYSTEM_SUPPORT_OS
#include "cmsis_os2.h" // 支持RTX5
#else
void delay_init(u8 SYSCLK);
#endif

void delay_us(u32 nus);
void delay_ms(u32 nms);

#endif /* __DELAY_H */
