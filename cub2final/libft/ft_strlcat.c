/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:09:32 by cmarguer          #+#    #+#             */
/*   Updated: 2020/11/12 19:47:56 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t res;

	i = 0;
	res = ft_strlen(src);
	while (*dst && i < size)
	{
		dst++;
		i++;
	}
	j = i;
	if (size != 0)
	{
		while (*src && i < size - 1)
		{
			*dst = *src;
			i++;
			src++;
			dst++;
		}
	}
	if (i < size)
		*dst = '\0';
	return (j + res);
}
