/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 08:07:53 by cmarguer          #+#    #+#             */
/*   Updated: 2020/11/12 18:47:29 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	c_words(char const *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	left;

	i = 0;
	left = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && left > 0)
		{
			left = 0;
			count++;
		}
		if (s[i] != c)
		{
			left++;
		}
		i++;
	}
	if (left > 0)
		count++;
	return (count);
}

static	char	**my_free(char **s, size_t i)
{
	size_t j;

	j = 0;
	if (s)
	{
		while (j < i)
		{
			free(s[j]);
			j++;
		}
		free(s);
	}
	return (s);
}

char			**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;
	size_t	left;

	if (!s)
		return (0);
	str = (char**)malloc(sizeof(char*) * (c_words(s, c) + 1));
	if (str)
	{
		i = 0;
		j = 0;
		while (j < c_words(s, c))
		{
			while (s[i] == c)
				i++;
			left = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			if (!(str[j++] = ft_substr(s, left, i - left)))
				return (my_free(str, i));
		}
		str[j] = 0;
	}
	return (str);
}
