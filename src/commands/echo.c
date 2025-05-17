#include "echo.h"

void _echo(char **args)
{
	args++;
	while (*args != NULL) {
		printf("%s ", *args);
		args++;
	}
	printf("\n");
}