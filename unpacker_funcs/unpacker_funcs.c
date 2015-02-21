#include <stdio.h>
#include <Windows.h>

int getDataPtr(char *file, long *pos, int sect)
{
	FILE *fp = fopen(file, "rb");
	if(fp == NULL)
		return -1;

	IMAGE_DOS_HEADER idh;

	fread((void *)&idh, sizeof(idh), 1, fp);
	fclose(fp);
	*pos = *(long *)&idh.e_res2[sect];
	return 0;
}
