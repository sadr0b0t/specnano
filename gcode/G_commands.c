#define GCode_G01 1
#define GCode_G02 2

void gcode_g01(double x, double y, double z, double f)
{
	printf("G%d: %f %f %f\n", command, x, y, z);
}

void gcode_g02(double x, double y, double z, double f, double r)
{
	printf("G%d: %f %f %f\n", command, x, y, z);
}

void GCommands(void)
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
				gcode_g01(x, y, z, F, R);
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
