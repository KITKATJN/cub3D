/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 00:20:27 by cmarguer          #+#    #+#             */
/*   Updated: 2021/02/28 16:19:49 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			ft_gnl(char **remainder, char **line, int fd, int j)
{
	char	*str;

	if (ft_strchr2(remainder[fd], '\n'))
	{
		while (remainder[fd][j] != '\n')
			j++;
		*line = ft_substr2(remainder[fd], 0, j);
		str = ft_substr2(remainder[fd], j + 1, ft_strlen2(remainder[fd]));
		free(remainder[fd]);
		remainder[fd] = str;
	}
	else
	{
		*line = ft_strdup2(remainder[fd]);
		free(remainder[fd]);
		remainder[fd] = 0;
		return (0);
	}
	return (1);
}

static char			*ft_ilovenorm(char **remainder, char *buffer, int fd)
{
	if (!remainder[fd])
		return (ft_strdup2(buffer));
	else
		return (ft_strjoin2(remainder[fd], buffer));
}

int					get_next_line(int fd, char **line)
{
	static char		*remainder[65535];
	char			buffer[BUFFER_SIZE + 1];
	char			*str;
	int				j;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	while ((j = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[j] = '\0';
		str = ft_ilovenorm(remainder, buffer, fd);
		free(remainder[fd]);
		remainder[fd] = str;
		if (ft_strchr2(buffer, '\n'))
			break ;
	}
	if (j < 0)
		return (-1);
	else if (j == 0 && (!remainder[fd] || remainder[fd][0] == '\0'))
	{
		*line = ft_strdup2("\0");
		return (0);
	}
	return (ft_gnl(remainder, line, fd, 0));
}
