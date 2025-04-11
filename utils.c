#include "shell.h"

void	*_w_malloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
	{
		perror(RED"MALLOC FAILED"RESET);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void	*_w_realloc(void *ptr, size_t size)
{
	void	*new;

	new = realloc(ptr, size);
	if (!new && size != 0)
	{
		perror(RED"REALLOC FAILED"RESET);
		exit(EXIT_FAILURE);
	}
	return (new);
}

void	_getcwd(char *buff, size_t size)
{
	if (getcwd(buff, size) == NULL)
		perror(RED"GETCWD FAILED"RESET);
}