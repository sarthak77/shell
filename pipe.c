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

void pipefunc()
{
    strcpy(pipecmd,cmd);
    int pipepoint=0;

    char*t=strtok(pipecmd,"|");
    while(t!=NULL)
    {
        pipecmdstorage[pipepoint]=t;
        t=strtok(NULL,"|");
        pipepoint++;
    }
    pipecmdstorage[pipepoint]=NULL;

    pipecheck=pipepoint;//checks if pipe or not(no of commands)
    pipepoint=0;
    //printf("%d\n",pipecheck);
 
    if(pipecheck==1)//no pipe then normal code
    {
        strcpy(cmd,pipecmdstorage[pipepoint]);
    	if(!strncmp(cmd,c1,3) || !strncmp(cmd,c2,4) || !strncmp(cmd,c3,2) || !strncmp(cmd,c4,2) || !strncmp(cmd,c5,5) || !strncmp(cmd,c7,5) || !strncmp(cmd,c6,8) || !strncmp(cmd,c8,6) || !strncmp(cmd,c9,8) || !strncmp(cmd,c10,4) || !strncmp(cmd,c11,4) || !strncmp(cmd,c12,8) || !strncmp(cmd,c13,4) || !strncmp(cmd,c14,2) || !strncmp(cmd,c15,2))
        {
            processbuilt_cmd();
            redirectioncheck();
            
            if(!builtinredirecterror)
                builtin_check();
        }
        else
        {
            process_cmd();
            execute();
            free(buf);
        }
    }
    else//if pipe then::
    {
        if(pipe(fd) != 0)
			perror("pipe failed");
        
        pid_t one =fork();
        if(one==0)
        {
            dup2(fd[1],1);
            close(fd[0]);
            
            strcpy(cmd,pipecmdstorage[pipepoint]);


            if(!strncmp(cmd,c1,3) || !strncmp(cmd,c2,4) || !strncmp(cmd,c3,2) || !strncmp(cmd,c4,2) || !strncmp(cmd,c5,5) || !strncmp(cmd,c7,5) || !strncmp(cmd,c6,8) || !strncmp(cmd,c8,6) || !strncmp(cmd,c9,8) || !strncmp(cmd,c10,4) || !strncmp(cmd,c11,4) || !strncmp(cmd,c12,8) || !strncmp(cmd,c13,4) || !strncmp(cmd,c14,2) || !strncmp(cmd,c15,2))
            {
                processbuilt_cmd();
                redirectioncheck();
                builtin_check();
            exit(3);

            }
            else
            {
                process_cmd();
                redirectioncheck();
                if(execvp(buf[0],buf)==-1)//-1 if failed
				    printf("%s: command not found\n",buf[0]);
                free(buf);
            }

        }
        else
        {   
            wait(NULL);
            close(fd[1]);
            pid_t two=fork();
            
            if(two==0)
            {
                dup2(fd[0],0);
                close(fd[0]);
                close(fd[1]);
                dup2(pipeout,1);
                free(buf);
                strcpy(cmd,pipecmdstorage[pipepoint+1]);

                if(!strncmp(cmd,c1,3) || !strncmp(cmd,c2,4) || !strncmp(cmd,c3,2) || !strncmp(cmd,c4,2) || !strncmp(cmd,c5,5) || !strncmp(cmd,c7,5) || !strncmp(cmd,c6,8) || !strncmp(cmd,c8,6) || !strncmp(cmd,c9,8) || !strncmp(cmd,c10,4) || !strncmp(cmd,c11,4) || !strncmp(cmd,c12,8) || !strncmp(cmd,c13,4) || !strncmp(cmd,c14,2) || !strncmp(cmd,c15,2))
                {
                    processbuilt_cmd();
                    redirectioncheck();
                    builtin_check();
                }
                else
                {
                    process_cmd();
                    redirectioncheck();
                        if(execvp(buf[0],buf)==-1)//-1 if failed
                            printf("%s: command not found\n",buf[0]);
                            
                }
            }
            else
            {
                wait(NULL);
            }
        }

    }
    //printf("finish\n");
}