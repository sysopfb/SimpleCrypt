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
	char szFilePath[1024];

	//getfilepath
	GetModuleFileNameA(0, szFilePath, 1024);


	if(getDataPtr(szFilePath, &pos, 0) != 0)
		exit(-1);

	char key[] = "test\0";

	FILE *self = fopen(szFilePath, "rb");
	if(pos)
		fseek(self, pos, SEEK_SET);
	fread((void *)&conf, sizeof(conf), 1, self);


	return 0;
}


