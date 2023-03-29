#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"

void vGarbage_box_check_task(void *pvParameters)
{
    while (1)
    {
        printf("12345\r\n");
        delay_ms(1000);
         GPIO_SetBits(GPIOA, GPIO_Pin_8); // LED0输出高
         delay_ms(1000);
         GPIO_ResetBits(GPIOA, GPIO_Pin_8); // LED0输出低
         delay_ms(1000);
    }
}
void vGarbage_box_check_task1(void *pvParameters)
{
    while (1)
    {
        printf("tianya\r\n");
        delay_ms(500);
         GPIO_SetBits(GPIOA, GPIO_Pin_8); // LED0输出高
         delay_ms(1000);
         GPIO_ResetBits(GPIOA, GPIO_Pin_8); // LED0输出低
         delay_ms(1000);
    }
}

int main(void)
{
    delay_init();                                                                  //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                                // 设置中断优先级分组2
    uart_init(9600);                                                               //串口初始化为9600
    LED_Init();                                                                    //初始化与LED连接的硬件接口
    xTaskCreate(vGarbage_box_check_task, "vGarbage_box_check_task", 310, 0, 1, 0); //垃圾盒检测任务 优先级1
    xTaskCreate(vGarbage_box_check_task1, "vGarbage_box_check_task1", 310, 0, 1, 0); //垃圾盒检测任务 优先级1
    vTaskStartScheduler();                                                         //开启任务调度

}
