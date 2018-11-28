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


void processbuilt_cmd()
{
    char temp[1000];
    strcpy(temp,cmd);
    char*token2=strtok(cmd,">,<,>>");
    strcpy(cmd,token2);
    //free(cmd);
	char*token=strtok(temp," ,	");
    

    while(token!=NULL)
    {
        if(in1==1 || out1==1 || out2==1)
		{
			if(doubleredirect==0)
			{
				strcpy(redirectfile,token);
				doubleredirect=1;
				token=strtok(NULL," ,	");
			}
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
			////both redirections
	        if((in1 && out1) || (in1 && out2))
		        strcpy(redirectfile2,token);
			
            token=strtok(NULL," ,	");
		}
    }
}