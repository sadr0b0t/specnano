void brezenhem()
{
	double k; 
	double error = 0;
	double k1;
	int i, j;
	int coord_x = 0;
	int coord_y = 0;
		
	
	deltax = x1 - x0;
	deltay = y1 - y0;
	
	k = (double) deltay / deltax;
	k1 = (double) deltax / deltay;
	
	if(k != 0 && k1 != 0)
	{
		deltax = abs(deltax) + 1;
		deltay = abs(deltay) + 1;
		
		picture = (uint8_t **) malloc(deltay * sizeof(uint8_t *));
		
		for(i = 0; i < deltay; i++)
		{
			picture[i] = (uint8_t *) malloc(deltax * sizeof(uint8_t));
			
			for(j = 0; j < deltax; j++)
			{
				picture[i][j] = ' ';
			}
		}
	  
		if(k > 1)
		{
			int coord_x = 0;
			
			for(i = 0; i < deltay && coord_x < deltax; i++)
			{
				picture[i][coord_x] = '*';
				
				error += k1;
				
				if(error >= 0.5)
				{
					error -= 1;
					coord_x++;
				}
			}
		}
		if(k == 1)
		{
			for(i = 0; i < deltax; i++)
			{
				picture[i][i] = (uint8_t) '*';
			}
		}
		if(k < 1 && k > 0)
		{
			coord_y = 0;

			for(i = 0; i < deltax && coord_y < deltay; i++)
			{
				picture[coord_y][i] = '*';
				
				error += k;
				
				if(error >= 0.5)
				{
					error -= 1;
					coord_y++;
				}
			}
		}
		if(k < 0 && k > -1)
		{
			coord_y = deltay - 1;
			
			printf("k = %g\nk1 = %g\n", k, k1);
			
			for(i = 0; i < deltax && coord_y >= 0; i++)
			{
				picture[coord_y][i] = '*';
				
				error += k;
				
				if(error <= -0.5)
				{
					error += 1;
					coord_y--;
				}
			}
		}
		if(k == -1)
		{
			for(i = 0; i < deltax; i++)
			{
				picture[deltax - i][i] = (uint8_t) '*';
			}
		}
		if(k < -1)
		{
			coord_x = 0;
			
			printf("k = %g\nk1 = %g\n", k, k1);
			
			for(i = deltay - 1; i >= 0 && coord_x < deltax; i--)
			{
				picture[i][coord_x] = (uint8_t) '*';
				
				error += k1;
				
				
				if(error <= -0.5)
				{
					error += 1;
					coord_x++;
				}
			}
		}
		/**
		draw(picture, x0, x1, y0, y1);
		**/
	}
	if(k == 0)
	{
		deltay = abs(deltay) + 1;
		
		pict = (uint8_t *) malloc(deltay * sizeof(uint8_t));
		
		for(i = 0; i < deltay; i++)
		{
			pict[i] = (uint8_t) '*';
		}
		/**
		drawline(picture, 1, deltay);
		**/
	}
	if(k1 == 0)
	{
		pict = (uint8_t *) malloc(deltax);
		
		for(i = 0; i < deltax; i++)
		{
			pict[i] = (uint8_t) '*';
		}
		
		/**
		drawline(picture, 1, deltax);
		**/
	}
}
