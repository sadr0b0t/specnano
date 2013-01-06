#include<stdio.h>

int main()
{
	FILE* f;
	int c=0;
	f=fopen("input", "r");
	while(1)
	{
		do
		{
			c=fgetc(f);
		}
		while(c=='\n');
		if(c==-1)
			return 0;
		ungetc(c, f);
		E(f);
	};
	return 0;
}
