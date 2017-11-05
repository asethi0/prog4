#include Mytar.c

void write_header(struct dir_node node, char* archiveName)
{
	FILE* fp;
	fp = fopen(archiveName, "a");
	/*appends to the end of the file*/
	int i = 0;
	for(i; i < 17; i++)
	{
		fwrite(&node[i], sizeof(node[i]), 1, fp);
	}
	fclose(fp);
}

/*writefile is the file which will have the header*/
void write_file(char* readFile, char* writeFile)
{
	FILE* read;
	FILE* write;
	read = fopen(readFile, "r");
	if(read == NULL)
	{
		printf("cannot open file for reading\n ");
		exit(1);
	}
	
	write = fopen(writeFile, "a");
	if(write == NULL)
	{
		printf("cannot open file to write to\n");
		exit(1);
	}

	char c;
	c = fgetc(read);
	while(c!= EOF)
	{
		fputc(c, write);
		c = fgetc(read);
	}
	fclose(read);
	fclose(write);
}

void write_dir(char* dirName, char* writeFile)
{
	DIR* dir;
	dir = opendir(dirName);
	if(dir == NULL)
	{
		printf("cannot open directory\n");
	}

	struct dirent* dp;
	char fname[500];
	while((dp = readdir(dir)) != NULL)
	{
		struct stat file;
		fname = 		

	
		