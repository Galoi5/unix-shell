#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 1024

void handle_echo(char *input) { printf("%s\n", input + 5); }

void handle_exit(char *input)
{
	if (atoi(input + 5) == 0)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}

void handle_pwd(char *input)
{
	char *cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
}

void handle_cd(char *input)
{
	char *dir = strdup(input + 3);
  if (dir[0] == '~') {
    char *home_dir = getenv("HOME");
    if (home_dir != NULL) {
      char *new_dir = malloc(strlen(home_dir) + strlen(dir));
      strcpy(new_dir, home_dir);
      strcat(new_dir, dir + 1);
      if (chdir(new_dir) == -1) {
        printf("cd: %s: No such file or directory\n", dir);
      }
      free(new_dir);
    }
  }
	else if (chdir(dir) == -1) {
		printf("cd: %s: No such file or directory\n", dir);
	}
	free(dir);
}

void handle_type(char *input)
{
	char *command = strdup(input + 5);
	if (strcmp(command, "exit") == 0 
  || strcmp(command, "type") == 0 
  || strcmp(command, "echo") == 0
  || strcmp(command, "pwd") == 0
  || strcmp(command, "cd") == 0) {
		printf("%s is a shell builtin\n", command);
		return;
	}

	char *path = strdup(getenv("PATH"));
	if (path != NULL) {
		char *dir = strtok(path, ":");
		while (dir != NULL) {
			char full_path[MAX_COMMAND_LENGTH];
			snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
			if (access(full_path, X_OK) == 0) {
				printf("%s is %s\n", command, full_path);
				free(path);
				return;
			}
			dir = strtok(NULL, ":");
		}
		free(path);
	}

	printf("%s: not found\n", command);
}

int exec_handler(char *input)
{
	char *command = strdup(input);
	char *args[MAX_COMMAND_LENGTH];
	int arg_count = 0;

	char *token = strtok(command, " ");
	while (token != NULL && arg_count < MAX_COMMAND_LENGTH - 1) {
		args[arg_count++] = token;
		token			  = strtok(NULL, " ");
	}
	args[arg_count] = NULL;
	if (access(args[0], X_OK) == 0) {
		if (fork() == 0) {
			execvp(args[0], args);
			exit(EXIT_FAILURE);
		}
		wait(NULL);
		free(command);
		return (1);
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
				free(command);
				return (1);
			}
			dir = strtok(NULL, ":");
		}
		free(path);
	}
	free(command);
	return (0);
}


void command_handler(char *input)
{
	if (strncmp(input, "echo ", 5) == 0) {
		handle_echo(input);
	} else if (strncmp(input, "exit ", 5) == 0) {
		handle_exit(input);
	} else if (strncmp(input, "type ", 5) == 0) {
		handle_type(input);
	} else if (strncmp(input, "pwd", 3) == 0) {
		handle_pwd(input);
	} else if (strncmp(input, "cd", 2) == 0) {
		handle_cd(input);
	} else {
		if (exec_handler(input))
			return;
		printf("%s: command not found\n", input);
	}
}

int main(int argc, char *argv[])
{
	// flush stdout
	setbuf(stdout, NULL);
	printf("$ ");

	char input[MAX_COMMAND_LENGTH];

	while (fgets(input, MAX_COMMAND_LENGTH, stdin) != NULL) {
		input[strcspn(input, "\n")] = 0;
		command_handler(input);
		printf("$ ");
	}
	return (EXIT_SUCCESS);
}
