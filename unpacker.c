#include <Windows.h>
#include "dosheader.h"
#include "unpacker_funcs/unpacker_funcs.h"
#include "rc4.h"

struct conf{
	int length;
	int stop;
} conf;

int main()
{
	long *pos;
	TCHAR szFilePath[1024];

	//getfilepath
	GetModuleFileNameA(0, LPSTR(szFilePath), 1024);


	if(getDataPtr(szFilePath, pos, 0) != 0)
		exit(-1);

	char key[] = "test\0";

	fread((void *)&conf, sizeof(conf), 1, pos);
	

	return 0;
}


