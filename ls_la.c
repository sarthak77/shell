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

void ls_la(int typeflag)
{
	DIR * dir;//The DIR data type represents a directory stream. 
	struct dirent * file;//forming struct
	struct stat f_info;//forming stat      
	char buf[128];
	struct passwd pwent, * pwentp;//provides user info
	struct group grp, * grpt;//provides info about groups
	char datestring[256];
	struct tm time;//contains info about time

	char path[1000];
	getcwd(path,sizeof(path));
	dir = opendir(path);//open directory

	while(file=readdir(dir)) //to traverse all files
	{
		if(typeflag==2)
		{	
			stat(file->d_name, &f_info);//file name

			print_perms(f_info.st_mode);//file permisions

			printf(" %3d", (int)f_info.st_nlink);//no of links

			if (!getpwuid_r(f_info.st_uid, &pwent, buf, sizeof(buf), &pwentp))
				printf(" %10s", pwent.pw_name);//owner name
			else
				printf(" %d", f_info.st_uid);

			if (!getgrgid_r (f_info.st_gid, &grp, buf, sizeof(buf), &grpt))
				printf(" %10s", grp.gr_name);//owner group
			else
				printf(" %d", f_info.st_gid);

			printf(" %6d", (int)f_info.st_size);//file size

			localtime_r(&f_info.st_mtime, &time);
			/* Get localized date string. */
			strftime(datestring, sizeof(datestring), "%F %T", &time);
			printf(" %s %s\n", datestring, file->d_name);//date and name
		}
		else
		{
			stat(file->d_name, &f_info);//file name
			if(strncmp(file->d_name,".",1) && strncmp(file->d_name,"..",2))
			{
				print_perms(f_info.st_mode);//file permisions

				printf(" %3d", (int)f_info.st_nlink);//no of links

				if (!getpwuid_r(f_info.st_uid, &pwent, buf, sizeof(buf), &pwentp))
					printf(" %10s", pwent.pw_name);//owner name
				else
					printf(" %d", f_info.st_uid);

				if (!getgrgid_r (f_info.st_gid, &grp, buf, sizeof(buf), &grpt))
					printf(" %10s", grp.gr_name);//owner group
				else
					printf(" %d", f_info.st_gid);

				printf(" %6d", (int)f_info.st_size);//file size

				localtime_r(&f_info.st_mtime, &time);
				/* Get localized date string. */
				strftime(datestring, sizeof(datestring), "%F %T", &time);
				printf(" %s %s\n", datestring, file->d_name);//date and name

			}
		}
	}   
}