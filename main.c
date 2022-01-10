#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	char *line;
	int fd;
	if (argc != 2)
	{
		printf("Please provide a file path when running");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		printf("%s", line);
		free(line);
	}
	close(fd);
}
/*
int main(int argc, char **argv)
{
	if (argc != 2)
		return(printf("CRASH\n"));
	printf("path is : %s", argv[1]);
	int fd1 = open("test.txt", O_RDONLY);
	int fd2 = open("get_next_line.c", O_RDONLY);
	int fd3 = open(argv[1], O_RDONLY);
	read_n_line(fd1, 1);
	read_n_line(fd2, 5);
	read_n_line(fd1, 1);
	read_n_line(fd1, 1);
	return (0);
}
*/
