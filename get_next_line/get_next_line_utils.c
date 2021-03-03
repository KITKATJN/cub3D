/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 00:21:39 by cmarguer          #+#    #+#             */
/*   Updated: 2021/02/28 16:19:24 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strjoin2(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (0);
	str = malloc(ft_strlen2((char*)s1) + (ft_strlen2((char*)s2) + 1));
	if (str)
	{
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
		while (s2[j] != '\0')
		{
			str[i + j] = s2[j];
			j++;
		}
		str[i + j] = '\0';
		return (str);
	}
	return (0);
}

char		*ft_strdup2(const char *s1)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char*)malloc(ft_strlen2((char*)s1) + 1);
	if (str)
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
	else
		return (0);
	str[i] = '\0';
	return (str);
}

char		*ft_substr2(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char) * len + 1);
	if (!s)
		return (0);
	if (str)
	{
		if (start >= ft_strlen2((char*)s))
		{
			str[i] = '\0';
			return (str);
		}
		while (s[start + i] != '\0' && i < len)
		{
			str[i] = s[start + i];
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (0);
}

size_t		ft_strlen2(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != 0)
	{
		i++;
	}
	return (i);
}

char		*ft_strchr2(const char *s, int c)
{
	char	*tmp;

	while (*s)
	{
		if (*s == c)
		{
			tmp = (char*)s;
			return (tmp);
		}
		s++;
	}
	if (c == '\0')
	{
		tmp = (char*)s;
		return (tmp);
	}
	return (NULL);
}
