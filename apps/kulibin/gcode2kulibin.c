#include<stdio.h>
#include"../../gcode/inc/file_processing_method.h"
#include"../../gcode/inc/gcode.h"
#include"../../gcode/inc/G_commands.h"
#include"../../gcode/g01/inc/g01.h"

FILE* f;

int handler_result_kulibin(double dx, double dy, double dz, double f) {
	printf("move(%f, %f, %f)\n", dx, dy, dz);
}

int gcode2kulibin(char* file_path) {
    handler_g01 = &gcode_g01;
    handler_gcommand_result = &handler_result_kulibin;

	f=fopen(file_path, "r");

	int i;
	for(i=0; i<5; i++)
		if(file_processing(f))
			return 0;
}

int main(void) {
    gcode2kulibin("input.g");
    return 0;
}
