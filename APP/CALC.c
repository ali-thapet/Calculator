
#define F_CPU 8000000
#include <util/delay.h>

#include "DIO_Int.h"
#include "LCD_Int.h"
#include "CALC_Int.h"
#include "KEYPAD_Int.h"



void CLAC_Welcome(void)
{
	s32 Max_P = P_MAX_RANG;
	s32 Max_N = N_MAX_RANG;
	LCD_SetCursor(0,0);
	LCD_WriteString("WELCOME TO ");
	LCD_SetCursor(1,0);
	LCD_WriteString("ALI's CALCLATOR ");
	_delay_ms(1000);
	LCD_Clear();
	LCD_WriteString("MAX POS RANG");
	_delay_ms(1000);
	LCD_Clear();
	LCD_WriteString(" = ");
	LCD_WriteNumber(Max_P);
	_delay_ms(1000);
	LCD_Clear();
	LCD_WriteString("MAX NEG RANG");
	_delay_ms(1000);
	LCD_Clear();
	LCD_WriteString(" = ");
	LCD_WriteNumber(Max_N);
	_delay_ms(1000);
	LCD_Clear();
}
void CALC_Clear(void)
{
	LCD_Clear();
}

void CALC_Infinity(void)
{
	LCD_WriteString(" infinity  ? ");
	_delay_ms(500);
	LCD_Clear();
}

s32 CALC_Add(s32 num1,s32 num2)
{
	s32 sum;
	sum=num1+num2;
	LCD_WriteChar('=');
	LCD_WriteNumber(sum);
	return sum;
}

s32 CALC_Subtraction(s32 num1,s32 num2)
{
	s32 sum;
	sum=num1-num2;
	LCD_WriteChar('=');
	LCD_WriteNumber(sum);
	return sum;
}

s32 CALC_Multiplication(s32 num1,s32 num2)
{
	s32 sum;
	sum=num1*num2;
	LCD_WriteChar('=');
	LCD_WriteNumber(sum);
	return sum;
}
s32 CALC_Division(s32 num1,s32 num2)
{
	s32 sum;
	sum=num1/num2;
	LCD_WriteChar('=');
	LCD_WriteNumber(sum);
	return sum;
}
