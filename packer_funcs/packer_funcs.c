#include <stdio.h>
#include "../dosheader.h"

int setDataPtr(char *file, long pos, int sect)
{
	FILE *fp = fopen(file, "rb+");
	if(fp == NULL)
		return -1;

	IMAGE_DOS_HEADER idh;

	fread((void *)&idh, sizeof(idh), 1, fp);

	*(long *)&idh.e_res2[sect] = pos;

	rewind(fp);
	fwrite((void *)&idh, sizeof(idh), 1, fp);
	fclose(fp);
	return 0;
}
