#include"../inc/g03.h"

double g03_x0 = 4;
double g03_y0 = 4;

extern void g03_enter_point (double x1, double y1, double r, double f)
{
	const double dx = 1.0;
	const double dy = 1.0;
	
	double x_r, y_r;
	g03_centerCircle (x1, y1, r, &x_r, &y_r);
	printf ("g03: (%f, %f)\n", x_r, y_r);
	
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