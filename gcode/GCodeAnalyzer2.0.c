#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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
double F,S,H,I,J;
int setFlags[5];
int negFlag=0;
int c=0;

void GCommands()
{
	switch(command)
	{
		case 1:
			printf("G%d: %f %f %f\n", command, x, y, z);
			break;
		case 2:
			printf("G%d: %f %f %f\n", command, x, y, z);
			break;
		default:
			break;
	};
	for(int i=0; i<5; i++)
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
	for(int i=0; i<5; i++)
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
