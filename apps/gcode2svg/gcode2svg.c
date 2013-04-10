#include<stdio.h>
#include"../../gcode/inc/file_processing_method.h"
#include"../../gcode/inc/gcode.h"
#include"../../gcode/inc/G_commands.h"
#include"../../gcode/g01/inc/g01.h"

FILE* f;

int handler_result_svg(double dx, double dy, double dz, double f) {
	printf("%f,%f ", dx, dy);
}

int gcode2svg(char* file_path) {
    handler_g01 = &gcode_g01;
    handler_gcommand_result = &handler_result_svg;

	f=fopen(file_path, "r");

	int i;
	for(i=0; i<5; i++)
		if(file_processing(f))
			return 0;
}

int main(void) {
    printf("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
    printf("<svg>\n");
    printf("<g id=\"layer1\">\n");
    printf("<path d=\"m ");

    gcode2svg("input.g");

    printf("\" \n");
    
    printf("id=\"path1\"\n");
    printf("   style=\"fill:none;stroke:#000000;stroke-width:1px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\" />\n");
    printf("</g>\n");
    printf("</svg>\n");
    
    return 0;
}

