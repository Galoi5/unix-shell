#include "type.h"
#include <string.h>
#include <unistd.h>

void _is_shell_builtin(char *cmd)
{
	printf("%s is a shell builtin\n", cmd);
}

void _not_found(char *cmd)
{
	printf("%s: not found\n", cmd);
}

void _type(char **args)
{
	int i = 1;
	while (args[i] != NULL) {
		if (strcmp(args[i], "exit") == 0) {
			_is_shell_builtin(args[i]);
		}
		else if (strcmp(args[i], "echo") == 0) {
			_is_shell_builtin(args[i]);
		}
		else if (strcmp(args[i], "type") == 0) {
			_is_shell_builtin(args[i]);
		}
		else if (strcmp(args[i], "pwd") == 0) {
			_is_shell_builtin(args[i]);
		}
		else {
			char *path = strdup(getenv("PATH"));
			if (path != NULL) {
				char *dir = strtok(path, ":");
				int found = 0;
				while (dir != NULL && !found) {
					char full_path[MAX_COMMAND_LENGTH];
					snprintf(full_path, sizeof(full_path), "%s/%s", dir, args[i]);
					if (access(full_path, X_OK) == 0) {
						printf("%s is %s\n", args[i], full_path);
						found = 1;
					}
					dir = strtok(NULL, ":");
				}
				if (!found) {
					_not_found(args[i]);
				}
				free(path);
			} else {
				_not_found(args[i]);
			}
		}
		i++;
	}
}

