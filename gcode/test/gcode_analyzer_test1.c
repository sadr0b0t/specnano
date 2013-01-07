#include<stdio.h>
#include"../file_processing_method.c"

int main()
{
	FILE* f;
	f=fopen("input", "r");
	while(1)
	{
		if(file_processing(f))
			return 0;
	}
}
