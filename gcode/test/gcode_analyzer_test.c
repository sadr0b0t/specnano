#include<stdio.h>
#include"../inc/file_processing_method.h"
#include"../inc/gcode.h"
#include"test.h"

FILE* f;

int handler_g01_test4(int* a, double x, double y, double z, double f)
{
	printf("G1: X%f Y%f Z%f F%f\n", x, y, z, f);
	if(x==2 && y==3 && z==4 && f==5)
		printf("pass!");
	else
		printf("fail!");
}

int test1(char* input_data_path)
{
    char file_path[strlen(input_data_path) + strlen("input_test01") + 2]; 
    sprintf(file_path, "%s/%s", input_data_path, "input_test01");
	f=fopen(file_path, "r");
	while(1)
	{
		if(file_processing(f))
			return 0;
	}
}

int test2(char* input_data_path)
{
	char file_path[strlen(input_data_path) + strlen("input_test01") + 2]; 
    sprintf(file_path, "%s/%s", input_data_path, "input_test01");
	f=fopen(file_path, "r");
	
	if(file_processing(f))
		return 0;
}

int test3(char* input_data_path)
{
    char file_path[strlen(input_data_path) + strlen("input_test01") + 2]; 
    sprintf(file_path, "%s/%s", input_data_path, "input_test01");
	f=fopen(file_path, "r");
	
	int i;
	for(i=0; i<5; i++)
		if(file_processing(f))
			return 0;
}

int test4(char* input_data_path)
{
    handler_g01 = &handler_g01_test4;

    char file_path[strlen(input_data_path) + strlen("input_test04") + 2]; 
    sprintf(file_path, "%s/%s", input_data_path, "input_test04");
	f=fopen(file_path, "r");
	
	int i;
	if(file_processing(f))
		return 0;
}

int test5(char* input_data_path)
{
    char file_path[strlen(input_data_path) + strlen("input_test04") + 2]; 
    sprintf(file_path, "%s/%s", input_data_path, "input_test04");
	f=fopen(file_path, "r");

	int i;
	for(i=0; i<5; i++)
		if(file_processing(f))
			return 0;
}


