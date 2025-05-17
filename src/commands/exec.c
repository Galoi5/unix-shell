#include "exec.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int _exec(char **args)
{
	if (args == NULL || args[0] == NULL) {
		return 0;
	}
	if (access(args[0], X_OK) == 0) {
		if (fork() == 0) {
			execvp(args[0], args);
			exit(EXIT_FAILURE);
		}
		wait(NULL);
		return 1;
	}
	char *path = strdup(getenv("PATH"));
	if (path != NULL) {
		char *dir = strtok(path, ":");
		while (dir != NULL) {
			char full_path[MAX_COMMAND_LENGTH];
			snprintf(full_path, sizeof(full_path), "%s/%s", dir, args[0]);
			if (access(full_path, X_OK) == 0) {
				if (fork() == 0) {
					execvp(full_path, args);
					exit(EXIT_FAILURE);
				}
				wait(NULL);
				free(path);
				return 1;
			}
			dir = strtok(NULL, ":");
		}
		free(path);
	}
	return 0;
}
