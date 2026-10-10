#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t Num;

int main(void)
{
	OLED_Init();

	Timer_Init();
	
	OLED_ShowString(1, 1, "Num:");
	OLED_ShowString(2, 1, "CNT:");

	
	while (1)
	{
		OLED_ShowNum(1, 5, Num, 5);
		OLED_ShowNum(2, 5, Timer_GetCounter(), 5);
	}
}

/*void TIM2_IRQHandler(void)
{
	// 1. 确认是 TIM2 的更新中断触发了
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		// 2. 这里写你要干的事，比如翻转 LED
		Num ++;
		// 3. 清除中断标志位（必须放在任务执行完之后）
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}*/
