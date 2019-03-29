#ifndef my_ls_h
#define my_ls_h

#include <dirent.h>
#include <sys/stat.h>

char* sperm (char*, int);
void print (struct stat, struct dirent*, char*); 
void checkDir (struct dirent*, char*);
void do_ls (char*);

#endif
