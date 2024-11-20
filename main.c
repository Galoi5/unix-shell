#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	char	*argv[] = {"ls", "-l", "-h", "-a", NULL};

	execvp(argv[0], argv);
	return (EXIT_SUCCESS);
}
