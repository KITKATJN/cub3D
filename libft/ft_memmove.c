/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:53:53 by cmarguer          #+#    #+#             */
/*   Updated: 2020/11/12 10:21:20 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dest;
	unsigned char const	*sour;
	size_t				i;

	if (dst == 0 && src == 0)
		return (dst);
	i = 0;
	sour = (unsigned const char*)src;
	dest = (unsigned char*)dst;
	if ((size_t)dest < (size_t)sour)
		while ((len--) > 0)
		{
			dest[i] = sour[i];
			i++;
		}
	else
		while (len-- > 0)
		{
			dest[len] = sour[len];
		}
	return (dst);
}
