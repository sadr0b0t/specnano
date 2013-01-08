#include<stdio.h>
#include"../file_processing_method.h"

FILE* f;

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
