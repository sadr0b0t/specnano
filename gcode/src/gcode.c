#include"../inc/gcode.h"

int Error_Status=0;

void catchError(int param, int code, char* msg)
{
	if(param)
	{
		printf("Error Code %d: %s\n", code, msg);
		Error_Status = 1;
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
double F,S,H,I,J,K,L,P,R,Q,D;
int M=0;
int* setFlags;
int negFlag=0;



extern void GCommands()
{
	switch(command)
	{
		case GCode_G01:
		    if(handler_g01)
		        catchError(handler_g01(setFlags, x, y, z, F), ERROR_CODE_G01, "");
			break;
		case GCode_G02:
			if(handler_g02)
		        catchError(handler_g02(setFlags, x, y, z, F, R), ERROR_CODE_G02, "");
			break;
		case GCode_G03:
			catchError(gcode_g03(setFlags, x, y, z, F, R), ERROR_CODE_G03, "");
			break;
		case GCode_G04:
			catchError(gcode_g04(setFlags), ERROR_CODE_G04, "");
			break;
		case GCode_G15:
			catchError(gcode_g15(setFlags, x, y, z), ERROR_CODE_G15, "");
			break;
		case GCode_G16:
			catchError(gcode_g16(setFlags, x, y), ERROR_CODE_G16, "");
			break;
			
		case GCode_G17:
			catchError(gcode_g17(setFlags), ERROR_CODE_G17, "");
			break;
		case GCode_G18:
			catchError(gcode_g18(setFlags), ERROR_CODE_G18, "");
			break;
		case GCode_G19:
			catchError(gcode_g19(setFlags), ERROR_CODE_G19, "");
			break;
			
		case GCode_G40:
			catchError(gcode_g40(setFlags, x, y, z, F), ERROR_CODE_G40, "");
			break;
		case GCode_G41:
			catchError(gcode_g41(setFlags, x, y, z, F, D), ERROR_CODE_G41, "");
			break;
		case GCode_G42:
			catchError(gcode_g42(setFlags, x, y, z, F, D), ERROR_CODE_G42, "");
			break;
		case GCode_G43:
			catchError(gcode_g43(setFlags, x, y, z, F, H, S, M), ERROR_CODE_G43, "");
			break;
		case GCode_G44:
			catchError(gcode_g44(setFlags, x, y, z, F, H, S, M), ERROR_CODE_G44, "");
			break;
		case GCode_G49:
			catchError(gcode_g49(setFlags, x, y, z), ERROR_CODE_G49, "");
			break;
		case GCode_G53:
			catchError(gcode_g53(setFlags), ERROR_CODE_G53 , "");
			break;
		case GCode_G70:
			catchError(gcode_g70(setFlags), ERROR_CODE_G70 , "");
			break;
		case GCode_G71:
			catchError(gcode_g71(setFlags), ERROR_CODE_G71 , "");
			break;
		case GCode_G80:
			catchError(gcode_g80(setFlags), ERROR_CODE_G80 , "");
			break;
		case GCode_G81:
			catchError(gcode_g81(setFlags, x, y, z, F, R), ERROR_CODE_G81 , "");
			break;
		case GCode_G82:
			catchError(gcode_g82(setFlags, x, y, z, F, R, P), ERROR_CODE_G82 , "");
			break;
		case GCode_G83:
			catchError(gcode_g83(setFlags, x, y, z, F, R, Q), ERROR_CODE_G83 , "");
			break;
		case GCode_G84:
			catchError(gcode_g84(setFlags, x, y, z, F, R, M), ERROR_CODE_G84 , "");
			break;
		case GCode_G90:
			catchError(gcode_g90(setFlags, x, y, z, F), ERROR_CODE_G90 , "");
			break;
		case GCode_G91:
			catchError(gcode_g91(setFlags), ERROR_CODE_G91 , "");
			break;
		case GCode_G94:
			catchError(gcode_g94(setFlags), ERROR_CODE_G94 , "");
			break;
		case GCode_G95:
			catchError(gcode_g95(setFlags), ERROR_CODE_G95 , "");
			break;
		default:
			break;
	};
	int i;
	for(i=0; i<12; i++)
		setFlags[i]=0;
}

extern void MCommands()
{
	switch(command)
	{
		case GCode_M01:
			break;
		case GCode_M02:
			break;
		case GCode_M03:
			break;
		default:
			break;
	};
	int i;
	for(i=0; i<12; i++)
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

extern double A()
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
			F=A();
			setFlags[0]=1;
			break;
			
		case 'S':
			S=A();
			setFlags[1]=1;
			break;
			
		case 'H':
			H=A();
			setFlags[2]=1;
			break;
			
		case 'I':
			I=A();
			setFlags[3]=1;
			break;
			
		case 'J':
			J=A();
			setFlags[4]=1;
			break;
			
		case 'K':
			K=A();
			setFlags[5]=1;
			break;
			
		case 'L':
			L=A();
			setFlags[6]=1;
			break;
			
		case 'P':
			P=A();
			setFlags[7]=1;
			break;
			
		case 'R':
			R=A();
			setFlags[8]=1;
			break;
			
		case 'Q':
			Q=A();
			setFlags[9]=1;
			break;
			
		case 'D':
			D=A();
			setFlags[10]=1;
			break;
			
		case 'M':
			M=W();
			setFlags[11]=1;
			break;
			
		case 'X':
			x=A();
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
			y=A();
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
			z=A();
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
			catchError(1, 0, "Invalide command in input stream (should be started from 'G' or 'M')");
			break;
	};
	if(Error_Status)
		return 1;
	return 0;
	
}

extern int parse_start(FILE* ff)
{	
	setFlags=malloc(sizeof(int)*12);
	f=ff;
	Error_Status=0;
	int code=E();
	free(setFlags);
	if(code)
		return 0;
	else
		return 1;
}
