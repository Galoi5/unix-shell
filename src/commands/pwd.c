#include "pwd.h"

void _pwd()
{
	char *cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
}