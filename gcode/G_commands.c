#include<stdio.h>

extern void gcode_g01(double x, double y, double z, double f)
{
	printf("G1: X%f Y%f Z%f F%f\n", x, y, z, f);
}

extern void gcode_g02(double x, double y, double z, double f, double r)
{
	printf("G2: X%f Y%f Z%f R%f F%f\n", x, y, z, r, f);
}
