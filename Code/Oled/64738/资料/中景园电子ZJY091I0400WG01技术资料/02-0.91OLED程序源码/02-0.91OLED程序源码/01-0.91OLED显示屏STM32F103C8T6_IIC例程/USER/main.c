//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2018-10-31
//  ����޸�   : 
//  ��������   : OLED I2C�ӿ���ʾ����(STM32F103ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND  ��Դ��
//              VCC  3.3v��Դ
//              D0   PA0��SCL��
//              D1   PA1��SDA��
//              RES  PA2��SPIģ��ĳ�IICģ����Ҫ�Ӵ����ţ�IICģ���û�����ԣ�
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2018-10-31
//All rights reserved
//******************************************************************************/
#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"

int main(void)
{
	u8 t=' ';
	delay_init();
	OLED_Init();
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
	while(1)
	{
		OLED_ShowPicture(0,0,128,32,BMP1,1);
		OLED_Refresh();
		delay_ms(500);
		OLED_Clear();
		OLED_ShowChinese(0,0,0,16,1);//��
		OLED_ShowChinese(18,0,1,16,1);//��
		OLED_ShowChinese(36,0,2,16,1);//԰
		OLED_ShowChinese(54,0,3,16,1);//��
		OLED_ShowChinese(72,0,4,16,1);//��
		OLED_ShowChinese(90,0,5,16,1);//��
		OLED_ShowChinese(108,0,6,16,1);//��
		OLED_ShowString(8,16,"ZHONGJINGYUAN",16,1);
		OLED_Refresh();
		delay_ms(500);
		OLED_Clear();
		OLED_ShowString(20,0,"2014/05/01",16,1);
		OLED_ShowString(0,16,"ASCII:",16,1);  
		OLED_ShowString(63,16,"CODE:",16,1);
		OLED_ShowChar(48,16,t,16,1);//��ʾASCII�ַ�	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,16,t,3,16,1);
		OLED_Refresh();
		delay_ms(500);
		OLED_Clear();
		OLED_ShowChinese(0,0,0,16,1); //16*16 ��
		OLED_ShowChinese(16,0,0,24,1);//24*24 ��
		OLED_ShowChinese(40,0,0,32,1);//32*32 ��
		OLED_Refresh();
	  delay_ms(500);
  	OLED_Clear();
		OLED_ShowString(0,7,"A",8,1);
		OLED_ShowString(18,4,"B",12,1);
		OLED_ShowString(36,2,"C",16,1);
		OLED_ShowString(56,0,"D",24,1);
	  OLED_Refresh();
		delay_ms(500);
		OLED_ScrollDisplay(11,4,1);
	}
}

