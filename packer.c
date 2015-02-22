#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "rc4.h"
#include "packer_funcs/packer_funcs.h"


int main(int argc, char *argv[])
{
	unsigned char *data;
	//unsigned char *key;

	if(argc != 4)
	{
		printf("Usage: %s <stub> <file> <key>", argv[0]);
		exit(1);
	}

    //Copy file so we don't overwrite our stub
	char stubCopy[MAX_PATH];
	strcpy(stubCopy, argv[1]);
	strcat(stubCopy, ".crypted.exe");

	CopyFile(argv[1], stubCopy, FALSE);


    //Open needed files (missing error checking)
	//Stub
	FILE *stub = fopen(stubCopy, "rb+");
	//File to encrypt
	FILE *fp = fopen(argv[2], "rb");
	//Get filesize of file to encrypt
	fseek(fp, 0, SEEK_END);
	long fileSize = ftell(fp);
	rewind(fp);

    //Get size of stub in bytes
	fseek(stub, 0, SEEK_END);
    long stubSize = ftell(stub);


    //Write the file size to end of stub
	fwrite(&fileSize, sizeof(int), 1, stub);
    //Write length of key
    int keylength = strlen(argv[3])+1;
    fwrite(&keylength, sizeof(int),1, stub);
    //Write the key
    unsigned char *key = malloc(keylength);
    strcpy(key, argv[3]);
    fwrite(key, keylength, 1, stub);

    //Need a buffer to hold our entire file
    unsigned char *buff = malloc(fileSize+1);
    memset(buff, 0, fileSize+1);
    fread(buff, fileSize, 1, fp);
    //*(buff + fileSize) = '\0';
    //key needs to be added to beginning of file (structure?)
    //unsigned char key[] = "test";
    rc4(buff, key, fileSize, keylength);
    //Test printf
    printf("%s\n", buff);

    //fprintf(stub, "%d", &fileSize);
    fwrite(buff, fileSize, 1, stub);

    //Test code below
    rc4(buff, key, fileSize, keylength);
    printf("%s\n", buff);
    /*
	char buff[4096 * 2];
	while(fileSize > 0)
	{
		long rw = fileSize > sizeof(buff) ? sizeof(buff) : fileSize;
		fread(buff, rw, 1, fp);
		fwrite(buff, rw, 1, stub);
		fileSize -= rw;
	}*/
	fclose(fp);
	fclose(stub);
	free(buff);
	free(key);

	setDataPtr(stubCopy, stubSize, 0);

	return 0;
}
