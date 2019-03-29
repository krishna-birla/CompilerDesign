#include <stdio.h>
#include <stdlib.h>

void main()
{
	int a, b[10];
	b[6] = a + 1;
	for(a = 1;a < 9;a = a + 1)
	{
		b[6] = 6;
	}
	b[1] = a - 3;
	while(a == 10)
	{
		a = a + 1;
	}
	if(b[4] == a)
	{
		a = 5;
	}
	char c;
	c = '4';
	if(a == 5)
	{
		b[4] = a;
	}
	else
	{
		b[4] = 5;
	}
	switch(a)
	{
		case 1:{
			a = 6;
			break;
		}
		case 2:{
			a = 7;
			break;
		}
		default:{
			a = 7;
			break;
		}
	}
	c = a + "65";
}
