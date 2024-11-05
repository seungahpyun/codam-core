#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	*line;
	int		i;
	
	i = 0;
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	while (i < 10 && (line = get_next_line(fd)) != NULL)
	{
		printf("Line %d: %s", i + 1, line);
		free(line);
		i++;
	}
	if (close(fd) == -1)
	{
		perror("Error closing file");
		return (1);
	}
	return (0);
}
