#include "ir.h" 


void Ir_init(void)
{
    HAL_TIM_Base_Start_IT(&htim4);
    HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_4);
}


