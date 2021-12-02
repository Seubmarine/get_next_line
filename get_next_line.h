/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:06:28 by tbousque          #+#    #+#             */
/*   Updated: 2021/12/02 00:18:57 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# define BUFFER_SIZE 32

typedef struct s_list
{
	void		*content;
	struct s_list	*next;
}	t_list;

typedef struct s_line
{
	int	fd;
	char	*data;
}	t_line;

char	*get_next_line(int fd);
#endif