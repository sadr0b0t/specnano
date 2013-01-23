#include<stdio.h>

int* flags;

int flags_calc(int q)
{
	int i;
	int summ=0;
	for(i=0; i<12; i++)
		if(flags[i])
			summ+=1;
	if(summ==q)
		return 1;
	return 0;
}

extern int gcode_g01(int* _f, double x, double y, double z, double f)
{
	flags=_f;
	if(!(flags[0] && flags_calc(1)))
		return 1;	
	printf("G01: X%f Y%f Z%f F%f\n", x, y, z, f);
	return 0;
}

extern int gcode_g02(int* _f, double x, double y, double z, double f, double r)
{
	flags=_f;
	if(!(flags[0] && flags[8] && flags_calc(2)))
		return 1;
	printf("G02: X%f Y%f Z%f R%f F%f\n", x, y, z, r, f);
	return 0;
}

extern int gcode_g03(int* _f, double x, double y, double z, double f, double r)
{
	flags=_f;
	if(!(flags[0] && flags[8] && flags_calc(2)))
		return 1;
	printf("G03: X%f Y%f Z%f R%f F%f\n", x, y, z, r, f);
	return 0;
}

extern int gcode_g04(int* _f)
{
	flags=_f;
	if(!(flags_calc(0)))
		return 1;
	printf("G04\n");
	return 0;
}

extern int gcode_g15(int* _f, double x, double y, double z)
{
	flags=_f;
	if(!(flags_calc(0)))
		return 1;
	printf("G15: X%f Y%f Z%f\n", x, y, z);
	return 0;
}

extern int gcode_g16(int* _f, double x, double y)
{
	flags=_f;
	if(!(flags_calc(0)))
		return 1;
	printf("G16: r%f phi%f\n", x, y);
	return 0;
}

extern int gcode_g17(int* _f)
{
	flags=_f;
	if(!(flags_calc(0)))
		return 1;
	printf("G17\n");
	return 0;
}

extern int gcode_g18(int* _f)
{
	flags=_f;
	if(!(flags_calc(0)))
		return 1;
	printf("G18\n");
	return 0;
}

extern int gcode_g19(int* _f)
{
	flags=_f;
	if(!(flags_calc(0)))
		return 1;
	printf("G19\n");
	return 0;
}

extern int gcode_g40(int* _f, double x, double y, double z, double f)
{
	flags=_f;
	if(!(flags[0] && flags_calc(1)))
		return 1;
	printf("G40: X%f Y%f Z%f F%f\n", x, y, z, f);
	return 0;
}

extern int gcode_g41(int* _f, double x, double y, double z, double f, double d)
{
	flags=_f;
	if(!(flags[0] && flags[10] && flags_calc(2)))
		return 1;
	printf("G41: X%f Y%f Z%f D%f F%f\n", x, y, z, d, f);
	return 0;
}

extern int gcode_g42(int* _f, double x, double y, double z, double f, double d)
{
	flags=_f;
	if(!(flags[0] && flags[10] && flags_calc(2)))
		return 1;
	printf("G42: X%f Y%f Z%f D%f F%f\n", x, y, z, d, f);
	return 0;
}

extern int gcode_g43(int* _f, double x, double y, double z, double f, double h, double s, int m)
{
	flags=_f;
	if(!(flags[0] && flags[2] && flags[1] && flags[11] && flags_calc(4)))
		return 1;
	printf("G43: X%f Y%f Z%f H%f S%f F%f M%d\n", x, y, z, h, s, f, m);
	return 0;
}

extern int gcode_g44(int* _f, double x, double y, double z, double f, double h, double s, int m)
{
	flags=_f;
	if(!(flags[0] && flags[2] && flags[1] && flags[11] && flags_calc(4)))
		return 1;
	printf("G44: X%f Y%f Z%f H%f S%f F%f M%d\n", x, y, z, h, s, f, m);
	return 0;
}

extern int gcode_g49(int* _f, double x, double y, double z)
{
	flags=_f;
	if(!(flags_calc(0)))
		return 1;
	printf("G49: X%f Y%f Z%f\n", x, y, z);
	return 0;
}

extern int gcode_g53(int* _f)
{
	flags=_f;
	if(!(flags_calc(0)))
		return 1;
	printf("G53");
	return 0;
}

extern int gcode_g70(int* _f)
{
	flags=_f;
	if(!(flags_calc(0)))
		return 1;
	printf("G70");
	return 0;
}

extern int gcode_g71(int* _f)
{
	flags=_f;
	if(!(flags_calc(0)))
		return 1;
	printf("G71");
	return 0;
}

extern int gcode_g80(int* _f)
{
	flags=_f;
	if(!(flags_calc(0)))
		return 1;
	printf("G80");
	return 0;
}

extern int gcode_g81(int* _f, double x, double y, double z, double f, double r)
{
	flags=_f;
	if(!(flags[0] && flags[8] && flags_calc(2)))
		return 1;
	printf("G81: X%f Y%f Z%f R%f F%f\n", x, y, z, r, f);
	return 0;
}

extern int gcode_g82(int* _f, double x, double y, double z, double f, double r, double p)
{
	flags=_f;
	if(!(flags[0] && flags[8] && flags[7] && flags_calc(3)))
		return 1;
	printf("G82: X%f Y%f Z%f R%f P%f F%f\n", x, y, z, r, p, f);
	return 0;
}

extern int gcode_g83(int* _f, double x, double y, double z, double f, double r, double q)
{
	flags=_f;
	if(!(flags[0] && flags[8] && flags[7] && flags_calc(3)))
		return 1;
	printf("G83: X%f Y%f Z%f R%f Q%f F%f\n", x, y, z, r, q, f);
	return 0;
}

extern int gcode_g84(int* _f, double x, double y, double z, double f, double r, int m)
{
	flags=_f;
	if(!(flags[0] && flags[8] && flags[7] && flags_calc(3)))
		return 1;
	printf("G84: X%f Y%f Z%f R%f F%f M%d\n", x, y, z, r, f, m);
	return 0;
}

extern int gcode_g90(int* _f, double x, double y, double z, double f)
{
	flags=_f;
	if(!(flags[0] && flags_calc(1)))
		return 1;
	printf("G90: X%f Y%f Z%f F%f\n", x, y, z, f);
	return 0;
}

extern int gcode_g91(int* _f)
{
	flags=_f;
	if(!(flags_calc(0)))
		return 1;
	printf("G91");
	return 0;
}

extern int gcode_g94(int* _f)
{
	flags=_f;
	if(!(flags_calc(0)))
		return 1;
	printf("G94");
	return 0;
}

extern int gcode_g95(int* _f)
{
	flags=_f;
	if(!(flags_calc(0)))
		return 1;
	printf("G95");
	return 0;
}
