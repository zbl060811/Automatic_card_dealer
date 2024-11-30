#include "ir.h"

uint32_t upcount;         // 定时器中断溢出次数
uint16_t valueup;         // 上升沿计数
uint16_t valuedown;       // 下降沿计数
uint8_t isup_flag;        // 上升沿标志
uint32_t weigh;           // 脉宽值
uint16_t buffer[128]={0};     // 数据缓冲区
uint16_t buffid;          // 缓冲区ID
uint8_t recflag;          // 接收标志

void Ir_init(void)
{
    HAL_TIM_Base_Start_IT(&htim4);
    HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_4);
}


/// @brief Period elapsed callback in non-blocking mode
/// @param htim 
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    upcount++;
}


/// @brief Input Capture callback in non-blocking mode
/// @param htim 
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(isup_flag)
    {
        isup_flag = 0;
        upcount = 0;
        valueup = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
        __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_4, TIM_ICPOLARITY_FALLING);
    }
    else 
    {
        isup_flag = 1;
        valuedown = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
        __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_4, TIM_ICPOLARITY_RISING);
        weigh = valuedown + (upcount*65536) - valueup;
        
        if(weigh>4400 && weigh<4600)    
        {
            buffid = 0;
            buffer[buffid++]=weigh;
        }     
        else if(buffid > 0)
        {
            buffer[buffid++]=weigh;
            if(buffid > 32)
            {
                recflag = 1;
                buffid = 0;
            }
        }
    }
}

