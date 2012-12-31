#include <stdio.h>
#include <stdlib.h>
#include "Read.h"

void read (float* x0, float* y0, float* z0, float* x1, float* y1, float* z1) {
	char ch;
	char arr [256];
	float coord [6];
	int i = 0;
	int j = 0;
	FILE * in;
	in = fopen ("in.txt","r");
	while (!feof(in)) {
		ch = getc (in);
		if (ch >= 48 && ch <= 57  || ch == 45 || ch == 46) {
			arr [i++] = ch;
			while (ch != ',' && ch != ')') {
				ch = getc (in);
				arr [i++] = ch;
			}
			arr [i] = '\0';
			i = 0;
			coord [j++] = atof (arr);
		}
	}
	fclose (in);
	*x0 = coord [0];
	*y0 = coord [1];
	*z0 = coord [2];
	*x1 = coord [3];
	*y1 = coord [4];
	*z1 = coord [5];
}

void input (float* x0, float* y0, float* z0, float* x1, float* y1, float* z1) {
	scanf ("%f %f %f %f %f %f", x0, y0, z0, x1, y1, z1);
}