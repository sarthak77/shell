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

//modifying cmd to give it to execvp
void process_cmd()
{	
	//check if bg
	if(cmd[strlen(cmd)-1]=='&')
	{
		bg=1;
		cmd[strlen(cmd)-1]='\0';//remove &
	}
	else
		bg=0;
	//printf("bg:%d\n",bg);

	buf=malloc(100*sizeof(char*));
	int i=0;
	char*token=strtok(cmd," ,	");
	while((token!=NULL) && (bg==0 || (bg==1 && strcmp(token,"&"))))//to not store &
	{

		if(in1==1 || out1==1 || out2==1)
		{
			if(doubleredirect==0)
			{
				strcpy(redirectfile,token);
				doubleredirect=1;
				token=strtok(NULL," ,	");
			}
			//break;
		}

		if(token!=NULL)
		{
			if(!strcmp(token,"<"))
			{
				in1=1;
			}
			else if(!strcmp(token,">"))
			{
				out1=1;
			}
			else if(!strcmp(token,">>"))
			{
				out2=1;
			}
			else
				buf[i++]=token;
			
			token=strtok(NULL," ,	");
		}
	}

	//both redirections
	if((in1 && out1) || (in1 && out2))
	{
		strcpy(redirectfile2,buf[1]);
		buf[1]=NULL;	
	}

	buf[i]=NULL;
	//for(int j=0;buf[j]!=NULL;j++)
	//	printf("%s\n",buf[j]);
}