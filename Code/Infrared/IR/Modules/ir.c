#include "ir.h"

ir_t ir;        // 创建红外结构体对象

/// @brief 红外通信初始化
/// @param  
void Ir_init(void)
{
    HAL_TIM_Base_Start_IT(&htim4);
    HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_4);
}

/// @brief 红外接收信号转换
/// @param num 
void ir_rece(char num[])
{
    for (int i = 0; i < 32;i++)
    {
        if(ir.buffer[i]<1200)
        {
            num[i / 8] = num[i / 8] << 1;
        }
        else
        {
            num[i / 8] = num[i / 8] << 1;
            num[i / 8] |= 0x01;
        }
    }
}


/// @brief Period elapsed callback in non-blocking mode
/// @param htim 
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    ir.upcount++;
}


/// @brief Input Capture callback in non-blocking mode
/// @param htim 
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(ir.isup_flag)
    {
        ir.isup_flag = 0;
        ir.upcount = 0;
        ir.valueup = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
        __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_4, TIM_ICPOLARITY_FALLING);
    }
    else 
    {
        ir.isup_flag = 1;
        ir.valuedown = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
        __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_4, TIM_ICPOLARITY_RISING);
        ir.weigh = ir.valuedown + (ir.upcount*65536) - ir.valueup;
        
        if(ir.weigh>4400 && ir.weigh<4600)    
        {
            ir.buffid = 0;
            ir.buffer[ir.buffid++]=ir.weigh;
        }     
        else if(ir.buffid > 0)
        {
            ir.buffer[ir.buffid++]=ir.weigh;
            if(ir.buffid > 32)
            {
                ir.recflag = 1;
                ir.buffid = 0;
            }
        }
    }
}

