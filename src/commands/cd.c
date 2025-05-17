#include "cd.h"

void _cd(char **args)
{
	if (args[1][0] == '~') {
		char *home = getenv("HOME");
		if (home != NULL) {
			char *new_dir = malloc(strlen(home) + strlen(args[1]));
			strcpy(new_dir, home);
			strcat(new_dir, args[1] + 1);
			if (chdir(new_dir) == -1) {
				printf("cd: %s: No such file or directory\n", args[1]);
			}
			free(new_dir);
		}
	}
	else if (chdir(args[1]) == -1) {
		printf("cd: %s: No such file or directory\n", args[1]);
	}
}
