/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 00:21:42 by cmarguer          #+#    #+#             */
/*   Updated: 2021/02/28 16:24:19 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# define BUFFER_SIZE 100 //нужен ли?

int			get_next_line(int fd, char **line);
char		*ft_strdup2(const char *s1);
char		*ft_strjoin2(char const *s1, char const *s2);
char		*ft_substr2(char const *s, unsigned int start, size_t len);
size_t		ft_strlen2(const char *str);
char		*ft_strchr2(const char *s, int c);

#endif
