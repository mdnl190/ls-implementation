#include "my_ls.h"

int main (int argC, char* argV[])
{
	if (argC >= 2)
		do_ls (argV[1]);
	else
		do_ls((char *)".");
	return 0;
}
