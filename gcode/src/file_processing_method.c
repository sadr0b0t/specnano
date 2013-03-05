#include"../inc/file_processing_method.h"

extern int file_processing(FILE* f)
{
	int c=0;
	do
	{
		c=fgetc(f);
	}
	while(c=='\n');
	if(c==-1)
		return 1;
	ungetc(c, f);
	if(parse_start(f))
		return 0;
	return 1;
}
