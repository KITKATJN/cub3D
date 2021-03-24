/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:24:37 by cmarguer          #+#    #+#             */
/*   Updated: 2020/11/12 08:09:59 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char*)malloc(ft_strlen((char*)s1) + 1);
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
