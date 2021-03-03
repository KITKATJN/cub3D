/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:10:49 by cmarguer          #+#    #+#             */
/*   Updated: 2020/11/12 08:05:24 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dest;
	unsigned const char	*sor;
	size_t				i;

	dest = (unsigned char*)dst;
	sor = (unsigned char*)src;
	i = 0;
	if (src == 0 && dst == 0)
		return (dst);
	while (i < n)
	{
		dest[i] = sor[i];
		i++;
	}
	return (dst);
}
