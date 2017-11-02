typedef file
{
	char name[100];
	int mode;
	int uid;
	int gid;
	off_t size;
	long mtime;
	int chksum;
	int typeflag;
	char lname[100];
	int version;
	char uname[32];
	char gname[32]
	char* devmajor;
	char prefix[155];
};	
