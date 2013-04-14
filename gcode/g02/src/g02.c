#include"../inc/g02.h"
#include"../../inc/gcode.h"
#include"../../inc/g.h"

extern void g02_enter_point (double x1, double y1, double r, double f)
{
	const double dx = 1.0;
	const double dy = 1.0;
	
	double x_r, y_r;
	double** arr;
	double** arr1;
	int size, size1;
	int i;
	
	g02_centerCircle (x1, y1, r, &x_r, &y_r); /*Нахождение центра дуги окружности*/
	
	size = g02_size (dx, dy, x1, y1, r, x_r, y_r); /*Нахождение размера массива точек пересечения с сеткой*/
	
	arr = (double**)malloc(size*sizeof(double*));
	for (i = 0; i < size; ++i)
		arr [i] = (double*)malloc(2*sizeof(double));
	
	arr = g02_ElMas(size, dx, dy, x1, y1, r, x_r, y_r);
	size1 = size;
	g02_offset(arr, &size1); /*Исключение из массива точек одинаковых элементов*/
	arr1 = (double**)malloc(size1*sizeof(double*));
	for (i = 0; i < size1; ++i)
		arr1 [i] = (double*)malloc(2*sizeof(double));
	for (i = 0; i < size1; ++i) {
		arr1 [i][0] = arr [i][0];
		arr1 [i][1] = arr [i][1];
	}
	g02_sort (arr1, size1, x1, y1); /*Сортировка массива точек*/
	/*for (i = 0; i < size1; ++i) {
		printf ("(%f, %f)\n", arr1[i][0], arr1[i][1]);
	}*/
	
	for (i = 0; i < size; ++i) {
		free (arr [i]);
	}
	free (arr);
	for (i = 0; i < size1; ++i) {
		free (arr1 [i]);
	}
	free (arr1);
	
	g_x0 = x1;
	g_y0 = y1;

	/*handle result*/
	if (handler_gcommand_result)
		handler_gcommand_result (g_x0, g_y0, 0, f);
}

void g02_centerCircle (double x1, double y1, double r, double* x_r, double* y_r) {
	if (x1 == g_x0) {
		*y_r = (y1 + g_y0) / 2;
		if (y1 > g_y0)
			*x_r = sqrt(pow(r, 2) - pow(*y_r - y1, 2)) + x1;
		else
			*x_r = -1 * sqrt(pow(r, 2) - pow(*y_r - y1, 2)) + x1;
	}
	else if (y1 == g_y0) {
		*x_r = (x1 + g_x0) / 2;
		if (x1 > g_x0)
			*y_r = -1 * sqrt(pow(r, 2) - pow(*x_r - x1, 2)) + y1;
		else
		*y_r = sqrt(pow(r, 2) - pow(*x_r - x1, 2)) + y1;
	}
	else {
		double x0, y0, k;
		double a, b, c;
		x0 = (x1 + g_x0) / 2;
		y0 = (y1 + g_y0) / 2;
		k = -1 * (x1 - g_x0) / (y1 - g_y0);
		a = pow(k, 2) + 1;
		b = -2 * k * (k*x0 - y0 + y1) - 2 * x1;
		c = pow(x1, 2) + pow(k*x0 - y0 + y1, 2) - pow(r, 2);
		if (x1 > g_x0 && y1 < g_y0 || x1 < g_x0 & y1 < g_y0)
			*x_r = (-1 * b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
		else
			*x_r = (-1 * b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
		*y_r = k * (*x_r - x0) + y0;
	}
}

void g02_area (double dx, double dy, double x1, double y1, double r, double x_r, double y_r, int* kx0, int* kx1, int* ky0, int* ky1) {
	if (x1 == g_x0) {
		if (y1 > g_y0) {
			while (g_y0 >= *ky0 + dy) {
				*ky0 += dy;
			}
			*ky1 = *ky0;
			while (y1 > *ky1) {
				*ky1 += dy;
			}
			while (x_r - r >= *kx0 + dx) {
				*kx0 += dx;
			}
			*kx1 = *kx0;
			while (x1 > *kx1) {
				*kx1 += dx;
			}
		}
		else {
			while (y1 >= *ky0 + dy) {
				*ky0 += dy;
			}
			*ky1 = *ky0;
			while (g_y0 > *ky1) {
				*ky1 += dy;
			}
			while (x1 >= *kx0 + dx) {
				*kx0 += dx;
			}
			*kx1 = *kx0;
			while (x_r + r > *kx1) {
				*kx1 += dx;
			}			
		}
	}
	else if (y1 == g_y0) {
		if (x1 > g_x0) {
			while (g_x0 >= *kx0 + dx) {
				*kx0 += dx;
			}
			*kx1 = *kx0;
			while (x1 > *kx1) {
				*kx1 += dx;
			}
			while (y1 >= *ky0 + dy) {
				*ky0 += dy;
			}
			*ky1 = *ky0;
			while (y_r + r > *ky1) {
				*ky1 += dy;
			}	
		}
		else {
			while (x1 >= *kx0 + dx) {
				*kx0 += dx;
			}
			*kx1 = *kx0;
			while (g_x0 > *kx1) {
				*kx1 += dx;
			}
			while (y_r - r >= *ky0 + dy) {
				*ky0 += dy;
			}
			*ky1 = *ky0;
			while (y1 > *ky1) {
				*ky1 += dy;
			}
		}
	}
	else if (x1 > g_x0) {
		if (y1 > g_y0) {
			while (g_y0 >= *ky0 + dy) {
				*ky0 += dy;
			}
			*ky1 = *ky0;
			if (x_r < x1) {
				while (y_r + r > *ky1) {
					*ky1 += dy;
				}
			}
			else {
				while (y1 > *ky1) {
					*ky1 += dy;
				}
			}
			if (y_r > g_y0) {
				while (x_r - r >= *kx0 + dx) {
					*kx0 += dx;
				}
			}
			else {
				while (g_x0 >= *kx0 + dx) {
					*kx0 += dx;
				}
			}
			*kx1 = *kx0;
			while (x1 > *kx1) {
				*kx1 += dx;
			}
		}
		else {
			while (g_x0 >= *kx0 + dx) {
				*kx0 += dx;
			}
			*kx1 = *kx0;
			if (y_r > y1) {
				while (x_r + r > *kx1) {
					*kx1 += dx;
				}
			}
			else {
				while (x1 > *kx1) {
					*kx1 += dx;
				}
			}
			while (y1 >= *ky0 + dy) {
				*ky0 += dy;
			}
			*ky1 = *ky0;
			if (x_r > g_x0) {
				while (y_r + r > *ky1) {
					*ky1 += dy;
				}
			}
			else {
				while (g_y0 > *ky1) {
					*ky1 += dy;
				}
			}
		}
	}
	else {
		if (y1 < g_y0) {
			while (x1 >= *kx0 + dx) {
				*kx0 += dx;
			}
			*kx1 = *kx0;
			if (y_r < g_y0) {
				while (x_r + r > *kx1) {
					*kx1 += dx;
				}
			}
			else {
				while (g_x0 > *kx1) {
					*kx1 += dx;
				}
			}
			if (x_r > x1) {
				while (y_r - r >= *ky0 + dy) {
					*ky0 += dy;
				}
			}
			else {
				while (y1 >= *ky0 + dy) {
					*ky0 += dy;
				}
			}
			*ky1 = *ky0;
			while (g_y0 > *ky1) {
				*ky1 += dy;
			}
		}
		else {
			if (y_r < y1) {
				while (x_r - r >= *kx0 + dx) {
					*kx0 += dx;
				}
			}
			else {
				while (x1 >= *kx0 + dx) {
					*kx0 += dx;
				}
			}
			*kx1 = *kx0;
			while (g_x0 > *kx1) {
				*kx1 += dx;
			}
			if (x_r < g_x0) {
				while (y_r - r >= *ky0 + dy) {
					*ky0 += dy;
				}
			}
			else {
				while (g_y0 >= *ky0 + dy) {
					*ky0 += dy;
				}
			}
			*ky1 = *ky0;
			while (y1 > *ky1) {
				*ky1 += dy;
			}
		}
	}
	
	//printf ("(%f, %f), (%f, %f)\n", *kx0*dx, *kx1*dx, *ky0*dy, *ky1*dy);
}

int g02_size (double dx, double dy, double x1, double y1, double r, double x_r, double y_r) {
	int kx0 = 0;
	int kx1 = 0;
	int ky0 = 0;
	int ky1 = 0;
	g02_area (dx, dy, x1, y1, r, x_r, y_r, &kx0, &kx1, &ky0, &ky1); /*Нахождение прямоугольной области, в которой находится дуга*/
	double xk0 = kx0 * dx;
	double xk1 = kx1 * dx;
	double yk0 = ky0 * dy;
	double yk1 = ky1 * dy;
	int size = 0;
	double i;
	
	if (x1 == g_x0) {
		if (y1 > g_y0) {
			for (i = xk0; i <= x1; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= g_y0 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= y1)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= g_y0 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= y1)
						size = size + 1;
				}
			}
			double j;
			if (yk0 == g_y0)
				j = yk0;
			else
				j = yk0 + dy;
			for (i = j; i <= y1; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= xk0 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= x1)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= xk0 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= x1)
						size = size + 1;
				}
			}
		}
		else {
			double j;
			if (xk0 == x1)
				j = xk0;
			else
				j = xk0 + dx;
			for (i = j; i <= xk1; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= y1 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= g_y0)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= y1 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= g_y0)
						size = size + 1;
				}
			}
			if (yk0 == y1)
				j = yk0;
			else
				j = yk0 + dy;
			for (i = j; i <= g_y0; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= x1 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= xk1)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= x1 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= xk1)
						size = size + 1;
				}
			}
		}
	}
	else if (y1 == g_y0) {
		if (x1 > g_x0) {
			double j;
			if (xk0 == g_x0)
				j = xk0;
			else
				j = xk0 + dx;
			for (i = j; i <= x1; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= y1 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= yk1)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= y1 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= yk1)
						size = size + 1;
				}
			}
			if (yk0 == g_y0)
				j = yk0;
			else
				j = yk0 + dy;
			for (i = j; i <= yk1; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= g_x0 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= x1)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= g_x0 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= x1)
						size = size + 1;
				}
			}
		}
		else {
			double j;
			if (xk0 == x1)
				j = xk0;
			else
				j = xk0 + dx;
			for (i = j; i <= g_x0; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= yk0 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= y1)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= yk0 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= y1)
						size = size + 1;
				}
			}
			for (i = yk0; i <= y1; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= x1 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= g_x0)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= x1 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= g_x0)
						size = size + 1;
				}
			}			
		}
	}
	else if (x1 > g_x0) {
		if (y1 > g_y0) {
			for (i = xk0; i <= x1; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= g_y0 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= yk1)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= g_y0 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= yk1)
						size = size + 1;
				}
			}
			double j;
			if (yk0 == g_y0)
				j = yk0;
			else
				j = yk0 + dy;
			for (i = j; i <= yk1; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= xk0 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= x1)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= xk0 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= x1)
						size = size + 1;
				}
			}			
		}
		else {
			double j;
			if (xk0 == g_x0)
				j = xk0;
			else
				j = xk0 + dx;
			for (i = j; i <= xk1; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= y1 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= yk1)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= y1 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= yk1)
						size = size + 1;
				}
			}
			if (yk0 == y1)
				j = yk0;
			else
				j = yk0 + dy;
			for (i = j; i <= yk1; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= g_x0 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= kx1)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= g_x0 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= kx1)
						size = size + 1;
				}
			}							
		}
	}
	else {
		if (y1 < g_y0) {
			double j;
			if (xk0 == x1)
				j = xk0;
			else
				j = xk0 + dx;
			for (i = j; i <= xk1; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= yk0 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= g_y0)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= yk0 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= g_y0)
						size = size + 1;
				}
			}
			for (i = yk0; i <= g_y0; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= x1 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= kx1)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= x1 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= kx1)
						size = size + 1;
				}
			}
		}
		else {
			for (i = xk0; i <= g_x0; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= yk0 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= y1)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= yk0 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= y1)
						size = size + 1;
				}
			}
			for (i = yk0; i <= y1; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= xk0 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= g_x0)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= xk0 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= g_x0)
						size = size + 1;
				}
			}
		}
	}
	return size;
}

double** g02_ElMas (int size, double dx, double dy, double x1, double y1, double r, double x_r, double y_r) {
	int kx0 = 0;
	int kx1 = 0;
	int ky0 = 0;
	int ky1 = 0;
	g02_area (dx, dy, x1, y1, r, x_r, y_r, &kx0, &kx1, &ky0, &ky1); /*Нахождение прямоугольной области, в которой находится дуга*/
	double xk0 = kx0 * dx;
	double xk1 = kx1 * dx;
	double yk0 = ky0 * dy;
	double yk1 = ky1 * dy;
	int i;
	int k = 0;
	double** arr = (double**)malloc(size*sizeof(double*));
	for (i = 0; i < size; ++i) {
		arr [i] = (double*)malloc(2*sizeof(double));
	}
	if (x1 == g_x0) {
		if (y1 > g_y0) {
			for (i = xk0; i <= x1; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= g_y0 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= y1) {
						arr [k][0] = i;
						double tmp = sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r;
						arr [k][1] = yk0;
						while (tmp >= arr [k][1] + dy)
							arr [k][1] += dy;
						k = k + 1;
					}
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= g_y0 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= y1) {
						arr [k][0] = i;
						double tmp = -1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r;
						arr [k][1] = yk0;
						while (tmp >= arr [k][1] + dy)
							arr [k][1] += dy;
						k = k + 1;
					}
				}
			}
			double j;
			if (yk0 == g_y0)
				j = yk0;
			else
				j = yk0 + dy;
			for (i = j; i <= y1; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= xk0 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= x1) {
						arr [k][1] = i;
						double tmp = sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r;
						arr [k][0] = xk0;
						while (tmp >= arr [k][0] + dx)
							arr [k][0] += dx;
						k = k + 1;
					}
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= xk0 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= x1) {
						arr [k][1] = i;
						double tmp = -1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r;
						arr [k][0] = xk0;
						while (tmp >= arr [k][0] + dx)
							arr [k][0] += dx;
						k = k + 1;
					}
				}
			}
		}
		else {
			double j;
			if (xk0 == x1)
				j = xk0;
			else
				j = xk0 + dx;
			for (i = j; i <= xk1; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= y1 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= g_y0) {
						arr [k][0] = i;
						double tmp = sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r;
						arr [k][1] = yk0;
						while (tmp >= arr [k][1] + dy)
							arr [k][1] += dy;
						k = k + 1;
					}
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= y1 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= g_y0) {
						arr [k][0] = i;
						double tmp = -1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r;
						arr [k][1] = yk0;
						while (tmp >= arr [k][1] + dy)
							arr [k][1] += dy;
						k = k + 1;
					}
				}
			}
			if (yk0 == y1)
				j = yk0;
			else
				j = yk0 + dy;
			for (i = j; i <= g_y0; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= x1 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= xk1) {
						arr [k][1] = i;
						double tmp = sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r;
						arr [k][0] = xk0;
						while (tmp >= arr [k][0] + dx)
							arr [k][0] += dx;
						k = k + 1;
					}
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= x1 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= xk1) {
						arr [k][1] = i;
						double tmp = -1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r;
						arr [k][0] = xk0;
						while (tmp >= arr [k][0] + dx)
							arr [k][0] += dx;
						k = k + 1;
					}
				}
			}
		}
	}
	else if (y1 == g_y0) {
		if (x1 > g_x0) {
			double j;
			if (xk0 == g_x0)
				j = xk0;
			else
				j = xk0 + dx;
			for (i = j; i <= x1; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= y1 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= yk1) {
						arr [k][0] = i;
						double tmp = sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r;
						arr [k][1] = yk0;
						while (tmp >= arr [k][1] + dy)
							arr [k][1] += dy;
						k = k + 1;
					}
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= y1 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= yk1) {
						arr [k][0] = i;
						double tmp = -1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r;
						arr [k][1] = yk0;
						while (tmp >= arr [k][1] + dy)
							arr [k][1] += dy;
						k = k + 1;
					}
				}
			}
			if (yk0 == g_y0)
				j = yk0;
			else
				j = yk0 + dy;
			for (i = j; i <= yk1; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= g_x0 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= x1) {
						arr [k][1] = i;
						double tmp = sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r;
						arr [k][0] = xk0;
						while (tmp >= arr [k][0] + dx)
							arr [k][0] += dx;
						k = k + 1;
					}
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= g_x0 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= x1) {
						arr [k][1] = i;
						double tmp = -1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r;
						arr [k][0] = xk0;
						while (tmp >= arr [k][0] + dx)
							arr [k][0] += dx;
						k = k + 1;
					}
				}
			}
		}
		else {
			double j;
			if (xk0 == x1)
				j = xk0;
			else
				j = xk0 + dx;
			for (i = j; i <= g_x0; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= yk0 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= y1) {
						arr [k][0] = i;
						double tmp = sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r;
						arr [k][1] = yk0;
						while (tmp >= arr [k][1] + dy)
							arr [k][1] += dy;
						k = k + 1;
					}
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= yk0 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= y1) {
						arr [k][0] = i;
						double tmp = -1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r;
						arr [k][1] = yk0;
						while (tmp >= arr [k][1] + dy)
							arr [k][1] += dy;
						k = k + 1;
					}
				}
			}
			for (i = yk0; i <= y1; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= x1 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= g_x0) {
						arr [k][1] = i;
						double tmp = sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r;
						arr [k][0] = xk0;
						while (tmp >= arr [k][0] + dx)
							arr [k][0] += dx;
						k = k + 1;
					}
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= x1 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= g_x0) {
						arr [k][1] = i;
						double tmp = -1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r;
						arr [k][0] = xk0;
						while (tmp >= arr [k][0] + dx)
							arr [k][0] += dx;
						k = k + 1;
					}
				}
			}			
		}
	}
	else if (x1 > g_x0) {
		if (y1 > g_y0) {
			for (i = xk0; i <= x1; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= g_y0 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= yk1) {
						arr [k][0] = i;
						double tmp = sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r;
						arr [k][1] = yk0;
						while (tmp >= arr [k][1] + dy)
							arr [k][1] += dy;
						k = k + 1;
					}
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= g_y0 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= yk1) {
						arr [k][0] = i;
						double tmp = -1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r;
						arr [k][1] = yk0;
						while (tmp >= arr [k][1] + dy)
							arr [k][1] += dy;
						k = k + 1;
					}
				}
			}
			double j;
			if (yk0 == g_y0)
				j = yk0;
			else
				j = yk0 + dy;
			for (i = j; i <= yk1; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= xk0 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= x1) {
						arr [k][1] = i;
						double tmp = sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r;
						arr [k][0] = xk0;
						while (tmp >= arr [k][0] + dx)
							arr [k][0] += dx;
						k = k + 1;
					}
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= xk0 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= x1) {
						arr [k][1] = i;
						double tmp = -1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r;
						arr [k][0] = xk0;
						while (tmp >= arr [k][0] + dx)
							arr [k][0] += dx;
						k = k + 1;
					}
				}
			}			
		}
		else {
			double j;
			if (xk0 == g_x0)
				j = xk0;
			else
				j = xk0 + dx;
			for (i = j; i <= xk1; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= y1 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= yk1) {
						arr [k][0] = i;
						double tmp = sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r;
						arr [k][1] = yk0;
						while (tmp >= arr [k][1] + dy)
							arr [k][1] += dy;
						k = k + 1;
					}
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= y1 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= yk1) {
						arr [k][0] = i;
						double tmp = -1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r;
						arr [k][1] = yk0;
						while (tmp >= arr [k][1] + dy)
							arr [k][1] += dy;
						k = k + 1;
					}
				}
			}
			if (yk0 == y1)
				j = yk0;
			else
				j = yk0 + dy;
			for (i = j; i <= yk1; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= g_x0 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= kx1) {
						arr [k][1] = i;
						double tmp = sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r;
						arr [k][0] = xk0;
						while (tmp >= arr [k][0] + dx)
							arr [k][0] += dx;
						k = k + 1;
					}
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= g_x0 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= kx1) {
						arr [k][0] = i;
						double tmp = -1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r;
						arr [k][0] = xk0;
						while (tmp >= arr [k][0] + dx)
							arr [k][0] += dx;
						k = k + 1;
					}
				}
			}							
		}
	}
	else {
		if (y1 < g_y0) {
			double j;
			if (xk0 == x1)
				j = xk0;
			else
				j = xk0 + dx;
			for (i = j; i <= xk1; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= yk0 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= g_y0) {
						arr [k][0] = i;
						double tmp = sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r;
						arr [k][1] = yk0;
						while (tmp >= arr [k][1] + dy)
							arr [k][1] += dy;
						k = k + 1;
					}
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= yk0 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= g_y0) {
						arr [k][0] = i;
						double tmp = -1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r;
						arr [k][1] = yk0;
						while (tmp >= arr [k][1] + dy)
							arr [k][1] += dy;
						k = k + 1;
					}
				}
			}
			for (i = yk0; i <= g_y0; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= x1 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= kx1) {
						arr [k][1] = i;
						double tmp = sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r;
						arr [k][0] = xk0;
						while (tmp >= arr [k][0] + dx)
							arr [k][0] += dx;
						k = k + 1;
					}
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= x1 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= kx1) {
						arr [k][0] = i;
						double tmp = -1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r;
						arr [k][0] = xk0;
						while (tmp >= arr [k][0] + dx)
							arr [k][0] += dx;
						k = k + 1;
					}
				}
			}
		}
		else {
			for (i = xk0; i <= g_x0; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= yk0 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= y1) {
						arr [k][0] = i;
						double tmp = sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r;
						arr [k][1] = yk0;
						while (tmp >= arr [k][1] + dy)
							arr [k][1] += dy;
						k = k + 1;
					}
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= yk0 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= y1) {
						arr [k][0] = i;
						double tmp = -1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r;
						arr [k][1] = yk0;
						while (tmp >= arr [k][1] + dy)
							arr [k][1] += dy;
						k = k + 1;
					}
				}
			}
			for (i = yk0; i <= y1; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= xk0 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= g_x0) {
						arr [k][1] = i;
						double tmp = sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r;
						arr [k][0] = xk0;
						while (tmp >= arr [k][0] + dx)
							arr [k][0] += dx;
						k = k + 1;
					}
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= xk0 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= g_x0) {
						arr [k][0] = i;
						double tmp = -1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r;
						arr [k][0] = xk0;
						while (tmp >= arr [k][0] + dx)
							arr [k][0] += dx;
						k = k + 1;
					}
				}
			}
		}
	}
	return arr;
}

void g02_offset (double** arr, int* size) {
	int i, j, k;
	for (i = 0; i < *size; ++i)
		for (j = i + 1; j < *size; ++j)
			if (arr [i][0] == arr [j][0] && arr [i][1] == arr [j][1]) {
				*size = *size - 1;
				arr [j][0] = arr [*size][0];
				arr [j][1] = arr [*size][1];
				j = j - 1;
			}
}

void g02_sort (double** arr, int size, double x1, double y1) {
	int i, j;
	if (x1 == g_x0) {
		if (y1 > g_y0) {
			for (i = 0; i < size; ++i) {
				for (j = i + 1; j < size; ++j) {
					if (arr [i][1] > arr [j][1]) {
						double tmp = arr [i][1];
						arr [i][1] = arr [j][1];
						arr [j][1] = tmp;
						tmp = arr [i][0];
						arr [i][0] = arr [j][0];
						arr [j][0] = tmp;
					}
				}
			}
		}
		else {
			for (i = 0; i < size; ++i) {
				for (j = i + 1; j < size; ++j) {
					if (arr [i][1] < arr [j][1]) {
						double tmp = arr [i][1];
						arr [i][1] = arr [j][1];
						arr [j][1] = tmp;
						tmp = arr [i][0];
						arr [i][0] = arr [j][0];
						arr [j][0] = tmp;
					}
				}
			}
		}
	}
	else if (y1 == g_y0) {
		if (x1 > g_x0) {
			for (i = 0; i < size; ++i) {
				for (j = i + 1; j < size; ++j) {
					if (arr [i][0] > arr [j][0]) {
						double tmp = arr [i][0];
						arr [i][0] = arr [j][0];
						arr [j][0] = tmp;
						tmp = arr [i][1];
						arr [i][1] = arr [j][1];
						arr [j][1] = tmp;
					}
				}
			}
		}
		else {
			for (i = 0; i < size; ++i) {
				for (j = i + 1; j < size; ++j) {
					if (arr [i][0] < arr [j][0]) {
						double tmp = arr [i][0];
						arr [i][0] = arr [j][0];
						arr [j][0] = tmp;
						tmp = arr [i][1];
						arr [i][1] = arr [j][1];
						arr [j][1] = tmp;
					}
				}
			}
		}
	}
	else if (x1 > g_x0) {
		int ind = -1;
		if (y1 > g_y0) {
			for (i = 0; i < size; ++i) {
				for (j = i + 1; j < size; ++j) {
					if (arr [i][1] > arr [j][1]) {
						double tmp = arr [i][1];
						arr [i][1] = arr [j][1];
						arr [j][1] = tmp;
						tmp = arr [i][0];
						arr [i][0] = arr [j][0];
						arr [j][0] = tmp;
					}
				}
			}
			for (i = 0; i < size; ++i)
				if (g_x0 < arr [i][0]) {
						ind = i;
						break;
				}
			if (ind != -1)
				for (i = ind; i < size; ++i) {
					for (j = i + 1; j < size; ++j) {
						if (arr [i][0] > arr [j][0]) {
							double tmp = arr [i][0];
							arr [i][0] = arr [j][0];
							arr [j][0] = tmp;
							tmp = arr [i][1];
							arr [i][1] = arr [j][1];
							arr [j][1] = tmp;
						}
					}
				}			
		}
		else {
			for (i = 0; i < size; ++i) {
				for (j = i + 1; j < size; ++j) {
					if (arr [i][0] > arr [j][0]) {
						double tmp = arr [i][0];
						arr [i][0] = arr [j][0];
						arr [j][0] = tmp;
						tmp = arr [i][1];
						arr [i][1] = arr [j][1];
						arr [j][1] = tmp;
					}
				}
			}
			for (i = 0; i < size; ++i)
				if (g_y0 > arr [i][1]) {
						ind = i;
						break;
				}
			if (ind != -1)
				for (i = ind; i < size; ++i) {
					for (j = i + 1; j < size; ++j) {
						if (arr [i][1] < arr [j][1]) {
							double tmp = arr [i][1];
							arr [i][1] = arr [j][1];
							arr [j][1] = tmp;
							tmp = arr [i][0];
							arr [i][0] = arr [j][0];
							arr [j][0] = tmp;
						}
					}
				}
		}
	}
	else {
		int ind = -1;
		if (y1 < g_y0) {
			for (i = 0; i < size; ++i) {
				for (j = i + 1; j < size; ++j) {
					if (arr [i][1] < arr [j][1]) {
						double tmp = arr [i][1];
						arr [i][1] = arr [j][1];
						arr [j][1] = tmp;
						tmp = arr [i][0];
						arr [i][0] = arr [j][0];
						arr [j][0] = tmp;
					}
				}
			}
			for (i = 0; i < size; ++i)
				if (g_x0 > arr [i][0]) {
						ind = i;
						break;
				}
			if (ind != -1)
				for (i = ind; i < size; ++i) {
					for (j = i + 1; j < size; ++j) {
						if (arr [i][0] < arr [j][0]) {
							double tmp = arr [i][0];
							arr [i][0] = arr [j][0];
							arr [j][0] = tmp;
							tmp = arr [i][1];
							arr [i][1] = arr [j][1];
							arr [j][1] = tmp;
						}
					}
				}			
		}
		else {
			for (i = 0; i < size; ++i) {
				for (j = i + 1; j < size; ++j) {
					if (arr [i][0] < arr [j][0]) {
						double tmp = arr [i][0];
						arr [i][0] = arr [j][0];
						arr [j][0] = tmp;
						tmp = arr [i][1];
						arr [i][1] = arr [j][1];
						arr [j][1] = tmp;
					}
				}
			}
			for (i = 0; i < size; ++i)
				if (g_y0 < arr [i][1]) {
						ind = i;
						break;
				}
			if (ind != -1)
				for (i = ind; i < size; ++i) {
					for (j = i + 1; j < size; ++j) {
						if (arr [i][1] < arr [j][1]) {
							double tmp = arr [i][1];
							arr [i][1] = arr [j][1];
							arr [j][1] = tmp;
							tmp = arr [i][0];
							arr [i][0] = arr [j][0];
							arr [j][0] = tmp;
						}
					}
				}
		}
	}
}
