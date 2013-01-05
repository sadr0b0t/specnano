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
	int i;
	for(i=0; i<9; i++)
		setFlags[i]=0;
}
