#include<stdio.h>
#include<stdlib.h>
#include<math.h>

FILE* f;
/*Error function*/
void error()
{
	printf("Input Error!\n");
	exit(1);
}

int stack=0;
int command=0;
char commandL=0;
double parameter=0.0;
int q=0;
double x=0.0,y=0.0,z=0.0;
int negFlag=0;

void SCommand(int speed)
{
	printf("\nS=%d\n", speed);
}

void FCommand(double par)
{
	printf("\nF=%f\n", par);
}

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
}

void otherCommands(int name)
{
	switch(name)
	{
		
	};
}

/*Number-recognizing non terminal*/
int W()
{
	/*Get next token*/
	int c=fgetc(f);
	switch(c)
	{
		/*If current token is a digit or minus*/
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
			/*Returns a token to the input stream*/
			ungetc(c, f);
			return stack;
	};
}

/*Real number constr. non terminal*/
double Q()
{
	double parameter;
	parameter=W();
	if(negFlag)
		parameter*=-1;
	q=0;
	stack=0;
	/*Get next token*/
	int c=fgetc(f);
	/*If current token is dot*/
	if(c=='.')
	{
		int tmp;
		tmp=W();
		if(negFlag)
			parameter-=tmp*pow(10, -q);
		else
			parameter+=tmp*pow(10, -q);
		/*printf("%f\n", tmp*pow(10, -q));*/
		q=0;
		stack=0;
	}
	else
		/*Returns a token to the input stream*/
		ungetc(c, f);
	negFlag=0;
	return parameter;
}

/*The non terminal of the command parameters*/
void T()
{
	/*Get next token*/
	int c=fgetc(f);
	switch(c)
	{
		/*Serching command parameters in current token*/
		case 'S':
		{
			int k;
			k=W();
			SCommand(k);
			stack=0;
			q=0;
			break;
		}
		case 'F':
		{
			double num;
			num=Q();
			FCommand(num);
			break;
		}
		case 'X':
		{
			x=Q();
			switch(commandL)
			{
				case 'G':
					GCommands();
					break;
				case 'M':
					MCommands();
					break;
			};
			switch(fgetc(f))
			{
				case ' ':
					T();
					break;
				case '$':
					exit(0);
					break;
				case '\n':
					;
			};
			break;
		}
		case 'Y':
		{
			y=Q();
			switch(commandL)
			{
				case 'G':
					GCommands();
					break;
				case 'M':
					MCommands();
					break;
			};
			switch(fgetc(f))
			{
				case ' ':
					T();
					break;
				case '$':
					exit(0);
					break;
				case '\n':
					;
			};
			break;
		}
		case 'Z':
		{
			z=Q();
			switch(commandL)
			{
				case 'G':
					GCommands();
					break;
				case 'M':
					MCommands();
					break;
			};
			switch(fgetc(f))
			{
				case ' ':
					T();
					break;
				case '$':
					exit(0);
					break;
				case '\n':
					;
			};
			break;
		}
		/*If no command parameters in token*/
		default:
		{
			/*Returns a token to the input stream*/
			ungetc(c, f);
			break;
		}
	};
}

/*Starting non terminal*/
int E()
{
	int c=fgetc(f);
	switch(c)
	{
		/*Serching commands in current token*/
		case 'G':
			commandL='G';
			command=W();
			q=0;
			stack=0;
			switch(fgetc(f))
			{
				case ' ':
					T();
					break;
				case '$':
					exit(0);
					break;
				case '\n':
					;
			};
			break;
		case 'M':
			commandL='M';
			command=W();
			q=0;
			stack=0;
			switch(fgetc(f))
			{
				case ' ':
					T();
					break;
				case '$':
					exit(0);
					break;
				case '\n':
					;
			};
			break;
		/*If no commands in current token*/
		default:
			error();
			break;
	};
}

int main()
{
	/*Open input stream as file*/
	f=fopen("input", "r");
	int c=0;
	while(1)
	{
		/*Get next token*/
		c=fgetc(f);
		/*If end of stream*/
		if(c==-1 || c=='$') {
			fclose(f);
			return 0;
		}
		/*If not a new cortege*/
		if(c!='\n')
			/*Returns a token to the input stream*/
			ungetc(c, f);
		E();
	};
	return 0;
}
