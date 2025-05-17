#include "commands/utils.h"
#include "commhandler.h"

int main(int argc, char *argv[])
{
	// flush stdout
	setbuf(stdout, NULL);
	printf("$ ");

	char input[MAX_COMMAND_LENGTH];

	while (fgets(input, MAX_COMMAND_LENGTH, stdin) != NULL) {
		input[strlen(input) - 1] = '\0';
        if (commhandler(input) == -1) {
            printf("Error: %s\n", input);
            return (EXIT_FAILURE);
        }
		printf("$ ");
	}
	return (EXIT_SUCCESS);
}
