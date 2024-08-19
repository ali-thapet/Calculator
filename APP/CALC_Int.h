
#ifndef CALC_INT_H_
#define CALC_INT_H_

#define  P_MAX_RANG   2147483647
#define  N_MAX_RANG  -2147483647


void CLAC_Welcome(void);
void CALC_Clear(void);
void CALC_Infinity(void);
s32 CALC_Add(s32 num1,s32 num2);
s32 CALC_Subtraction(s32 num1,s32 num2);
s32 CALC_Multiplication(s32 num1,s32 num2);
s32 CALC_Division(s32 num1,s32 num2);

#endif /* CALC_INT_H_ */