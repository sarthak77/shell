#include "declarations.h"

int main()
{
	//initialize
	homeflag=1;
	maxbg=0;
	remindflag=0;
	pipein=dup(0);
	pipeout=dup(1);

	//built in commands
	strcpy(c1,"pwd");
	strcpy(c2,"echo ");
	strcpy(c3,"cd ");
	strcpy(c4,"ls");
	strcpy(c5,"pinfo");
	strcpy(c6,"remindme");
	strcpy(c7,"clock");
	strcpy(c8,"setenv");
	strcpy(c9,"unsetenv");
	strcpy(c10,"jobs");
	strcpy(c11,"kjob");
	strcpy(c12,"overkill");
	strcpy(c13,"quit");
	strcpy(c14,"fg");
	strcpy(c15,"bg");


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
		pipecheck=0;
		pipedes=0;
		intermediatepipe=0;
		//pid=0;/////////////////////////
		builtinredirecterror=0;
		
		
		in1=0;
		out1=0;
		out2=0;
		in1i=0;
		out1i=0;
		out2i=0;
		doubleredirect=0;

		char a='z';
		
		//ctrl+c
		signal(SIGINT,sigintHandler);
		//ctrl+z
		signal(SIGTSTP,sigstpHandler);
		//ctrl+'\'
		signal(SIGQUIT,sigqHandler);

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
			pipecheck=0;
			pipedes=0;
			intermediatepipe=0;
			//pid=0;/////////////////////////
			builtinredirecterror=0;
			
			in1=0;
			out1=0;
			out2=0;
			in1i=0;
			out1i=0;
			out2i=0;
			doubleredirect=0;


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

			//if(!builtin_check())
			//{
				pipefunc();
			//}
			cmdc--;
		}

		////////////////////////////////////////////////////////////////

	}
	return 0;
}
