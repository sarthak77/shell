#include "declarations.h"

int main()
{
	//initialize
	homeflag=1;
	maxbg=0;
	remindflag=0;

	//built in commands
	strcpy(c1,"pwd");
	strcpy(c2,"echo ");
	strcpy(c3,"cd ");
	strcpy(c4,"ls");
	strcpy(c5,"pinfo");
	strcpy(c6,"remindme");
	strcpy(c7,"clock");

	int i,j,flag,pointer;

	while(1)
	{
		/////////////////////take input////////////////////////////////

		flag=0;//for removing front space
		pointer=0;//for storing commands
		remindflag=0;//for reminder
		remindmsg[0]='\0';//for reminder msg
		j=0;
		cmdc=0;

		char a='z';
		prompt();

		//get input
		while(a!=10)
		{
			a=getc(stdin);
			if(a==10)
				break;

			tcs[pointer]=a;
			pointer++;
		}
		tcs[pointer]='\0';
		//printf("%s\n",tcs);
		
		/////////////////////////////////////////////////////////////////

		////////////////tokenising and storing///////////////////////////

		tempcmd=strtok(tcs,";");

		while(tempcmd!=NULL)
		{
			cmdstorage[cmdc]=tempcmd;
			tempcmd=strtok(NULL,";");
			cmdc++;
		}

		////////////////////////////////////////////////////////////////

		///////////executing all commands given in one input////////////

		cmdc--;
		while(cmdstorage[cmdc]!=NULL)
		{
			//initial conditions
			remindflag=0;
			remindmsg[0]='\0';
			flag=0;
			pointer=0;
			j=0;

			strcpy(cmd,cmdstorage[cmdc]);//for uniformity

			//remove front space
			for(i=0;i<strlen(cmd);i++)
			{
				if(flag==0)
				{
					if(cmd[i]!=32 && cmd[i]!=9)
					{
						cmd[j++]=cmd[i];
						flag=1;
					}
				}
				else
					cmd[j++]=cmd[i];
			}
			cmd[j]='\0';

			//remove backward space
			for(i=j-1;cmd[i]==9 || cmd[i]==32;i--);
			cmd[i+1]='\0';

			//check for built in cmds
			if(!strncmp(cmd,c1,3) || !strncmp(cmd,c2,4) || !strncmp(cmd,c3,2) || !strncmp(cmd,c4,2) || !strncmp(cmd,c5,5) || !strncmp(cmd,c7,5))
				builtin_cmd();

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
			}

			//not built in cmds
			else
			{
				process_cmd();
				execute();
				free(buf);
			}
			cmdc--;
		}

		////////////////////////////////////////////////////////////////

	}
	return 0;
}
