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

//for multiple bg processes and reminder handling
void bg_proc_initialize(int pid,char*string)
{
	maxbg++;
	a[maxbg].pid=pid;
	a[maxbg].jobid=maxbg;
	if(!remindflag)
	{
		strcpy(a[maxbg].command,string);
		a[maxbg].flag=0;
	}
	else
	{
		strcpy(a[maxbg].command,remindmsg);
		a[maxbg].flag=1;
		//printf("erere");
	}
}