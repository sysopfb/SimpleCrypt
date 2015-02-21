#include <stdio.h>
#include "rc4.h"
#include "dosheader.h"
#include "packer_funcs/packre_funcs.h"

int main(int argc, char *argv[])
{
	unsigned char *data;
	unsigned char *key;

	if(argc != 3)
	{
		printf("Usage: %s <file> <key>", argv[0]);
		exit(1);
	}

	


	rc4(bleh, key);

	printf("\n%s\n", bleh);

	rc4(bleh, key);

	printf("\n%s\n", bleh);

	return 0;
}
