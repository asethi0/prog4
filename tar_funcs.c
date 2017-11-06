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
	struct stat info;

	char fname[500];
	while((dp = readdir(dir)) != NULL)
	{
		struct stat file;
		fname = dp->d_name;
		lstat(fname, &info);
		if(S_ISREG(file.st_mode))
		{
			add_file(dp);/*makes the header*/
			write_file(fname, writeFile);
		}

		if(S_ISDIR9file.st_mode)
		{
			add_dir(fname);
			chdir(fname);
			write_dir(fname, writeFile);
			chdir("..");
		}
	}
}		

					
int get_permissions(char* path)
{
	 struct stat ret;
    if (stat(path, &ret) == -1) {
        printf("unable to access file\n");
			exit(1);
    }

 return (ret.st_mode & S_IRUSR)|(ret.st_mode & S_IWUSR)|(ret.st_mode & S_IXUSR)|/*owner*/
        (ret.st_mode & S_IRGRP)|(ret.st_mode & S_IWGRP)|(ret.st_mode & S_IXGRP)|/*group*/
        (ret.st_mode & S_IROTH)|(ret.st_mode & S_IWOTH)|(ret.st_mode & S_IXOTH);/*other*/
}

	
		
