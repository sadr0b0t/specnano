#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"G_commands.h"
#include"M_commands.h"

#define GCode_G01 1
#define GCode_G02 2

FILE* f;

void error(int code)
{
	printf("Input Error!%d\n", code);
	exit(1);
}

int stack=0;
int command=0;
char commandL=0;
double parameter=0.0;
int q=0;
double x=0.0,y=0.0,z=0.0;
double F,S,H,I,J,K,L,P,R;
int setFlags[9];
int negFlag=0;
int c=0;

void GCommands()
{
	switch(command)
	{
		case GCode_G01:
			if(setFlags[0])
				gcode_g01(x, y, z, F);
			else
				error(2);
			break;
		case GCode_G02:
			if(setFlags[0] && setFlags[8])
				gcode_g02(x, y, z, F, R);
			else
				error(2);
			break;
		default:
			break;
	};
	int i;
	for(i=0; i<9; i++)
		setFlags[i]=0;
}

void MCommands()
{
	switch(command)
	{
		case 1:
			printf("M%d\n", command);
			break;
		case 2:
			printf("M%d\n", command);
			break;
		default:
			break;
	};
	int i;
	for(i=0; i<9; i++)
		setFlags[i]=0;
}

int W()
{
	int c=fgetc(f);
	switch(c)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			stack*=10;
			stack+=c-48;
			q++;
			W();
			break;
		case '-':
			negFlag=1;
			W();
			break;
		default:
			ungetc(c, f);
			return stack;
	};
}

double Q()
{
	double parameter;
	parameter=W();
	if(negFlag)
		parameter*=-1;
	q=0;
	stack=0;
	c=fgetc(f);
	if(c=='.')
	{
		int tmp;
		tmp=W();
		if(negFlag)
			parameter-=tmp*pow(10, -q);
		else
			parameter+=tmp*pow(10, -q);
		q=0;
		stack=0;
	}
	else
		ungetc(c, f);
	negFlag=0;
	return parameter;
}

void T()
{
	int c=fgetc(f);
	switch(c)
	{
		case 'S':
			S=Q();
			setFlags[1]=1;
			break;
			
		case 'F':
			F=Q();
			setFlags[0]=1;
			break;
			
		case 'H':
			H=Q();
			setFlags[2]=1;
			break;
			
		case 'I':
			I=Q();
			setFlags[3]=1;
			break;
			
		case 'J':
			J=Q();
			setFlags[4]=1;
			break;
			
		case 'K':
			K=Q();
			setFlags[5]=1;
			break;
			
		case 'L':
			L=Q();
			setFlags[6]=1;
			break;
			
		case 'P':
			P=Q();
			setFlags[7]=1;
			break;
			
		case 'R':
			R=Q();
			setFlags[8]=1;
			break;
			
		case 'X':
			x=Q();
			switch(fgetc(f))
			{
				case ' ':
					T();
					break;
				default:
					ungetc(c, f);
					break;
			};
			break;
			
		case 'Y':
			y=Q();
			switch(fgetc(f))
			{
				case ' ':
					T();
					break;
				default:
					ungetc(c, f);
					break;
			};
			break;
			
		case 'Z':
			z=Q();
			switch(fgetc(f))
			{
				case ' ':
					T();
					break;
				default:
					ungetc(c, f);
					break;
			};
			break;
			
		default:
			ungetc(c, f);
			break;
	};
}

int E()
{
	c=fgetc(f);
	switch(c)
	{
		case 'G':
		case 'M':
			commandL=c;
			command=W();
			q=0;
			stack=0;
			switch(fgetc(f))
			{
				case ' ':
					T();
					if(commandL=='G')
						GCommands();
					else
						MCommands();
					break;
				default:
					ungetc(c, f);
					break;
			};
			break;
		default:
			error(1);
			break;
	};
}

int main()
{
	f=fopen("input", "r");
	while(1)
	{
		do
		{
			c=fgetc(f);
		}
		while(c=='\n');
		if(c==-1)
			return 0;
		ungetc(c, f);
		E();
	};
	return 0;
}
