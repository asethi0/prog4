#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
#include "tar.h"
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
char get_typeflag(char* name)
{
	char retVal;
	struct stat file_stat;
	stat(name, &file_stat);
	if(S_ISREG(file_stat.st_mode))
		retVal = '0';
	else if(S_ISLNK(file_stat.st_mode))
		retVal = '2';
	else if(S_ISDIR(file_stat.st_mode))
		retVal = '5';
	/*need to   do  test case for regular file(alternate)*/
	return retVal;	
}

char get_type_from_flag(dir_tree_node* node)
{
	char retVal;
	char flag = node->data->typeflag;
	if(flag =='0' ||flag == '\0')
	{
		retVal = 'f';
	}
	else if(flag == '2')
	{
		retVal = 's';
	}
	
	else
	{
		retVal = 'd';
	}

	return retVal;
}


void add_file(struct* dirent dir)
{
	ino_t inode = dir.d_ino;
	char* name = dir.d_name;
	
	struct stat file_info;
	lstat(dir->d_name,&file_info);
	
	struct file* header = malloc(sizeof(file));
	if(header == NULL)
	{
		perror("malloc failed");
		exit(1);
	}
	strcpy(header->name, name);
	header->mode = file_info.st_mode;
	header->uid = file_info.st_uid;
	header->gid = file_info.st_gid;
	header->size = file_info.st_size;
	header->mtime = file_info.mtime; 
	header->typeflag = get_typeflag(name);
	
	/*finding out if file is of type symlink
 * 	if it is,lname will be set to value of link  */
	if(strcmp(get_typeflag(name),"2") == 0) 
		header->lname =     	
	header->version = malloc(sizof(char) *2);
	header->version = "00";

	/*for uname and gname*/
	struct group* grp;
	struct passwd* pwd;
	grp = getgrgid(gid);
	pwd = getpwuid(uid); 
	header->uname = pwd->pw_name;
	header->gname = grp->gr_name;
	header->devmajor ="00000000";
	header->devminor = "00000000";

	/*prefix is not assigned a value because it must store relative path
 * 	this needs to be updated in the add directotry method*/

}	


void addNode(file* file, file* parent)
{
}
/*returns 1 if it exists*/
int file_exists(char* filename)
{
	struct stat file;
	return (stat(filename, &file) == 0);
}

FILE* create_archive(char* name)
{
	FILE *fp;
	fp = fopen(name, "w+")
	return fp;
}

	
