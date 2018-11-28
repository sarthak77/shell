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

int builtin_check()
{
    //check for built in cmds
	if(!strncmp(cmd,c1,3) || !strncmp(cmd,c2,4) || !strncmp(cmd,c3,2) || !strncmp(cmd,c4,2) || !strncmp(cmd,c5,5) || !strncmp(cmd,c7,5) || !strncmp(cmd,c8,6) || !strncmp(cmd,c9,8) || !strncmp(cmd,c10,4) || !strncmp(cmd,c11,4) || !strncmp(cmd,c12,8) || !strncmp(cmd,c13,4) || !strncmp(cmd,c14,2) || !strncmp(cmd,c15,2))
		{
            builtin_cmd();
            return 1;
        }

	//remindme
	else if(!strncmp(cmd,c6,8))
	{
		int ll;
		//managing bg process if &
		if(cmd[strlen(cmd)-1]=='&')
			cmd[strlen(cmd)-1]='\0';
		for(ll=strlen(cmd)-1;cmd[ll]==9 || cmd[ll]==32;ll--);
		cmd[ll+1]='\0';

		if(!strcmp(cmd,c6))
			printf("no arguments given\n");
		else
			reminder();
        
        return 1;
	}
	else
	{
    	return 0;
	}
}