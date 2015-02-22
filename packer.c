#include <stdio.h>
#include <Windows.h>
#include "rc4.h"
#include "packer_funcs/packre_funcs.h"

int main(int argc, char *argv[])
{
	unsigned char *data;
	unsigned char *key;

	if(argc != 4)
	{
		printf("Usage: %s <stub> <file> <key>", argv[0]);
		exit(1);
	}

	char stubCopy[MAX_PATH];
	strcpy(stubCopy, argv[1]);
	strcat(stubCopy, ".crypted.exe");

	CopyFile(argv[1], stubCopy, FALSE);

	//rc4 encrypt file

	FILE *stub = open(stubCopy, "rb+");

	FILE *fp = open(argv[2], "rb");
	fseek(fp, 0, SEEK_END);
	long fileSize = ftell(fp);
	long none = 0;
	rewind(fp);

	fseek(stub, 0, SEEK_END);
	
	fwrite(fileSize, sizeof(fileSize), 1, stub);
	fwrite(none, sizeof(none), 1, stub);

	long stubSize = ftell(stub);

	char buff[4096 * 2];

	while(fileSize > 0)
	{
		long rw = fileSize > sizeof(buff) ? sizeof(buff) : fileSize;
		fread(buff, rw, 1, fp);
		fwrite(buff, rw, 1, stub);
		fileSize -= rw;
	}
	fclose(fp);
	fclose(stub);

	setDataPtr(stubCopy, stubSize);

	return 0;
}
