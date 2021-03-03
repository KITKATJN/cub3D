/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 08:18:07 by cmarguer          #+#    #+#             */
/*   Updated: 2020/11/12 08:22:04 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(const char *set, int c)
{
	size_t i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	left;
	size_t	right;

	left = 0;
	if (s1 == 0 || set == 0)
		return (0);
	while (s1[left] && check_set(set, s1[left]))
		left++;
	right = ft_strlen(s1);
	while (right > left && check_set(set, s1[right - 1]))
		right--;
	str = malloc(right - left + 1);
	if (str)
	{
		i = 0;
		while (left < right)
			str[i++] = s1[left++];
		str[i] = '\0';
		return (str);
	}
	return (0);
}
