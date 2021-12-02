/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 00:31:10 by tbousque          #+#    #+#             */
/*   Updated: 2021/12/02 15:24:41 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*verify_new_line(char **p_buf)
{
	char	*newline_location;
	char	*buf;
	char	*readed;
	char	*new_buf;

	buf = *p_buf;
	newline_location = ft_strchr(buf, '\n');
	if (newline_location)
	{
		new_buf = ft_strdup(newline_location + 1);
		newline_location[1] = '\0';
		readed = ft_strdup(buf);
		free(buf);
		buf = new_buf;
		*p_buf = buf;
		return(readed);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*saved_buf[_SC_OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	ssize_t		n_read;
	char		*readed;
	
	if (!saved_buf[fd])
		saved_buf[fd] = ft_strdup("");
	readed = verify_new_line(&saved_buf[fd]);
	if (readed)
		return (readed);
	while (1)
	{
		n_read = read(fd, buf, BUFFER_SIZE);
		if (n_read == 0)
		{
			readed = NULL;
			if (ft_strlen(saved_buf[fd]))
				readed = ft_strdup(saved_buf[fd]);
			free(saved_buf[fd]);
			saved_buf[fd] = NULL;
			return (readed);
		}
		buf[n_read] = '\0';
		readed = ft_strjoin(saved_buf[fd], buf);
		free(saved_buf[fd]);
		saved_buf[fd] = readed;
		if (ft_strchr(buf, '\n'))
		{
			readed = verify_new_line(&saved_buf[fd]);
			return (readed);
		}
	}
}

#include <stdio.h>
void read_n_line(int fd, int n_line)
{
	char	*str;
	int i;

	i = 0;
	while (i < n_line)
	{
		str = get_next_line(fd);
		if (str)
			printf("%s", str);
		free(str);
		i++;
	}
}

#include <fcntl.h>
int main(int argc, char **argv)
{
	if (argc != 2)
		return(printf("CRASH\n"));
	printf("path is : %s", argv[1]);
	int fd1 = open("test.txt", O_RDONLY);
	int fd2 = open("get_next_line.c", O_RDONLY);
	int fd3 = open(argv[1], O_RDONLY);
	read_n_line(fd2, 15);
	read_n_line(fd1, 1);
	read_n_line(fd2, 200);
	read_n_line(fd1, 1);
	read_n_line(fd1, 1);
	read_n_line(fd3, 1000);
	read_n_line(fd2, 200);

	return (0);
}