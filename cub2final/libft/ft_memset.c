/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:16:40 by cmarguer          #+#    #+#             */
/*   Updated: 2020/10/29 12:30:15 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memset(void *dest, int c, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = dest;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return (str);
}
