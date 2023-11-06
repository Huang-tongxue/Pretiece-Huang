#ifndef _ALARM_H_
#define _ALARM_H_


#include "OLED.h"
#include "Timer.h"
#include "Buzzer.h"
#include "Encoder.h"
#include "Delay.h"
#include "Key.h"

typedef struct
{
	uint16_t Clock_Num;
	uint16_t Setting_Num;
}Alarm;

void Alarm_Init(void)
{
	OLED_Init();
	BUZZER_Init();
	Timer_Init();
	Encoder_Init();
	Key_Init();
}


//**����ʱ��




//**��ʼ����ʱ





//**������������








#endif /*_ALARM_H_*/
