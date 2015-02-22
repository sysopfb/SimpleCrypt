#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "unpacker_funcs/unpacker_funcs.h"
#include "rc4.h"

struct conf{
	int length;
	int stop;
} conf;

int main()
{
	long pos;
	long len;
	char szFilePath[1024];

	//getfilepath
	GetModuleFileNameA(0, szFilePath, 1024);


	if(getDataPtr(szFilePath, &pos, 0) != 0)
		exit(-1);

	FILE *self = fopen(szFilePath, "rb");
	if(pos)
		fseek(self, pos, SEEK_SET);
    //Old code to be pruned later
	//fread((void *)&conf, sizeof(conf), 1, self);

    fread(&len, sizeof(int), 1, self);
    //fscanf(self, "%d", &len);

    //Test code for now
    printf("%d\n", len);

    unsigned char *data = malloc(len+1);
    fread((char *)data, len, 1, self);

    printf("%s\n", data);

    unsigned char key[] = "test";
    rc4(data, key, len);

    printf("%s\n", data);

    fclose(self);
    free(data);

	return 0;
}


