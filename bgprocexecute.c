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

void bgprocexecute()
{
	pid_t wpid;
	int status;
	int i;

	while((wpid=waitpid(-1,&status,WNOHANG))>0)//returns -1 if all processes finished
	{
		//if finished
		if(WIFEXITED(status) || WIFSIGNALED(status))
		{
			//search for child
			for(i=1;i<=maxbg;i++)
			{
				//will be printed only if another not built in command executed
				if(a[i].pid==wpid && a[i].flag==0)
					printf("[%d]+	Done\t\t\t%s with pid %d\n",a[i].jobid,a[i].command, wpid);
				if(a[i].pid==wpid && a[i].flag==1)
					printf("REMINDER: %s\n",a[i].command);
			}
			//prompt();
		}
	}

	//if all procs finished then maxbg=0
	wpid=waitpid(-1,&status,WNOHANG);
	if(wpid==-1)
		maxbg=0;
}