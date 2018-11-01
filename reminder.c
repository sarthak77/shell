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

int reminder()
{
	if(!strncmp(cmd,"remindme ",9))
	{
		remindflag=1;
		char* r;//for token
		r=strtok(cmd," ,	");
		r=strtok(NULL," ,	");//r=2nd argument

		//checks 2nd arg is int or not
		int no=0;
		for(int i=0;i<strlen(r);i++)
		{
			if(r[i]>47 && r[i]<58)
				no=1;
			else
			{
				no=0;
				break;
			}
		}

		if(no)
		{
			char re[100];
			strcpy(re,"sleep");
			sprintf(re,"%s %s &",re,r);//form sleep command with &
			strcpy(cmd,re);

			//copy msg
			r=strtok(NULL," ,	");//3rd argument
			if(r==NULL)
			{
				printf("provide reminder msg\n");
				return 0;
			}
			else
			{
				strcpy(remindmsg,r);
				//printf("%s\n\n",remindmsg);
				r=strtok(NULL," ,	");
				while(r!=NULL)
				{
					strcat(remindmsg," ");
					strcat(remindmsg,r);
					r=strtok(NULL," ,	");
				}
				//printf("%s\n",remindmsg);
				//printf("%s\n",cmd);
				process_cmd();
				execute();
				//free(buf);
			}
		}
		else
		{
			printf("argument expected to be int\n");
			return 0;
		}
		free(r);
	}
	else
	{
		printf("no arguments given\n");
		return 0;
	}
	return 0;
}