#include"../inc/g02.h"

extern void g02_enter_point (double x0, double y0, double z0, int radius)
{
	int i;
	int size = 50 * radius * radius;
	double** arr = (double**)malloc(size*sizeof(double*));
	for (i = 0; i < size; ++i)
	{
		arr [i] = (double*)malloc(3*sizeof(double));
	}
	for (i = 0; i < size; ++i)
	{
		arr [i][0] = 0;
		arr [i][1] = 0;
		arr [i][2] = 0;
	}
    int count = 0;
    double teta,fi;
    fi = 0.0;
    teta = (-1) * M_PI / 2;
    for (teta; teta < M_PI/2; teta = teta + M_PI/(5*radius))
    {
        for (fi; fi < 2*M_PI; fi = fi + M_PI/(5*radius))
        {
            double c_x = x0 + radius * sin(teta) * cos(fi);
            double c_y = y0 + radius * sin(teta) * sin(fi);
            double c_z = z0 + radius * cos(teta);
            int t_x = c_x;
            int t_y = c_y;
            int t_z = c_z;
            //X
            if (c_x - t_x < 0.5)
                t_x = t_x;
            else
                t_x += 1;

            //Y
            if (c_y - t_y < 0.5)
                t_y = t_y;
            else
                t_y += 1;

            //Z
            if (c_z - t_z < 0.5)
                t_z = t_z;
            else
                t_z += 1;

            arr[count][0] = t_x;
			arr[count][1] = t_y;
			arr[count][2] = t_z;
            count += 1;
            if (count == size)
                break;
        }

        fi = 0.0;
        if (count == size)
            break;
    }
	for (i = 0; i < size; ++i)
	{
		printf("(%f, %f, %f)\n", arr [i][0],  arr [i][1],  arr [i][2]);
	}
	for (i = 0; i < size; ++i)
	{
		free (arr [i]);
	}
	free (arr);
}