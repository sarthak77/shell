### C-Shell
Shell built in C language with basic commands and other advanced features

### File Structure

<br>├── bgprocexecute.c
<br>├── bg_proc_initialize.c
<br>├── builtin_check.c
<br>├── builtin_cmd.c
<br>├── clk.c
<br>├── declarations.h
<br>├── execute.c
<br>├── ls_la.c
<br>├── main.c
<br>├── Makefile
<br>├── pipe.c
<br>├── print_perms.c
<br>├── processbuilt_cmd.c
<br>├── process_cmd.c
<br>├── prompt.c
<br>├── README.md
<br>├── redirectioncheck.c
<br>├── reminder.c
<br>└── sighand.c

0 directories, 19 files

### File Content

- bg_proc_initialize.c: stores multiple bg processes
- bgprocexecute.c: manages printing of info related to bg processes
- builtin_cmd.c: manages builtin commands
- clk.c: manages clock command
- execute.c: for executing non builtin commands using execvp
- ls_la.c: manages ls command
- print_perms.c: prints permissions in ls -l command
- process_cmd.c: preprocess the command before giving it to execvp
- prompt.c: prints prompt
- reminder.c: manages reminder command
- builtin_check.c: checks if built in cmd or not 
- processbuilt_cmd.c: pre process built in command before executing
- redirectioncheck.c: manages redirection
- sighand.c: functions for signal handling
- pipe.c: manages piped processes
- main.c: contains int main
- declarations.h: contains global variables and declarations of functions
- Makefile: compiles all

### CODE
- comments everywhere for easy understanding of code.
