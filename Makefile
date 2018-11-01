cshell : bgprocexecute.o bg_proc_initialize.o builtin_cmd.o clk.o execute.o ls_la.o main.o print_perms.o process_cmd.o prompt.o reminder.o
	gcc $^ -o cshell

bgprocexecute.o : bgprocexecute.c
	gcc -c bgprocexecute.c

bg_proc_initialize.o : bg_proc_initialize.c
	gcc -c bg_proc_initialize.c

builtin_cmd.o : builtin_cmd.c
	gcc -c builtin_cmd.c

clk.o : clk.c
	gcc -c clk.c

execute.o : execute.c
	gcc -c execute.c

ls_la.o : ls_la.c
	gcc -c ls_la.c

main.o : main.c
	gcc -c main.c

print_perms.o : print_perms.c
	gcc -c print_perms.c

process_cmd.o : process_cmd.c
	gcc -c process_cmd.c

prompt.o : prompt.c
	gcc -c prompt.c

reminder.o : reminder.c
	gcc -c reminder.c

clean : 
	rm -f bgprocexecute.o bg_proc_initialize.o builtin_cmd.o clk.o execute.o ls_la.o main.o print_perms.o process_cmd.o prompt.o reminder.o cshell
