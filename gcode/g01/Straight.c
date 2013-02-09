#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Read.h"

int sizeArr (float, float, float, float, float, float, const float, const float, const float); // Возвращает размер массива
void u (int*, float, float, const float);
void filling (float**, int*, const float, char, int); // Заполнение массива
void sort (float**, int, char); // Сортировка массива
void offset (float**, int*); // Смещение массива
void coordVertice (float**, int, const float, const float, const float);

int main () {
	int i, j;
	const float dx = 1.0;
	const float dy = 1.0;
	const float dz = 1.0;
	float x0, y0, z0, x1, y1, z1; // Наччальные и конечные координаты точек
	int size; // Размер массива
	float** arr;
	float** arrCoord; // Массив точек
	float** arrCoordVertice; // Массив координат вершин
	int index = 1;
	read (&x0, &y0, &z0, &x1, &y1, &z1); // Считывание из файла
	//input (&x0, &y0, &z0, &x1, &y1, &z1); // Ввод
	size = sizeArr (x0, y0, z0, x1, y1, z1, dx, dy, dz);
	arr = (float**)malloc(size*sizeof(float*));
	for (i = 0; i < size; ++i) {
		arr [i] = (float*)malloc(3*sizeof(float));
	}
	arr [0][0] = x0;
	arr [0][1] = y0;
	arr [0][2] = z0;
	arr [size - 1][0] = x1;
	arr [size - 1][1] = y1;
	arr [size - 1][2] = z1;
	filling (arr, &index, dx, 'x', size);
	filling (arr, &index, dy, 'y', size);
	filling (arr, &index, dz, 'z', size);
	if (x0 != x1) {
		sort (arr, size, 'x');
	}
	else if (y0 != y1) {
		sort (arr, size, 'y');
	}
	int tmpSize = size;
	offset (arr, &size);
	arrCoord = (float**)malloc(size*sizeof(float*));
	for (i = 0; i < size; ++i) {
		arrCoord [i] = (float*)malloc(3*sizeof(float));
	}
	for (i = 0; i < size; ++i) {
		for (j = 0; j < 3; ++j) {
			arrCoord [i][j] = arr [i][j];
		}
	}
	for (i = 0; i < size; ++i) {
		printf ("(%f, %f, %f)\n", arrCoord [i][0], arrCoord [i][1], arrCoord [i][2]);
	}
	coordVertice (arrCoord, size, dx, dy, dz);
	int tmpSizeCoord = size;
	offset (arrCoord, &size);
	arrCoordVertice = (float**)malloc(size*sizeof(float*));
	for (i = 0; i < size; ++i) {
		arrCoordVertice [i] = (float*)malloc(3*sizeof(float));
	}
	printf ("\n");
	for (i = 0; i < size; ++i) {
		printf ("(%f, %f, %f)\n", arrCoord [i][0], arrCoord [i][1], arrCoord [i][2]);
	}
	for (i = 0; i < tmpSize; ++i) {
		free (arr [i]);
	}
	free (arr);
	for (i = 0; i < tmpSizeCoord; ++i) {
		free (arrCoord [i]);
	}
	free (arrCoord);
	for (i = 0; i < size; ++i) {
		free (arrCoordVertice [i]);
	}
	free (arrCoordVertice);
	return 0;
}

int sizeArr (float x0, float y0, float z0, float x1, float y1, float z1, const float dx, const float dy, const float dz) {
	int size = 2;
	u (&size, x0, x1, dx);
	u (&size, y0, y1, dy);
	u (&size, z0, z1, dz);
	return size;
}

void u (int* size, float u0, float u1, const float du) {
	float quant = 0;
	if (u0 < u1) {
		if (u0 >= 0) {
			while (quant <= u0) {
				quant += du;
			}
		}
		else {
			while (quant >= u0 + du) {
				quant -= du;
			}
			if (u0 == quant) {
				quant += du;
			}
		}
		while (quant < u1) {
			*size = *size + 1;
			quant += du;
		}
	}
	else if (u0 > u1) {
		if (u0 > 0) {
			while (quant <= u0 - du) {
				quant += du;
			}
			if (u0 == quant) {
				quant -= du;
			}
		}
		else {
			while (quant >= u0) {
				quant -= du;
			}
		}
		while (quant > u1) {
			*size = *size + 1;
			quant -= du;
		}
	}
}

void filling (float** arr, int* index, const float du, char u, int size) {
	float quant = 0;
	float u0, u1;
	if (u == 'x') {
		u0 = arr [0][0];
		u1 = arr [size - 1][0];
	}
	else if (u == 'y') {
		u0 = arr [0][1];
		u1 = arr [size - 1][1];			
	}
	else {
		u0 = arr [0][2];
		u1 = arr [size - 1][2];					
	}	
	if (u0 < u1) {
		if (u0 >= 0) {
			while (quant <= u0) {
				quant += du;
			}
		}
		else {
			while (quant >= u0 + du) {
				quant -= du;
			}
			if (u0 == quant) {
				quant += du;
			}
		}
		while (quant < u1) {
			if (u == 'x') {
				arr [*index][0] = quant;
				arr [*index][1] = (arr [*index][0] - u0) * (arr [size - 1][1] - arr [0][1]) / (u1 - u0) + arr [0][1];
				arr [*index][2] = (arr [*index][0] - u0) * (arr [size - 1][2] - arr [0][2]) / (u1 - u0) + arr [0][2];
			}
			else if (u == 'y') {
				arr [*index][1] = quant;
				arr [*index][0] = (arr [*index][1] - u0) * (arr [size - 1][0] - arr [0][0]) / (u1 - u0) + arr [0][0];
				arr [*index][2] = (arr [*index][1] - u0) * (arr [size - 1][2] - arr [0][2]) / (u1 - u0) + arr [0][2];				
			}
			else {
				arr [*index][2] = quant;
				arr [*index][0] = (arr [*index][2] - u0) * (arr [size - 1][0] - arr [0][0]) / (u1 - u0) + arr [0][0];
				arr [*index][1] = (arr [*index][2] - u0) * (arr [size - 1][1] - arr [0][1]) / (u1 - u0) + arr [0][1];					
			}
			quant += du;
			*index = *index + 1;
		}
	}
	else if (u0 > u1) {
		if (u0 > 0) {
			while (quant <= u0 - du) {
				quant += du;
			}
			if (u0 == quant) {
				quant -= du;
			}
		}
		else {
			while (quant >= u0) {
				quant -= du;
			}
		}
		while (quant > u1) {
			if (u == 'x') {
				arr [*index][0] = quant;
				arr [*index][1] = (arr [*index][0] - u0) * (arr [size - 1][1] - arr [0][1]) / (u1 - u0) + arr [0][1];
				arr [*index][2] = (arr [*index][0] - u0) * (arr [size - 1][2] - arr [0][2]) / (u1 - u0) + arr [0][2];
			}
			else if (u == 'y') {
				arr [*index][1] = quant;
				arr [*index][0] = (arr [*index][1] - u0) * (arr [size - 1][0] - arr [0][0]) / (u1 - u0) + arr [0][0];
				arr [*index][2] = (arr [*index][1] - u0) * (arr [size - 1][2] - arr [0][2]) / (u1 - u0) + arr [0][2];				
			}
			else {
				arr [*index][2] = quant;
				arr [*index][0] = (arr [*index][2] - u0) * (arr [size - 1][0] - arr [0][0]) / (u1 - u0) + arr [0][0];
				arr [*index][1] = (arr [*index][2] - u0) * (arr [size - 1][1] - arr [0][1]) / (u1 - u0) + arr [0][1];
			}
			quant -= du;
			*index = *index + 1;
		}
	}
}

void sort (float** arr, int size, char u) {
	float temp [3];
	int i, j, k, l;
	float u0, u1;
	if (u == 'x') {
		u0 = arr [0][0];
		u1 = arr [size - 1][0];
		k = 0;
	}
	else {
		u0 = arr [0][1];
		u1 = arr [size - 1][1];	
		k = 1;		
	}
	if (u0 < u1) {
		for (i = 1; i < size - 1; ++i) {
			for (j = 1; j < size - 1; ++j) {
				if (arr [i][k] < arr [j][k]) {
					for (l = 0; l < 3; ++l) {
						temp [l] = arr [i][l];
						arr [i][l] = arr [j][l];
						arr [j][l] = temp [l];
					}
				}
			}
		}
	}
	else {
		for (i = 1; i < size - 1; ++i) {
			for (j = 1; j < size - 1; ++j) {
				if (arr [i][k] > arr [j][k]) {
					for (l = 0; l < 3; ++l) {
						temp [l] = arr [i][l];
						arr [i][l] = arr [j][l];
						arr [j][l] = temp [l];
					}
				}
			}
		}
	}
}

void offset (float** arr, int* size) {
	int i, j, k, l;
	for (i = 0; i < *size; ++i) {
		for (j = i + 1; j < *size; ++j) {
			if (arr [i][0] == arr [j][0] && arr [i][1] == arr [j][1] && arr [i][2] == arr [j][2]) {
				for (l = j; l < *size - 1; ++l) {
					for (k = 0; k < 3; ++k) {
						arr [l][k] = arr [l + 1][k];
					}
				}
				*size = *size - 1;
				j--;
			}
			else {
				j = *size - 1;
			}
		}
	}
}

void coordVertice (float** arr, int size, const float dx, const float dy, const float dz) {
	int i, j;
	float quant = 0;
	float du;
	for (i = 0; i < size; ++i) {
		for (j = 0; j < 3; ++j) {
			if (j == 0)
				du = dx;
			else if (j == 1)
				du = dy;
			else
				du = dz;
			if (arr [i][j] > 0) {
				while (arr [i][j] >= quant) {
					quant += du;
				}
				arr [i][j] = quant - du;
			}
			else if (arr [i][j] < 0) {
				while (arr [i][j] < quant) {
					quant -= du;
				}
				arr [i][j] = quant;
			}
			quant = 0;
		}
	}
}