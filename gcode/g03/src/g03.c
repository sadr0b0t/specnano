#include"../inc/g03.h"

double g03_x0 = 3.2;
double g03_y0 = 2.3;

extern void g03_enter_point (double x1, double y1, double r, double f)
{
	const double dx = 1.0;
	const double dy = 1.0;
	
	double x_r, y_r;
	double** arr;
	int size;
	
	g03_centerCircle (x1, y1, r, &x_r, &y_r);
	
	printf ("g03: (%f, %f)\n", x_r, y_r);
	
	size = g03_size (dx, dy, x1, y1, r, x_r, y_r);
	printf ("%d\n", size);
	
	g03_x0 = x1;
	g03_y0 = y1;
}

void g03_centerCircle (double x1, double y1, double r, double* x_r, double* y_r) {
	if (x1 == g03_x0) {
		*y_r = (y1 + g03_y0) / 2;
		if (y1 > g03_y0)
			*x_r = -1 * sqrt(pow(r, 2) - pow(*y_r - y1, 2)) + x1;
		else
			*x_r = sqrt(pow(r, 2) - pow(*y_r - y1, 2)) + x1;
	}
	else if (y1 == g03_y0) {
		*x_r = (x1 + g03_x0) / 2;
		if (x1 > g03_x0)
			*y_r = sqrt(pow(r, 2) - pow(*x_r - x1, 2)) + y1;
		else
			*y_r = -1 * sqrt(pow(r, 2) - pow(*x_r - x1, 2)) + y1;		
	}
	else {
		double x0, y0, k;
		double a, b, c;
		x0 = (x1 + g03_x0) / 2;
		y0 = (y1 + g03_y0) / 2;
		k = -1 * (x1 - g03_x0) / (y1 - g03_y0);
		a = pow(k, 2) + 1;
		b = -2 * k * (k*x0 - y0 + y1) - 2 * x1;
		c = pow(x1, 2) + pow(k*x0 - y0 + y1, 2) - pow(r, 2);
		if (x1 > g03_x0 && y1 < g03_y0 || x1 < g03_x0 & y1 < g03_y0)
			*x_r = (-1 * b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
		else
			*x_r = (-1 * b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
		*y_r = k * (*x_r - x0) + y0;
	}
}

void g03_area (double dx, double dy, double x1, double y1, double r, double x_r, double y_r, int* kx0, int* kx1, int* ky0, int* ky1) {
	if (x1 == g03_x0) {
		if (y1 > g03_y0) {
			while (g03_y0 >= *ky0 + dy) {
				*ky0 += dy;
			}
			*ky1 = *ky0;
			while (y1 > *ky1) {
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
		else {
			while (y1 >= *ky0 + dy) {
				*ky0 += dy;
			}
			*ky1 = *ky0;
			while (g03_y0 > *ky1) {
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
	}
	else if (y1 == g03_y0) {
		if (x1 > g03_x0) {
			while (g03_x0 >= *kx0 + dx) {
				*kx0 += dx;
			}
			*kx1 = *kx0;
			while (x1 > *kx1) {
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
		else {
			while (g03_x0 >= *kx0 + dx) {
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
	}
	else if (x1 > g03_x0) {
		if (y1 < g03_y0) {
			if (y_r < g03_y0) {
				while (x_r - r >= *kx0 + dx) {
					*kx0 += dx;
				}
			}
			else {
				while (g03_x0 >= *kx0 + dx) {
					*kx0 += dx;
				}
			}
			*kx1 = *kx0;
			while (x1 > *kx1) {
				*kx1 += dx;
			}
			if (x_r < x1) {
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
			while (g03_y0 > *ky1) {
				*ky1 += dy;
			}
		}
		else {
			while (g03_x0 >= *kx0 + dx) {
				*kx0 += dx;
			}
			*kx1 = *kx0;
			if (y_r < y1) {
				while (x_r + r > *kx1) {
					*kx1 += dx;
				}
			}
			else {
				while (x1 > *kx1) {
					*kx1 += dx;
				}
			}
			if (x_r > g03_x0) {
				while (y_r - r >= *ky0 + dy) {
					*ky0 += dy;
				}
			}
			else {
				while (g03_y0 >= *ky0 + dy) {
					*ky0 += dy;
				}
			}
			*ky1 = *ky0;
			while (y1 > *ky1) {
				*ky1 += dy;
			}
		}
	}
	else {
		if (y1 > g03_y0) {
			while (x1 >= *kx0 + dx) {
				*kx0 += dx;
			}
			*kx1 = *kx0;
			if (y_r > g03_y0) {
				while (x_r + r > *kx1) {
					*kx1 += dx;
				}
			}
			else {
				while (g03_x0 > *kx1) {
					*kx1 += dx;
				}
			}
			while (g03_y0 >= *ky0 + dy) {
				*ky0 += dy;
			}
			*ky1 = *ky0;
			if (x_r > x1) {
				while (y_r + r > *ky1) {
					*ky1 += dy;
				}
			}
			else {
				while (y1 > *ky1) {
					*ky1 += dy;
				}
			}
		}
		else {
			while (y1 >= *ky0 + dy) {
				*ky0 += dy;
			}
			*ky1 = *ky0;
			if (x_r < g03_x0) {
				while (y_r + r > *ky1) {
					*ky1 += dy;
				}
			}
			else {
				while (g03_y0 > *ky1) {
					*ky1 += dy;
				}
			}
			if (y_r > y1) {
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
			while (g03_x0 > *kx1) {
				*kx1 += dx;
			}
		}
	}
	
	printf ("(%f, %f), (%f, %f)\n", *kx0*dx, *kx1*dx, *ky0*dy, *ky1*dy);
}

int g03_size (double dx, double dy, double x1, double y1, double r, double x_r, double y_r) {
	int kx0 = 0;
	int kx1 = 0;
	int ky0 = 0;
	int ky1 = 0;
	g03_area (dx, dy, x1, y1, r, x_r, y_r, &kx0, &kx1, &ky0, &ky1);
	double xk0 = kx0 * dx;
	double xk1 = kx1 * dx;
	double yk0 = ky0 * dy;
	double yk1 = ky1 * dy;
	int size = 0;
	double i;
	
	if (x1 == g03_x0) {
		if (y1 > g03_y0) {
			double j;
			if (xk0 == x1)
				j = xk0;
			else
				j = xk0 + dx;
			for (i = j; i <= xk1; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= g03_y0 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= y1)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= g03_y0 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= y1)
						size = size + 1;
				}
			}
			if (yk0 == g03_y0)
				j = yk0;
			else
				j = yk0 + dy;
			for (i = j; i <= y1; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= x1 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= xk1)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= x1 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= xk1)
						size = size + 1;
				}
			}
		}
		else {
			for (i = xk0; i <= x1; i = i + dx) {
				if (r >= i - x_r) {
					if ((sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= y1 && (sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= g03_y0)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) >= y1 && (-1*sqrt(pow(r, 2) - pow(i - x_r, 2)) + y_r) <= g03_y0)
						size = size + 1;
				}
			}
			double j;
			if (yk0 == y1)
				j = yk0;
			else
				j = yk0 + dy;
			for (i = j; i <= g03_y0; i = i + dy) {
				if (r >= i - y_r) {
					if ((sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= xk0 && (sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= x1)
						size = size + 1;
					if ((-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) >= xk0 && (-1*sqrt(pow(r, 2) - pow(i - y_r, 2)) + x_r) <= x1)
						size = size + 1;
				}
			}	
		}
	}
	else if (y1 == g03_y0) {
		if (x1 > g03_x0) {
			
		}
		else {
			
		}
	}
	else if (x1 > g03_x0) {
		if (y1 > g03_y0) {
			
		}
		else {
			
		}
	}
	else {
		if (y1 < g03_y0) {
			
		}
		else {
			
		}
	}
	return size;
}
