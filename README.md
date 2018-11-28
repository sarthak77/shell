## File_Structure

├── bgprocexecute.c
├── bg_proc_initialize.c
├── builtin_check.c
├── builtin_cmd.c
├── clk.c
├── declarations.h
├── execute.c
├── ls_la.c
├── main.c
├── Makefile
├── pipe.c
├── print_perms.c
├── processbuilt_cmd.c
├── process_cmd.c
├── prompt.c
├── README.md
├── redirectioncheck.c
├── reminder.c
└── sighand.c

0 directories, 19 files

## FILES

# bg_proc_initialize.c
- stores multiple bg processes

# bgprocexecute.c
- manages printing of info related to bg processes

# builtin_cmd.c
- manages builtin commands

# clk.c
- manages clock command

# execute.c
- for executing non builtin commands using execvp

# ls_la.c
- manages ls command

# print_perms.c
- prints permissions in ls -l command

# process_cmd.c
- preprocess the command before giving it to execvp

# prompt.c
- prints prompt

# reminder.c
- manages reminder command

# builtin_check.c
- checks if built in cmd or not 

# processbuilt_cmd.c
- pre process built in command before executing

# redirectioncheck.c
- manages redirection

# sighand.c
- functions for signal handling

# pipe.c
- manages piped processes

# main.c
- contains int main

# declarations.h
- contains global variables and declarations of functions

# Makefile
- compiles all

## CODE
- comments everywhere for easy understanding of code.


