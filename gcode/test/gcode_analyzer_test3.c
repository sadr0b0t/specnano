#include<stdio.h>
#include"../file_processing_method.c"

int main()
{
	FILE* f;
	f=fopen("input", "r");
	int i;
	for(i=0; i<5; i++)
		if(file_processing(f))
			return 0;
}
