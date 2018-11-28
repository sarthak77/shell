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

void clk()
{
	int n=0,t=0;
	char clkt[100],clkn[100];
	if(!strncmp(cmd,"clock ",6))
	{
		char*token=strtok(cmd," ,	");
		while(token!=NULL)
		{
			if(!strncmp(token,"-t",2))
			{
				t=1;
				strcpy(clkt,&token[2]);
			}
			else if(!strncmp(token,"-n",2))
			{
				n=1;
				strcpy(clkn,&token[2]);
			}
			
			token=strtok(NULL," ,	");
		}

		if(!n && !t)
			printf("invalid arguments given\n");
		else if(t && !n)
			printf("duration not specified\n");
		else if(n && !t)
			printf("interval not specified\n");
		else
		{
			//check if int
			int i;
			for(i=0;i<strlen(clkt);i++)
				if(clkt[i]>47 && clkt[i]<58)
					t=1;
				else
				{
					t=0;
					break;
				}

			for(i=0;i<strlen(clkn);i++)
				if(clkn[i]>47 && clkn[i]<58)
					n=1;
				else
				{
					n=0;
					break;
				}
			
			if(n && t)
			{
				//ascii to int function
				n=atoi(clkn);
				t=atoi(clkt);
				if(t==0)
				{
					printf("ERROR: t cannot be 0\n");
				}
				else
				{
					int loopcount=(n/t)+1;
					
					while(loopcount!=0)
					{	
						//open files
						FILE*f=fopen("/sys/class/rtc/rtc0/date","r");
						FILE*g=fopen("/sys/class/rtc/rtc0/time","r");
						
						//check for errors
						if(f==NULL || g==NULL)
						{
							printf("cannot open file\n");
						}
						else
						{
							char line[200];

							//get date
							if(fgets(line,sizeof line,f)!=NULL)
							{
								char j[100];
								strcpy(j,line);
								j[strlen(j)-1]='\0';//remove \n
							}

							//get time
							if(fgets(line,sizeof line,g)!=NULL)
							{
								char j[100];
								sprintf(j,"%s %s",j,line);
								printf("%s",j);
							}
							else
								perror("ERROR");
							
							//closing files
							fclose(f);
							fclose(g);
							
							//sleep
							if(n<t)
								sleep(n);
							else
							{
								sleep(t);
								n=n-t;
							}
							loopcount--;
						}
					}
				}
			}
		}
	}
	else
		printf("%s: command not found\n",cmd);
}
