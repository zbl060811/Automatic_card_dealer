#include "voice.h"

battery_t battery;


/// @brief 电池测量初始化
void voice_init()
{
    HAL_ADCEx_Calibration_Start(&hadc1);			// ADC校准函数，校准ADC1
	HAL_ADC_Start_IT(&hadc1);
}


/// @brief ADC转换
/// @param battery:存储电量的结构体指针
void voice_get(battery_t *battery)
{
    if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1) , HAL_ADC_STATE_REG_EOC))	// 转换完成
    {
        battery->adc_value = HAL_ADC_GetValue(&hadc1);	// 获取ADC采样值
        battery->adc_value = lowV(battery->adc_value);
        
        battery->adc_v = 3.3 * battery->adc_value / 4096.0;
        battery->adc_v = battery->adc_v * (10.0 + 20.0) / 10.0;
        
        battery->percentage = (battery->adc_v - 6.4) / (8.4 - 6.4)*100;		// 电池容量百分比
        
        if(battery->percentage > 100)		// 限幅
            battery->percentage = 100;
        if(battery->percentage < 0)
            battery->percentage = 0;
        
        HAL_ADC_Start_IT(&hadc1);		//  中断回调函数中或主程序中要重新开启ADC中断，否则ADC不能连续工作
    }
}


/// @brief 一阶低通滤波器
/// @param com：需要滤波的adc值
/// @return ： 返回滤波后的adc值
uint16_t lowV(uint16_t com)	
{
    static unsigned int iLastData;    //上一次值
    unsigned int iData;               //本次计算值
    float dPower = 0.4;               //滤波系数
    iData = ( com * dPower ) + ( 1 - dPower ) * iLastData; //计算
    iLastData = iData;                                     //存贮本次数据
    return iData;                                         //返回数据
}