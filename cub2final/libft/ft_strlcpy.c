/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:35:57 by cmarguer          #+#    #+#             */
/*   Updated: 2020/11/12 08:14:25 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	if (dst == 0 || src == 0)
		return (0);
	if (size == 0)
		return (ft_strlen((char*)src));
	if (ft_strlen((char*)src) < size)
	{
		ft_memcpy(dst, src, ft_strlen((char*)src));
		dst[ft_strlen((char*)src)] = '\0';
	}
	else
	{
		ft_memcpy(dst, src, size);
		dst[size - 1] = '\0';
	}
	return (ft_strlen((char*)src));
}
