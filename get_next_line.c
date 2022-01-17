/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 22:09:12 by tbousque          #+#    #+#             */
/*   Updated: 2022/01/17 22:21:09 by tbousque         ###   ########.fr       */
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
		return (readed);
	}
	return (NULL);
}

char	*eof_or_error(char **saved_buf, int fd, char *buf_of_read)
{
	char	*readed;

	readed = NULL;
	if (ft_strlen(saved_buf[fd]))
		readed = ft_strdup(saved_buf[fd]);
	free(saved_buf[fd]);
	saved_buf[fd] = NULL;
	free(buf_of_read);
	return (readed);
}

char	*join_until_newline(char **saved_buf, char *buf, int fd, char *readed)
{
	ssize_t	n_read;

	while (1)
	{
		n_read = read(fd, buf, BUFFER_SIZE);
		if (n_read == 0 || n_read == -1)
			return (eof_or_error(saved_buf, fd, buf));
		buf[n_read] = '\0';
		readed = ft_strjoin(saved_buf[fd], buf);
		free(saved_buf[fd]);
		saved_buf[fd] = readed;
		if (ft_strchr(buf, '\n'))
		{
			readed = verify_new_line(&saved_buf[fd]);
			free(buf);
			return (readed);
		}
	}
}

char	*get_next_line(int fd)
{
	static char	*saved_buf[20000];
	char		*buf;
	char		*readed;

	if (fd < 0)
		return (NULL);
	if (!saved_buf[fd])
		saved_buf[fd] = ft_strdup("");
	readed = verify_new_line(&saved_buf[fd]);
	if (readed)
		return (readed);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	return (join_until_newline(saved_buf, buf, fd, readed));
}
