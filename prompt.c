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

void prompt()
{
	int i;//general use
	char dir[1000];//stores getcwd
	char pwd[1000];//stores getcwd after removing home

	char* user=getenv("USER");//user
	char* home=getenv("HOME");//home

	//to get linux version
	struct utsname buf;
	int ret=uname(&buf);
	if(ret)
	{
		printf("Error in the System call\n");
	}
	char*t1=strtok(buf.version," ");
	char*t2=strtok(t1,"-");
	t2=strtok(NULL,"-");

	//pwd
	getcwd(dir,sizeof(dir));
	if(strlen(dir)<=strlen(home))
	{
		strcpy(pwd,dir);
	}
	else
	{
		for(i=0;dir[i]==home[i];i++);
		int j=i;
		while(dir[i]!='\0')
		{
			pwd[i-j]=dir[i];
			i++;
		}
		pwd[i-j]='\0';
	}

	//homedir for cd ~
	//will be executed only once
	if(homeflag==1)
	{
		strcpy(homedir,dir);
		homeflag=0;
	}

	//print prompt
	printf("%s@%s:~%s$ ",user,t2,pwd);
}