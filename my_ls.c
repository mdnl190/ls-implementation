#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#include "my_ls.h"

char* sperm (char* temp, int mode)
{
	strcpy (temp, "-rwxrwxrwx");
	for (int c = 1, t = 256; c < 10; t/=2, ++c)
		if ((mode & t) == 0) temp[c] = '-';
	return temp;
}

void print (struct stat buf, struct dirent *de, char* filename)
{
	struct passwd  *pwd;
	struct group   *grp; 
	struct tm      *tm = localtime(&buf.st_mtime);
	char   temp[500];
	char   perm[15];

	strftime(temp, sizeof(temp), nl_langinfo(D_T_FMT), tm);

	printf("%s\n\t%10.10s %lu ", filename, sperm(perm, buf.st_mode), buf.st_nlink);

	((pwd = getpwuid(buf.st_uid)) != NULL) ? printf("%-8.8s ", pwd->pw_name) :
		printf("%-8d ", buf.st_uid);

	((grp = getgrgid(buf.st_gid)) != NULL) ? printf("%-8.8s ", grp->gr_name) :
		printf("%-8d ", buf.st_gid);

	printf("%9jd %s %s\n\n", (intmax_t)buf.st_size, temp, de->d_name);
}

void checkDir (struct dirent *de, char* filename)
{
	struct stat buf;
	char temp[1000];
	sprintf(temp, "%s/%s", filename, de->d_name);
	stat(temp, &buf);
	(S_ISDIR(buf.st_mode)) ? do_ls(temp) : print(buf, de, temp);
}

void do_ls (char* file)
{
	DIR* mydir = opendir (file);
	struct dirent *myfile;

	if (mydir == NULL) return;
	while ((myfile = readdir(mydir)) != NULL)
	{
		if (strcmp(myfile->d_name, ".") == 0 || 
			strcmp(myfile->d_name, "..") == 0)
			continue;
		checkDir(myfile, file);		
	}

	closedir(mydir);
}
