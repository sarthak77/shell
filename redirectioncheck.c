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

void redirectioncheck()
{
    if((in1 && out1) || (in1 && out2))
		{
			in1i=open(redirectfile, O_RDONLY);
			if(in1i==-1)
			{
				builtinredirecterror=1;
				perror("ERROR");
			}
			else
				dup2(in1i,0);

			if(out1)
			{
				out1i=open(redirectfile2,O_WRONLY | O_TRUNC | O_CREAT, 0664);
				dup2(out1i,1);
			}

			else if(out2)
			{
				out2i=open(redirectfile2,O_WRONLY | O_APPEND | O_CREAT, 0664);
				dup2(out2i,1);
			}
		}
	else
		{
			if(in1==1)
			{
				in1i=open(redirectfile, O_RDONLY);
				if(in1i==-1)
				{
					builtinredirecterror=1;
					perror("ERROR");
				}
				else
					dup2(in1i,0);
			}
			else if(out1==1)
			{
				out1i=open(redirectfile,O_WRONLY | O_TRUNC | O_CREAT, 0664);
				dup2(out1i,1);
			}
			else if(out2==1)
			{
				out2i=open(redirectfile,O_WRONLY | O_APPEND | O_CREAT, 0664);
				dup2(out2i,1);
			}
		}
}