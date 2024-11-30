#ifndef __IR_H__
#define __IR_H__

#include "tim.h"

extern uint32_t upcount;         // 定时器中断溢出次数
extern uint16_t valueup;         // 上升沿计数
extern uint16_t valuedown;       // 下降沿计数
extern uint8_t isup_flag;        // 上升沿标志
extern uint32_t weigh;           // 脉宽值
extern uint16_t buffer[128];     // 数据缓冲区
extern uint16_t buffid;          // 缓冲区ID
extern uint8_t recflag;          // 接收标志


void Ir_init(void);

#endif
