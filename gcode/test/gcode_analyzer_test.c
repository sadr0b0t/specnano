#include<stdio.h>
#include"../inc/file_processing_method.h"

FILE* f;

void* handler_g01(double x, double y, double z, double f);

void handler_g01_test4(double x, double y, double z, double f)
{
	printf("G1: X%f Y%f Z%f F%f\n", x, y, z, f);
	if(x==2 && y==3 && z==4 && f==5)
		printf("pass!");
	else
		printf("fail!");
}

int test1()
{
	f=fopen("input", "r");
	while(1)
	{
		if(file_processing(f))
			return 0;
	}
}

int test2()
{
	f=fopen("input", "r");
	if(file_processing(f))
		return 0;
}

int test3()
{
	f=fopen("input", "r");
	int i;
	for(i=0; i<5; i++)
		if(file_processing(f))
			return 0;
}

int test4()
{
	f=fopen("input_one_line", "r");
	int i;
	if(file_processing(f))
		return 0;
}

int test5()
{
	f=fopen("input_two_lines", "r");
	int i;
	for(i=0; i<5; i++)
		if(file_processing(f))
			return 0;
}

/*void gcode_g01(double x, double y, double z, double f)
{
	handler_g01(x, y, z, f);
}*/

int main()
{
	printf("############## test1 ##############\n");
	test1();
	printf("############## End of test1 ##############\n");
	printf("############## test2 ##############\n");
	test2();
	printf("############## End of test2 ##############\n");
	printf("############## test3 ##############\n");
	test3();
	printf("############## End of test3 ##############\n");
}
