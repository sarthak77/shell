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

void builtin_cmd()
{
	//printf("entered builtin func with cmd:%s\n",cmd);
	int j=2,i,space=0;

	//managing bg process for built in cmds
	if(cmd[strlen(cmd)-1]=='&')
		cmd[strlen(cmd)-1]='\0';
	for(i=strlen(cmd)-1;cmd[i]==9 || cmd[i]==32;i--);
	cmd[i+1]='\0';

	//pwd
	if(!strcmp(cmd,c1))
	{
		char b[100];
		getcwd(b,sizeof(b));
		printf("%s\n",b);
	}

	//echo
	else if(!strncmp(cmd,c2,5))
	{
		printf("%s\n",&cmd[5]);
	}

	//cd
	else if(!strncmp(cmd,c3,3))
	{

		//removing multiple spaces with single space
		for(i=2;i<strlen(cmd);i++)
		{
			if(cmd[i]==9 || cmd[i]==32)
			{
				space++;
				if(space<2)
				{
					cmd[j]=cmd[i];
					j++;
				}
			}
			else
			{
				cmd[j]=cmd[i];
				j++;
				space=0;
			}
		}
		cmd[j]='\0';
		//i and j free

		//do nothing
		if(!strcmp(cmd,"cd ."))
		{
		}
		else if(!strcmp(cmd,"cd .."))
		{
			char temp[1000];
			getcwd(temp,sizeof(temp));

			//if dir is not /c
			if(strcmp(temp,"/"))//error if directory=/
			{
				for(i=strlen(temp)-1;temp[i]!='/';i--);

				temp[i++]=47;//backslash
				temp[i]='\0';
				//printf("%s\n",temp);
				//char temp2[1000];
				chdir(temp);
			}
		}
		//i and j free
		else if(!strcmp(cmd,"cd ~"))
		{
			chdir(homedir);
		}
		else if(!strcmp(cmd,"cd "))
		{
			chdir(homedir);
		}

		else
		{
			char a[1000];
			strcpy(a,&cmd[3]);
			if(chdir(a)!=0)
				perror("ERROR");
		}
	}
	else if(!strcmp(cmd,"cd"))
	{
		chdir(homedir);
	}

	//ls
	else if(!strncmp(cmd,c4,2))
	{	
		space=0;j=2;

		//removing multiple spaces
		for(i=2;i<strlen(cmd);i++)
		{
			if(cmd[i]==9 || cmd[i]==32)
			{
				space++;
				if(space<2)
				{
					cmd[j]=cmd[i];
					j++;
				}
			}
			else
			{
				cmd[j]=cmd[i];
				j++;
				space=0;
			}
		}
		cmd[j]='\0';

		if(!strcmp(cmd,"ls"))
		{
			int nof=scandir(".",&namelist,NULL,alphasort);
			if(nof==-1)
				perror("SCANDIR");
			else
			{
				int count;
				for(count=0;count<nof;count++)
				{	
					if(strncmp(namelist[count]->d_name,".",1) && strncmp(namelist[count]->d_name,"..",2))
						printf("%s   ",namelist[count]->d_name);
				}
				printf("\n");
			}
		}
		else if(!strcmp(cmd,"ls -a"))
		{
			int nof=scandir(".",&namelist,NULL,alphasort);
			if(nof==-1)
				perror("SCANDIR");
			else
			{
				int count;
				for(count=0;count<nof;count++)
				{	
					printf("%s   ",namelist[count]->d_name);
				}
				printf("\n");
			}
		}

		//for ls -l-a ..
		else if(!strncmp(cmd,"ls -",4))
		{
			int flagl=0,flaga=0;
			if(cmd[4]==97 || cmd[4]==108)
			{
				char delimit[]="-";//for multiple delimiters
				char*token=strtok(&cmd[2],delimit);
				int tokencount=0;
				while (token != NULL) 
				{
					if(!strncmp(token,"l",1))
					{
						tokencount=1;
						flagl=1;
					}
					if(!strncmp(token,"la",2) || !strncmp(token,"al",2))
						tokencount=2;
					if(!strncmp(token,"a",1))
					{
						//tokencount=2;
						flaga=1;
					}
					//if both l and a are present
					if(flagl && flaga)
						tokencount=2;

					token = strtok(NULL, delimit);
				}
				if(tokencount==1)
					ls_la(1);
				else if(tokencount==2)
					ls_la(2);
			}
			//error in flags
			else
				printf("ls: invalid line width: '%s'\n",&cmd[5]);
		}

		//for checking permissions of other files
		else
		{
			char p[1000];
			strcpy(p,&cmd[3]);
			int nof=scandir(p,&namelist,NULL,alphasort);
			if(nof==-1)
				perror("SCANDIR");
			else
			{
				int count;
				for(count=0;count<nof;count++)
				{	
					if(strncmp(namelist[count]->d_name,".",1) && strncmp(namelist[count]->d_name,"..",2))
						printf("%s   ",namelist[count]->d_name);
				}
				printf("\n");
			}
		}
	}

	//pinfo
	else if(!strncmp(cmd,c5,5))
	{
		char present[1000];
		getcwd(present,sizeof(present));
		//for only pinfo
		if(!strcmp(cmd,c5))
		{
			pid_t shellid=getpid();
			//printf("%d\n",shellid);
			sprintf(cmd,"%s %d",cmd,shellid);
			//printf("%s\n",cmd);

		}
		if (!strncmp(cmd,"pinfo ",6))
		{
			char id[100]={'\0'};
			strcat(id,&cmd[6]);
			//printf("%s\n",id);
			if(chdir("/proc")!=0)
				perror("Cannot access /proc");
			else
			{
				if(chdir(id)!=0)
					perror("id does not exist");
				else
				{
					printf("pid:	%s\n",id);
					FILE*f=fopen("status","r");
					if(f==NULL)
					{
						printf("cannot open file\n");
					}
					else
					{
						char line[500];
						int l=0;
						while(fgets(line,sizeof line,f)!=NULL)
						{
							//state
							if(l==2)
							{
								char status[100];
								strcpy(status,line);
								printf("%s",status);
							}

							//vm
							if(l==17)
							{
								char vm[100];
								strcpy(vm,line);
								if(!strncmp(vm,"VmSize",6))
									printf("%s",vm);
								else
									printf("Error in finding virtual memory(permission denied)\n");
							}

							l++;
						}
						fclose(f);
					}
					char exepath[500]={'\0'};
					ssize_t len;
					if ((readlink("exe", exepath, sizeof(exepath)))<0)
						printf("Error in finding exe path(permission denied)\n");
					else
						printf("Executable path:	%s\n",exepath);

				}
			}
		}
		else
		{
			printf("%s: command not found\n",cmd);
		}
		chdir(present);
	}

	//clock
	else if(!strncmp(cmd,c7,5))
	{
		if(!strcmp(cmd,c7))
			printf("no arguments given\n");
		else
			clk();
	}
	
	//setenv
	else if(!strncmp(cmd,c8,6))
	{
		if(!strcmp(cmd,c8))
			printf("No arguments given\n");
		else
		{
			char *a1[10];
			int i=0;
			char*token=strtok(cmd," ,	");
			while(token!=NULL)
			{
				a1[i]=token;
				//printf("%s\n\n",a1[i]);
				token=strtok(NULL," ,	");
				i++;
			}
			//printf("%d\n",i);

			if(i==1)
				printf("No argumnets given\n");
			else if(i==2)
				setenv(a1[1],"",1);
			else if(i==3)
				setenv(a1[1],a1[2],1);
			else
				printf("More arguments given\n");

		}
	}

	//unsetenv
	else if(!strncmp(cmd,c9,8))
	{
		if(!strcmp(cmd,c9))
			printf("No arguments given");
		else
		{
			char *a1[10];
			int i=0;
			char*token=strtok(cmd," ,	");
			while(token!=NULL)
			{
				a1[i]=token;
				//printf("%s\n\n",a1[i]);
				token=strtok(NULL," ,	");
				i++;
			}
			//printf("%d\n",i);

			if(i==1)
				printf("No argumnets given\n");
			else if(i==2)
				if(getenv(a1[1])==NULL)
					printf("variable does not exist\n");
				else
					if(unsetenv(a1[1])==-1)
						perror("unset error");
			else if (i>2)
				printf("More arguments given\n");
		}
	}

	//jobs
	else if(!strcmp(cmd,c10))
	{
		int i=1;
		while(i<=maxbg)
		{
			if(a[i].state==1)
				printf("[%d]\t%s\t%s [%d]\n",a[i].jobid,a[i].status,a[i].command,a[i].pid);
			i++;
		}
	}


	//kjob
	else if(!strncmp(cmd,c11,4))
	{
		char *a1[10];
			int i=0;
			char*token=strtok(cmd," ,	");
			while(token!=NULL)
			{
				a1[i]=token;
				//printf("%s\n\n",a1[i]);
				token=strtok(NULL," ,	");
				i++;
			}
			//printf("%d\n",i);

			if(i==1)
				printf("No argumnets given\n");
			else if(i==2)
				printf("Less arguments given\n");
			else if(i==3)
			{
				int jid=atoi(a1[1]);//jobid
				int sid=atoi(a1[2]);//signalid
				
				if(jid>maxbg)
					printf("No such job found\n");
				else if(jid<1)
					printf("No such job found\n");
				else
				{
					if(a[jid].state=1)
					{
						int procid=a[jid].pid;//process id of the given job
						if(kill(procid,sid)==-1)
							perror("ERROR");
						else
						{
							a[jid].state=0;
							//maxbg--;
						}
					}
				}
			}
			else
				printf("More arguments given\n");
	}

	//overkill
	else if(!strcmp(cmd,c12))
	{
		int i;
		for(i=1;i<=maxbg && a[i].state==1;i++)
			if(kill(a[i].pid,9)==-1)
				perror("ERROR");
			else
				a[i].state=0;
		maxbg=0;

	}

	//quit
	else if(!strcmp(cmd,c13))
	{
		exit(0);
	}

	//fg
	else if(!strncmp(cmd,c14,2))
	{

		if(!strcmp(cmd,c14))
		{
			if(maxbg==0)
			{
				printf("fg: current: no such job\n");
			}
			else
			{
				if(kill(a[maxbg].pid,SIGCONT)==-1)
					perror("ERROR:");
				else
				{
					a[maxbg].state=0;
					waitpid(a[maxbg].pid,NULL,WUNTRACED);
					maxbg--;
				}
			}
		}
		else
		{
			char *a1[10];
			int i=0;
			char*token=strtok(cmd," ,	");
			while(token!=NULL)
			{
				a1[i]=token;
				//printf("%s\n\n",a1[i]);
				token=strtok(NULL," ,	");
				i++;
			}
			//printf("%d\n",i);

			if(i==1)
			{
				if(kill(a[maxbg].pid,SIGCONT)==-1)
					perror("ERROR:");
				else
				{
					a[maxbg].state=0;
					waitpid(a[maxbg].pid,NULL,WUNTRACED);
					maxbg--;
				}

			}
			else if(i==2)
			{
				if(atoi(a1[1])>maxbg)
				{
					printf("fg: %s: no such job\n",a1[1]);
				}
				for(int j=1;j<=maxbg;j++)
				{
					int x=atoi(a1[1]);//id stored in a1[1]
					//printf("%d\n",x);
					if(x==a[j].jobid)
						if(kill(a[j].pid,SIGCONT)==-1)
							perror("ERROR:");
						else
						{
							a[j].state=0;
							waitpid(a[j].pid,NULL,WUNTRACED);
							//maxbg--;
						}
				}

			}
			else if (i>2)
				printf("More arguments given\n");
		}

	}

	//bg
	else if(!strncmp(cmd,c15,2))
	{

		if(!strcmp(cmd,c15))
		{
			int i;
			for(i=maxbg;i>=1;i--)
			{
				if(!strcmp(a[i].status,"Stopped"))
				{
					if(kill(a[i].pid,SIGCONT)==-1)
						perror("ERROR");
					else
					{
						strcpy(a[i].status,"Running");
						break;
					}
				}
			}
			if(i==0)
				printf("bg: current: no such job\n");
		}
		else
		{
			char *a1[10];
			int i=0;
			char*token=strtok(cmd," ,	");
			while(token!=NULL)
			{
				a1[i]=token;
				//printf("%s\n\n",a1[i]);
				token=strtok(NULL," ,	");
				i++;
			}
			//printf("%d\n",i);

			if(i==1)
			{
				int i;
				for(i=maxbg;i>=1;i--)
				{
					if(!strcmp(a[i].status,"Stopped"))
					{
						if(kill(a[i].pid,SIGCONT)==-1)
							perror("ERROR");
						else
						{
							strcpy(a[i].status,"Running");
							break;
						}
					}
				}	
				if(i==0)
					printf("bg: current: no such job\n");
			}
			else if(i==2)
			{
				int j;
				for(j=1;j<=maxbg;j++)
				{
					int x=atoi(a1[1]);//id stored in a1[1]
					//printf("%d\n",x);
					if(x==a[j].jobid)
						if(kill(a[j].pid,SIGCONT)==-1)
							perror("ERROR:");
						else
						{
							strcpy(a[j].status,"Running");
							break;
						}
				}
				if(j==maxbg+1)
					printf("bg: %s: no such job\n",a1[1]);
			}
			else if (i>2)
				printf("More arguments given\n");
		}


	}


	//error handling for other inputs
	else
	{
		printf("%s: command not found\n",cmd);

	}

	if(in1==1)
	{
		close(in1i);
		dup2(pipein,0);
	}
	if(out1==1)
	{
		close(out1i);
		dup2(pipeout,1);
	}
	if(out2==1)
	{
		close(out2i);
		dup2(pipeout,1);
	}
}