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

void execute()
{
	int status;
	pid_t wpid;//datatype

	pid=fork();

	//error in forking
	if(pid<0)
		printf("Cannot create child process\n");

	//child process
	else if (pid==0)
	{
		redirectioncheck();

		if(in1i!=-1)
		{

			//printf("executing cmd\n");
			if(execvp(buf[0],buf)==-1)//-1 if failed
				printf("%s: command not found\n",buf[0]);

			//dup2(pipeout,1);
			//dup2(pipein,0);
		}
		if(in1==1)
			close(in1i);
		if(out1==1)
			close(out1i);
		if(out2==1)
			close(out2i);
		
		}

	//parent process
	else
	{
		//background process
		if(bg==1)
		{
			bg_proc_initialize(pid,buf[0]);
			printf("[%d] %d\n",maxbg,pid);
		}

		//foreground process
		else//do while bacause we need it to run atleast once
		{
			waitpid(pid,&status,WUNTRACED);
			/*do
			{
				wpid = waitpid(pid, &status, WUNTRACED);
				//wuntraced to return if a child has stopped
				//status stores status info
			}
			while (!WIFEXITED(status) && !WIFSIGNALED(status));
			//waits for child to end
			//WIFEXITED returns true if the child terminated normally
			//WIFSIGNALED returns true if the child process was terminated by a signal.
			*/
			
		}
		bgprocexecute();
	}

}