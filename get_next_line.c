/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 00:31:10 by tbousque          #+#    #+#             */
/*   Updated: 2021/12/02 03:58:55 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	const char	*s_ptr;

	s_ptr = s;
	while (*s++)
		;
	return ((size_t)(s - s_ptr - 1));
}
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while(s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	s1len;
	size_t	s2len;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = malloc(sizeof(char) * (s1len + s2len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < s1len)
	{
		str[i] = s1[i];
		i++;
	}
	while (i - s1len < s2len)
	{
		str[i] = s2[i - s1len];
		i++;
	}
	str[i] = '\0';
	return (str);
}

#include <string.h>
char	*verify_new_line(char **p_buf)
{
	char	*newline_location;
	char	*buf;
	char	*readed;
	char	*new_buf;

	buf = *p_buf;
	newline_location = strchr(buf, '\n');
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
		if (strchr(buf, '\n'))
		{
			readed = verify_new_line(&saved_buf[fd]);
			return (readed);
		}
	}
}

#include <stdio.h>
#include <fcntl.h>
int main(void)
{
	char *str;

	int fd1 = open("test.txt", O_RDONLY);
	int i = 0;

	while (i < 6)
	{
		str = get_next_line(fd1);
		if (str)
			printf("%s", str);
		free(str);
		i++;
	}
	//int fd2 = open("get_next_line.c", O_RDONLY);
	//str = get_next_line(fd2);
	//printf("%s", str);
	//free (str);
	return (0);
}