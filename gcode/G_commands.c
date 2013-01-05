void gcode_g01(double x, double y, double z, double f)
{
	printf("G1: %f %f %f\n", x, y, z);
}

void gcode_g02(double x, double y, double z, double f, double r)
{
	printf("G2: %f %f %f\n", x, y, z);
}
