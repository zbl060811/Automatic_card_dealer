#ifndef __MOTOR_H__
#define __MOTOR_H__ 


#include "gpio.h"


/* 云台电机驱动引脚 */
#define WASH_GPIO_PROT              GPIOB
#define WASH_GPIO_PIN               GPIO_PIN_12
#define WASH_CTRL(x)                HAL_GPIO_WritePin(WASH_GPIO_PROT, WASH_GPIO_PIN, (GPIO_PinState)(x))

/* 发牌电机驱动引脚 */
#define SEND_GPIO_PROT              GPIOB
#define SEND_GPIO_PIN               GPIO_PIN_12
#define SEND_CTRL(x)                HAL_GPIO_WritePin(SEND_GPIO_PROT, SEND_GPIO_PIN, (GPIO_PinState)(x))

/* 云台电机驱动引脚 */
#define PTZ_GPIO_PROT               GPIOA
#define PTZ_GPIO_PIN                GPIO_PIN_12
#define PTZ_CTRL(x)                 HAL_GPIO_WritePin(PTZ_GPIO_PROT, PTZ_GPIO_PIN, (GPIO_PinState)(x))



// 洗牌电机
#define WASH_MOTOR_GPIO_PROT        GPIOA
#define WASH_MOTOR_GPIO_PIN         GPIO_PIN_5|GPIO_PIN_11

// 发牌电机
#define SEND_MOTOR_GPIO_PROT        GPIOB
#define SEND_MOTOR_BI1_GPIO_PIN     GPIO_PIN_1
#define SEND_MOTOR_FI1_GPIO_PIN     GPIO_PIN_0

// 腰盘电机
#define PTZ_MOTOR_GPIO_PROT         GPIOB
#define PTZ_MOTOR_BI2_GPIO_PIN      GPIO_PIN_13
#define PTZ_MOTOR_FI2_GPIO_PIN      GPIO_PIN_14



void motor_init(void);

#endif
