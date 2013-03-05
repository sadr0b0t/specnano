#include<stdio.h>
#include"../inc/file_processing_method.h"
#include"../inc/gcode.h"
#include"../inc/G_commands.h"

FILE* f;

int test6_math(char* input_data_path)
{
    handler_g01 = &gcode_g01;

    char file_path[strlen(input_data_path) + strlen("input_test04") + 2]; 
    sprintf(file_path, "%s/%s", input_data_path, "input_test04");
	f=fopen(file_path, "r");

	int i;
	for(i=0; i<5; i++)
		if(file_processing(f))
			return 0;
}

