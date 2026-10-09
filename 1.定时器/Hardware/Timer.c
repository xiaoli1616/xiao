#include "stm32f10x.h"                  // Device header


void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 给 TIM2 供电（通电）
	TIM_InternalClockConfig(TIM2); //选择内部时钟源：用 RCC 提供给 TIM2 的 72MHz 作为计数时钟
	TIM_TimeBaseInitTypeDef TIM_TimBaseInitStructure;
	TIM_TimBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //输入捕获和时钟分频，这里默认就好
	TIM_TimBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //cnt计数模式，这里是向上计数
	TIM_TimBaseInitStructure.TIM_Period = 10000 - 1; //ARR 10000次 / 10000Hz = 1秒
	TIM_TimBaseInitStructure.TIM_Prescaler = 7200 - 1; //PSC 72MHz / 7200 = 10000Hz
	TIM_TimBaseInitStructure.TIM_RepetitionCounter =0; //这个是重复计数器，高级计时器才有的，这里不需要，给0
	TIM_TimeBaseInit(TIM2, &TIM_TimBaseInitStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update); // 清除 TIM2 的更新事件标志位（硬件状态）
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  // 允许 TIM2 的更新中断（CNT 数满 ARR 归零时，产生中断信号）

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
// 【全局只调一次】配置 NVIC 优先级分组：2位抢占，2位响应
// 含义：抢占优先级可取 0~3，响应优先级可取 0~3
// 规则：数值越小，优先级越高
// 注意：整个工程只能调用一次，后续所有中断都按这个规则分配优先级
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; // 指定中断通道：TIM2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // 使能该通道：允许 TIM2 打断 CPU
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // 抢占优先级 = 2（数值越小，优先级越高；此处范围 0~3）
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; // 响应优先级 = 1（仅抢占相同时比先后；范围 0~3）
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
// 启动定时器 TIM2：让计数器 CNT 真正开始数数
// 不写这一句，前面 PSC、ARR 配得再完美，CNT 也只会躺着不动
}

	//void TIM2_IRQHandler(void)
	//{
	//	// 1. 确认是 TIM2 的更新中断触发了
	//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	//	{
	//		// 2. 这里写你要干的事，比如翻转 LED
	//		Num ++;
	//		// 3. 清除中断标志位（必须放在任务执行完之后）
	//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	//	}
	//}
		

		
		
		