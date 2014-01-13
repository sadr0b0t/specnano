#include"../inc/file_processing_method.h"

/*Способ обработки входного файла*/
/*Function, that define method of file processing*/
extern int file_processing(FILE* f)
{
	int c=0;
	do
	{
		c=fgetc(f);
	}
	while(c=='\n' || c=='\r');
	if(c==-1)
		return 1;
	ungetc(c, f);
	if(parse_start(f))
		return 0;
	return 1;
}
