#include "commhandler.h"
#include <stdlib.h>
#include <string.h>

void _too_many_args(char *cmd) { printf("%s: too many arguments\n", cmd); }

void _too_few_args(char *cmd) { printf("%s: too few arguments\n", cmd); }

void _command_not_found(char *cmd) { printf("%s: command not found\n", cmd); }

int redirect(char **args)
{
	for (int i = 0;; i++) {
		if (args[i] == NULL)
			break;
		if (strcmp(args[i], ">") == 0 || strcmp(args[i], "1>") == 0) {
			freopen(args[i + 1], "w", stdout);
			for (int j = i;; j++) {
				if (args[j] == NULL)
					break;
				free(args[j]);
			}
			args[i] = NULL;
			return 1;
		}
	}
	return 0;
}
void restorestdout() { freopen("/dev/tty", "w", stdout); }

int commhandler(char *input)
{
	if (input == NULL || input[0] == '\0') {
		return 0;
	}

	// main command handling
	char **args = argparse(input);
	if (args == NULL || args[0] == NULL) {
		return 0;
	}
	int is_redirected = redirect(args);


	int argc = 0;
	while (args[argc] != NULL)
		argc++;

	if (strcmp(args[0], "exit") == 0) {
		if (argc == 2)
			_exit(atoi(args[1]));
		else if (argc == 1)
			_exit(0);
		else
			_too_many_args(args[0]);
	} else if (strcmp(args[0], "echo") == 0) {
		_echo(args);
	} else if (strcmp(args[0], "type") == 0) {
		_type(args);
	} else if (strcmp(args[0], "pwd") == 0) {
		if (argc == 1)
			_pwd();
		else
			_too_many_args(args[0]);
	} else if (strcmp(args[0], "cd") == 0) {
		if (argc == 2)
			_cd(args);
		else
			_too_many_args(args[0]);
	} else {
		if (_exec(args) == 0)
			_command_not_found(args[0]);
	}

	// Free all allocated memory
	for (int i = 0; args[i] != NULL; i++) {
		free(args[i]);
	}
	free(args);
	if (is_redirected) {
		restorestdout();
	}
	return 0;
}