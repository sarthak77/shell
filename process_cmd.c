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
		cmd[strlen(cmd)-1]='\0';//remove & for testing
	}
	else
		bg=0;
	//printf("bg:%d\n",bg);

	buf=malloc(100*sizeof(char*));
	int i=0;
	char*token=strtok(cmd," ,	");
	while((token!=NULL) && (bg==0 || (bg==1 && strcmp(token,"&"))))//to not store &
	{
		//printf("%s\n",token);
		buf[i++]=token;
		token=strtok(NULL," ,	");
	}
	buf[i]=NULL;
	//for(int j=0;j<i;j++)
	//	printf("%s\n",buf[j]);
}