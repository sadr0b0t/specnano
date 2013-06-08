void brez_circle()
{
	int i, j;
	int x, y;
	int delta = 2 - 2 * radius;
	int error = 0;
	
	size = radius * 2 - 1;
	pict = (uint8_t **) malloc(size * sizeof(uint8_t *));
	
	for(i = 0; i < size; i++)
	{
		pict[i] = (uint8_t *) malloc(size);
		
		for(j = 0; j < size; j++)
		{
			pict[i][j] = ' ';
		}
	}
	
	pict[x0][y0] = '*';
	y = radius - 1;
	x = 0;
	
	while(y >= 0)
	{
		pict[x0 + x - 1][y0 - y] = '*';
		pict[x0 + x - 1][y0 + y] = '*';
		pict[x0 - x + 1][y0 - y] = '*';
		pict[x0 - x + 1][y0 + y] = '*';
		
		
		error = 2 * (delta + y) - 1;
		
		if(delta < 0 && error <= 0) 
		{
			x = x + 1;
			delta += 2 * x + 1;
			continue;
		}
		
		error = 2 * (delta - x) - 1;
		
		if(delta > 0 && error > 0) 
		{
			y = y - 1;
			delta += 1 - 2 * y;
			continue;
		}
		
		x = x + 1;
		delta += 2 * (x - y);
		y = y - 1;
	}
}
