#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
#include "tar.h"
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
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

char get_type_from_flag(dir_node* node)
{
	char retVal;
	char flag = node->typeflag;
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
	struct dir_node* header = malloc(sizeof(dir_node));
	if(header == NULL)
	{
		perror("malloc failed");
		exit(1);
	}
	strcpy(header->name, name);
	strcpy(header->mode, file_info.st_mode);
	strcpy(header->uid, file_info.st_uid);
	strcpy(header->gid, file_info.st_gid);
	strcpy(header->size, file_info.st_size);
	strcpy(header->mtime, file_info.mtime); 
	strcpy(header->typeflag, get_typeflag(name));
	
	if(strcmp(get_typeflag(name),"2") == 0) 
	{
		ssize_t len;
		len = readlink(name, header->linkname, sizeof(header->linkname) -1);
		header->linkname[len] = '\0';	
	}		
	header->version = malloc(sizof(char) *2);
	header->version = "00";

/*	for uname and gname */
	struct group* grp;
	struct passwd* pwd;
	grp = getgrgid(gid);
	pwd = getpwuid(uid); 
	strcpy(header->uname, pwd->pw_name);
	strcpy(header->gname, grp->gr_name);
	header->devmajor ="00000000";
	header->devminor = "00000000";
}	
/*
void add_dir(char *pathname) {
        dir_node *node = malloc(sizeof(dir_node));
        DIR *dir_stream = opendir(pathname);
        struct stat stat_buff;
        struct dirent entry;


        node->name = pathname;

        getcwd(node->prefix, 155);

        entry = readdir(dir_stream);
        lstat(entry.d_name, &stat_buff);

        node->mode= (char *)stat_buff.st.mode;
        node->uid = (char *)stat_buff.st_uid;
        node->gid = (char *)stat_buff.st_gid;
        node->size = "000000000000";
        node->mtime = (char *)stat_buff.st_mtime;
        node->typeflag = get_typeflag(pathname);
        node->linkname = {0};
        node->magic = "ustar\0";
        node->version = "00";
        struct group* grp;
        struct passwd* pwd;
        grp = getgrgid(gid);
        pwd = getpwuid(uid);
        node->uname = pwd->pw_name;
        node->gname = grp->gr_name;
        node->devmajor ="00000000";
        node->devminor = "00000000";
/*added a check for the curretn direcotry (.)*/
  /*      while(entry = readdir(dir_stream)) {
                if (entry.d_name != ".."|| entry.d_name!= "." ) {
                        add_entry(entry.d_name);
                }
        }

}*/


void add_entry(char *name) 
{
        char flag = get_typeflag(name);
        if (flag == '0' || flag == '2') {
                add_file(name);
        }
        else {
                add_dir(name);
        }
}


/*returns 1 if it exists*/
int file_exists(char* filename)
{
	struct stat file;
	return (stat(filename, &file) == 0);
}

void create_archive(char* name)
{
	FILE *fp;
	fp = fopen(name, "w+");
	fclose(fp);
}

	
