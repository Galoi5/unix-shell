#include "shell.h"

void	shell_exec(char **args)
{
	
}

char	**shell_split(char *line)
{
	char	**tokens;
	unsigned int 	pos;
	size_t	buffsize;

	buffsize = BUFSIZ;
	tokens = _w_malloc(BUFSIZ * sizeof(tokens));
	for (char *token =  strtok(line, DEL); token; token = strtok(NULL, DEL))
	{
		tokens[pos++] = token;
		if (pos >= buffsize)
		{
			buffsize *= 2;
			tokens = _w_realloc(tokens, buffsize * sizeof(tokens));
		}
	}
	tokens[pos] = NULL;
	return (tokens);
}	

char	*shell_read_line()
{
	char	*buffer;
	size_t	buffsize;
	char	cwd[BUFSIZ];

	buffer = NULL;

	_getcwd(cwd, sizeof(cwd));
	printf(CYAN"%s"RESET" $>", cwd);
	if (getline(&buffer, &buffsize, stdin) == -1)
	{
		free(buffer);
		buffer = NULL;
		if (feof(stdin))
			printf(RED"EOF."RESET);
		else
			printf(RED"GET LINE FAILED."RESET);
	}
	return (buffer);
}

int	main()
{
	char	*line;
	char	**args;

	// Read -> Evaluate -> Print -> Loop
	while (line = shell_read_line())
	{
		args = shell_split(line);
		
		shell_exec(args);

		free(line);
		free(args);
	}

	return (EXIT_SUCCESS);
}
