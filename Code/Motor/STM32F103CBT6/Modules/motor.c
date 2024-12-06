#include "motor.h"


/// @brief 电机初始化
/// @param  
void motor_init(void)
{
    SEND_CTRL(1);
    PTZ_CTRL(1);

}
