

#include "StdTypes.h"


u8 string_length(c8 *str)
{
	u8 i;
	for (i=0;str[i];i++);
	return i;
}

void string_reverse(c8 *str)
{
	u8 temp,len,i;
	
	len=string_length(str);
	for(i=0;i<=len-1;i++)
	{
		temp=str[i];
		str[i]=str[len-1];
		str[len-1]=temp;
		len--;
	}

}


void NUM_tostring(c8 *str,s32 num)
{
	u8 i,flag=0;
	s32 r;
	
	if (num==0)
	{
		str[0]='0';
		str[9]=0;
	}
	if (num<0)
	{
		num=num*(-1);
		flag=1;
	}
	for (i=0;num!=0;i++)
	{
		r=num%10;
		r=r+'0';
		str[i]=r;
		num=num/10;
	}
	if (flag==1)
	{
		str[i]='-';
		i++;
	}
	str[i]=0;
	string_reverse(str);
}
