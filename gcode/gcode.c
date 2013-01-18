#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define GCode_G01 1
#define GCode_G02 2

void catchError(int param, int code)
{
	if(param)
	{
		printf("Error Code %d\n", code);
		exit(1);
	}
}

FILE* f;

int c=0;
int stack=0;
int command=0;
char commandL=0;
double parameter=0.0;
int q=0;
double x=0.0,y=0.0,z=0.0;
double F,S,H,I,J,K,L,P,R;
int* setFlags;
int negFlag=0;

extern void GCommands()
{
	switch(command)
	{
		case GCode_G01:
			if(setFlags[0])
				catchError(gcode_g01(setFlags, x, y, z, F), 2);
			else
				catchError(1, 2);
			break;
		case GCode_G02:
			if(setFlags[0] && setFlags[8])
				catchError(gcode_g02(setFlags, x, y, z, F, R), 2);
			else
				catchError(1, 2);
			break;
		default:
			break;
	};
	int i;
	for(i=0; i<9; i++)
		setFlags[i]=0;
}

extern void MCommands()
{
	switch(command)
	{
		case 1:
			break;
		case 2:
			break;
		default:
			break;
	};
	int i;
	for(i=0; i<9; i++)
		setFlags[i]=0;
}

extern int W()
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

extern double Q()
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

extern void T()
{
	int c=fgetc(f);
	switch(c)
	{			
		case 'F':
			F=Q();
			setFlags[0]=1;
			break;
			
		case 'S':
			S=Q();
			setFlags[1]=1;
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

extern int E()
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
			catchError(1, 1);
			break;
	};
}

extern void parse_start(FILE* ff)
{	
	setFlags=malloc(sizeof(int)*9);
	f=ff;
	E();
}
