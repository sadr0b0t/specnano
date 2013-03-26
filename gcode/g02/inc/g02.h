#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void g02_centerCircle (double, double, double, double*, double*);
double** approximation ();
int g02_size (double, double, double, double, double, double, double);
void g02_area (double, double, double, double, double, double, double, int*, int*, int*, int*);
double** g02_ElMas (int, double, double, double, double, double, double, double);
void g02_offset (double**, int*);
void g02_sort (double**, int, double, double);

extern void g02_enter_point (double, double, double, double);
