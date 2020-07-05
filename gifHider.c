#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_FILE_SIZE (1024*1024)

const char *getFilenameExt(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

void hide(char* fileName)
{
	FILE *fptr;
	char data[MAX_FILE_SIZE];
	fptr = fopen(fileName, "rb");
	int i =0;
	int j;
	while(!feof(fptr))
		data[i++] = fgetc(fptr);
	fclose(fptr);

	fptr = fopen(fileName, "wb");
	for(j = 0 ; j < i-1 ; j++)
		fputc(data[j] ^ 0x60, fptr);
	fclose(fptr);
}

int main(int argc, char *argv[])
{
	DIR *directory;
	struct dirent* file;
	FILE* a;
	char ch;
	if(argc != 2)
	{
		printf("Error\n", argv[0]);
		exit(1);
	}
	directory = opendir(argv[1]);
	if(directory == NULL)
	{
		printf("Eroor\n");
		exit(2);
	}
	while((file=readdir(directory)) != NULL)
	{
		if(strcmp(getFilenameExt(file->d_name), "gif") == 0)
			hide(file->d_name);
	}
	return 0;
}