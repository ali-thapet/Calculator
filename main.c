



#include "String.h"
#include "DIO_Int.h"
#include "LCD_Int.h"
#include "KEYPAD_Int.h"
#include "CALC_Int.h"
  
#define F_CPU 8000000
#include <util/delay.h>

      /*    Codes Notes   */

 // flag1     for   Controlling clear first line or not
 // flag2     for   Multiplication Process
 // flag3     for   Addition Process
 // flag4     for   Subtraction Process
 // flag5     for   Division Process
 // flag6     to    Assign '0' in sum before insert new number
 // clearflag to    Alert that 'C' Pressed so (sum=0,garbage=0)
 // Minusflag to    Alert that '-' Pressed in first Block (the next number is negative)
 // MathFlag  to    If a math operation has done
 // NoMath    to    Alert to clear second line after hex representation
 // sp_C            counter to know times of '=' pressed
 // C=0             counter to know times of '-' pressed
 // FN              First Number
 // SN              Second Number
 // garbage         to save the result of the last operation
 // sum             to save the sum of the two numbers


/* You can do any operation with just two number */

/* Special Note: TO convert the number to write the number then press '=' twice */






s32 garbage=0;
s32 sum=0,FN=0,SN=0;      
u8 flag1=2,flag2=0,flag3=0,flag4=0,flag5=0,clearflag=0,Minusflag=0,C=0,flag6=0,SP_C=0,MathFlag=0,NoMath=0;

int main(void)
{	
 
  u8 r;
  DIO_Init();
  LCD_Init();
  KEYPAD_Init();
  CLAC_Welcome();
  while(1)
  {
	 r=KEYPAD_GetKey();
	 if(r!=NO_KEY)
	 {
		if(r>='0' && r<='9')
		{
			clearflag=0;

			if(flag1==0)
			{
				LCD_SetCursor(0,0);
				LCD_WriteString("                     ");
				LCD_SetCursor(0,0);
				flag1=2;
			}
			if(flag1==2)
			{
				   
					LCD_WriteChar(r);
					 if(flag6==1)
					 {
						 sum=0;
						 flag6=0;
					 }
					if(NoMath==1)
					{
						sum=0;
						NoMath=0;
					}
					sum=sum*10+(r-'0');
					SN=sum;
			}
	        
		 
		}
		
		 if(r=='=')
		{
			SP_C++;
			NoMath=1;
			LCD_SetCursor(1,0);
			LCD_WriteString("                     ");
			LCD_SetCursor(1,0);
			if(flag2==1)
			{
				MathFlag=1;
				NoMath=0;
				if(Minusflag==1)
				{
					if(FN==0||SN==0)
					{
						sum=0;
						LCD_WriteChar('=');
						LCD_WriteChar('0');
					}
					else
					{
						FN=(-1)*FN;
						sum=CALC_Multiplication(FN,SN);
						
					}
					 
					Minusflag=0; 
				}
				else if(Minusflag==0)
				{
					if(FN==0||SN==0)
					{
						sum=0;
						LCD_WriteChar('=');
						LCD_WriteChar('0');
					}
					else
					{
						sum=CALC_Multiplication(FN,SN);
					}
					
				}
				flag2=0;
				flag3=0;
				flag4=0;
				flag5=0;
			}
		   else if(flag3==1)
			{
				NoMath=0;
				MathFlag=1;
				if(Minusflag==1)
				{
					FN=(-1)*FN;
					sum=CALC_Add(FN,SN);
					Minusflag=0;
				}
				else if(Minusflag==0)
				{
					sum=CALC_Add(FN,SN);
				}
				flag2=0;
				flag3=0;
				flag4=0;
				flag5=0;
			}
			else if(flag4==1)
			{
				NoMath=0;
			    MathFlag=1;
				if(C%2==0)
				{   
					if(Minusflag==1)
					{
						FN=(-1)*FN;
						SN=(-1)*SN;
						sum=CALC_Add(FN,SN);
						Minusflag=0;
					}
					else if(Minusflag==0)
					{
						sum=CALC_Add(FN,SN);
					}
					
				}
				if(C%2!=0)
				{  
					if(Minusflag==1)
					{
						if(FN==SN)
						{
							sum=0;
							LCD_WriteChar('=');
							LCD_WriteChar('0');
						}
						if(FN!=SN)
						{
							if(C==1)
							{
								SN=(-1)*SN;
								sum=CALC_Add(FN,SN);
							}
							else
							{
								FN=(-1)*FN;
								sum=CALC_Add(FN,SN);
							}
							
						}
						Minusflag=0;
					}
					else if(Minusflag==0)
					{
						if(FN==SN)
						{
							sum=0;
							LCD_WriteChar('=');
							LCD_WriteChar('0');
						}
						if(FN!=SN)
						{
							sum=CALC_Subtraction(FN,SN);
						}
					}
					
					
				}
				flag2=0;
				flag3=0;
				flag4=0;
				flag5=0;
				flag6=0;
				C=0;
			}
			else if(flag5==1)
			{
				NoMath=0;
				MathFlag=1;
				if(Minusflag==1)
				{
					if(FN==0)
					{
						LCD_WriteChar('=');
						LCD_WriteChar('0');
					}
					else if(FN!=0&&SN==0)
					{
						CALC_Infinity();
						clearflag=1;
						garbage=0;
						SP_C=0;
					}
					else if(FN!=0&&SN!=0)
					{
						  SN=(-1)*SN;
						  sum=CALC_Division(FN,SN);
					}
				  
					Minusflag=0;
				}
				else if(Minusflag==0)
				{
					if(FN==0)
					{
						sum=0;
						LCD_WriteChar('=');
						LCD_WriteChar('0');
					}
					else if(FN!=0&&SN==0)
					{
						CALC_Infinity();
						clearflag=1;
						garbage=0;
						SP_C=0;
					}
					else if(FN!=0&&SN!=0)
					{
						sum=CALC_Division(FN,SN);
					}
				}
				flag2=0;
				flag3=0;
				flag4=0;
				flag5=0;		
			}
			else
			 {
				 if(NoMath==1)
				 {
					  if(SP_C==1)
					  {
						  if(sum==0&&garbage==0)
						  {
							  LCD_WriteChar('=');
							  LCD_WriteChar('0');
						  }
						  else
						  {
							  LCD_WriteChar('=');
							  LCD_WriteNumber(sum);
						  }
					  }
					  else if(SP_C==2)
					  {
						   garbage=sum;
						  LCD_WriteHex3(garbage);
						  SP_C=0;
					  }
				 }
				
			 } 
			 if(MathFlag==0)
			 {
				 garbage=sum;
			 }
			 else if(MathFlag==1)
			 {
				garbage=sum;
				sum=0;
				MathFlag=0;
			 }
			 flag1=0;
		}
		
		 if(r=='c')
		 {
			 
			 CALC_Clear();
			 clearflag=1;
			 garbage=0;
			 SP_C=0;
		 }
		
	     if(r=='*')
		{
			if(sum==0)
			{
				if(sum==0&&clearflag==0)
				{
					FN=garbage;
				}
				else if(sum==0&&clearflag==1)
				{
					FN=0;
					clearflag=0;
				}
				LCD_SetCursor(0,0);
				LCD_WriteString("                     ");
				LCD_SetCursor(0,0);
			}
		    else if(sum!=0)
			{
				FN=sum;
				flag6=1;
			}
			LCD_WriteChar('*');
			flag1=2;
			flag2=1;
			flag3=0;
			flag4=0;
			flag5=0;
		}
	
	     if(r=='+')
		 
		{
			if(sum==0)
			{
				if(sum==0&&clearflag==0)
				{
					FN=garbage;
				}
				else if(sum==0&&clearflag==1)
				{
					FN=0;
					clearflag=0;
				}
				LCD_SetCursor(0,0);
				LCD_WriteString("                     ");
				LCD_SetCursor(0,0);
				
			}
			else if(sum!=0)
			{
				FN=sum;
				flag6=1;
			}
			LCD_WriteChar('+');
			flag1=2;
			flag3=1;
			flag2=0;
			flag4=0;
			flag5=0;
			
		 }
		 
		 if(r=='-')
		 
		 {
			 if(sum==0)
			 {
				 Minusflag=1;
				 if(sum==0&&clearflag==0)
				 {
					 FN=garbage;
				 }
				 else if(sum==0&&clearflag==1)
				 {
					 FN=0;
					 clearflag=0;
				 }
				  LCD_SetCursor(0,0);
				  LCD_WriteString("                     ");
				  LCD_SetCursor(0,0);
			 }
			 else if(sum!=0)
			 {
				 FN=sum;
				 flag6=1;
			 }
				
			 LCD_WriteChar('-');
			 C++;
			 flag4=1;
			 flag1=2;
			 flag3=0; 
			 if(flag2==1)
			 {
				 Minusflag=1; 
				 flag4=0;
			 }
			 else if(flag5==1)
			 {
				 Minusflag=1; 
				 flag4=0;
			 }
			 
		 }
		 
		 if(r=='/')
		 
		 {
			 if (sum==0)
			 {
				 if(sum==0&&clearflag==0)
				 {
					 FN=garbage;
				 }
				 else if(sum==0&&clearflag==1)
				 {
					 FN=0;
					 clearflag=0;
				 } 
				 LCD_SetCursor(0,0);
				 LCD_WriteString("                     ");
				 LCD_SetCursor(0,0);
			 }
			else if(sum!=0)
			 {
				 FN=sum;
				 flag6=1;
			 }
			 LCD_WriteChar('/');
			 flag1=2;
			 flag5=1;
			 flag2=0;
			 flag3=0;
			 flag4=0;
		 }
		 
		
	 }
	   
   }
}

