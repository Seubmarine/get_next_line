/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 00:31:10 by tbousque          #+#    #+#             */
/*   Updated: 2022/01/10 16:52:16 by tbousque         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	static char	*saved_buf[20000];
	char		*buf;
	ssize_t		n_read;
	char		*readed;

	if (!saved_buf[fd])
		saved_buf[fd] = ft_strdup("");
	readed = verify_new_line(&saved_buf[fd]);
	if (readed)
		return (readed);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (1)
	{
		n_read = read(fd, buf, BUFFER_SIZE);
		if (n_read == 0 || n_read == -1)
		{
			readed = NULL;
			if (ft_strlen(saved_buf[fd]))
				readed = ft_strdup(saved_buf[fd]);
			free(saved_buf[fd]);
			saved_buf[fd] = NULL;
			free(buf);
			return (readed);
		}
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
