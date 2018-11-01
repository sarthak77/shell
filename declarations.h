#ifndef declarations
#define declarations

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

//structs
typedef struct Bgproc
{
	int pid;
	int jobid;
	char command[1000];
	int flag;
}bgproc;

//variables
int homeflag;//for cd~
char homedir[1000];//stores ~
char cmd[1000],tcs[1000];//stores commands
char*tempcmd;//tokenise tcs
struct dirent **namelist;//used in ls
char**buf;//for execvp
char*cmdstorage[1000];//stores commands after tokenising with ;
int cmdc;//pointer for above
int bg;//if the cmd is in bg or not
int maxbg;//no of bg processes
bgproc a[100];//stores bg process info
int remindflag;//for reminder
char remindmsg[2000];//for storing reminder msg


//built in commands
#define S 100
char c1[S];
char c2[S];
char c3[S];
char c4[S];
char c5[S];
char c6[S];
char c7[S];

//functions
void prompt();
void builtin_cmd();
void print_perms();
void ls_la(int);
void process_cmd();
void execute();
void bg_proc_initialize(int,char*);
void bgprocexecute();
int reminder();
void clk();

#endif
