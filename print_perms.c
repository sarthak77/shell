//libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/stat.h> 
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <sys/dir.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include<sys/utsname.h>
#include "declarations.h"

void print_perms(mode_t st) 
{
	char perms[11];

	if(st && S_ISREG(st)) perms[0]='-';
	else if(st && S_ISDIR(st)) perms[0]='d';
	else if(st && S_ISFIFO(st)) perms[0]='|';
	else if(st && S_ISSOCK(st)) perms[0]='s';
	else if(st && S_ISCHR(st)) perms[0]='c';
	else if(st && S_ISBLK(st)) perms[0]='b';
	else perms[0]='l';  // S_ISLNK

	perms[1] = (st && S_IRUSR) ? 'r':'-';
	perms[2] = (st && S_IWUSR) ? 'w':'-';
	perms[3] = (st && S_IXUSR) ? 'x':'-';
	perms[4] = (st && S_IRGRP) ? 'r':'-';
	perms[5] = (st && S_IWGRP) ? 'w':'-';
	perms[6] = (st && S_IXGRP) ? 'x':'-';
	perms[7] = (st && S_IROTH) ? 'r':'-';
	perms[8] = (st && S_IWOTH) ? 'w':'-';
	perms[9] = (st && S_IXOTH) ? 'x':'-';

	perms[10] = '\0';
	printf("%s", perms);
}