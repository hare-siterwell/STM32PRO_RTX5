#include "app.h"
#include "usart.h"

__NO_RETURN static void Task_Usart1(void *argument);

void app_main(void *argument) { osThreadNew(Task_Usart1, NULL, NULL); }

/* 串口1通信 */
__NO_RETURN static void Task_Usart1(void *argument) {
  printf("Task_Usart1 running!\r\n");
  usart1.sta = osSemaphoreNew(1U, 0U, NULL);

  while (1) {
    osSemaphoreAcquire(usart1.sta, osWaitForever);

    printf("%s\r\nData Length: %d\r\n", usart1.buf, usart1.len);

    UART_ReEnable(&huart1);
    osThreadYield();
  }
}
