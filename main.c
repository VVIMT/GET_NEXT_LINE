#include "get_next_line.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	int		x;
	int		fd;
	char	*line;

	if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
	x = 1;
	while (x == 1)
	{
		x = get_next_line(fd, &line);
		printf("%s\n", line);
		free(line);
	}
	if (argc == 2)
		close(fd);
}
