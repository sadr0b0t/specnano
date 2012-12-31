void GCommands(void)
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
	int i;
	for(i=0; i<5; i++)
		setFlags[i]=0;
}
