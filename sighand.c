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

//ctrl c
void sigintHandler(int sig_num)
{
	//printf ("\n");
	//prompt();
	fflush (stdout);
}


//ctrl z
void sigstpHandler(int sig_num)
{
	if(pid!=0)
	{
		kill(pid,SIGSTOP);
		maxbg++;
		a[maxbg].pid=pid;
		a[maxbg].jobid=maxbg;
		strcpy(a[maxbg].command,cmd);
		strcpy(a[maxbg].status,"Stopped");
		a[maxbg].flag=0;
		a[maxbg].state=1;
		printf("[%d]+  %s\t\t%s\n",a[maxbg].jobid,a[maxbg].status,a[maxbg].command);
		pid=0;
	}
	else
	{
		//printf ("\n");
		//prompt();
		fflush (stdout);	
	}
}

//ctrl '\'
void sigqHandler(int sig_num)
{
	printf("\n");
	prompt();
}
