#include<stdio.h>

extern int gcode_g01(int* flags, double x, double y, double z, double f)
{
	if(flags[0])
		printf("G1: X%f Y%f Z%f F%f\n", x, y, z, f);
	else
		return 1;
	return 0;
}

extern int gcode_g02(int* flags, double x, double y, double z, double f, double r)
{
	if(flags[0] && flags[8])
		printf("G2: X%f Y%f Z%f R%f F%f\n", x, y, z, r, f);
	else
		return 1;
	return 0;
}
