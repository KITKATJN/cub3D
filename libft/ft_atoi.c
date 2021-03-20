/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 07:19:14 by cmarguer          #+#    #+#             */
/*   Updated: 2020/11/12 07:21:48 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	long	j;
	int		minus;
	int		c1;

	i = 0;
	j = 0;
	minus = 1;
	c1 = -1;
	while (nptr[i] == ' ' || nptr[i] == '	' || nptr[i] == '\n'
			|| nptr[i] == '\t' || nptr[i] == '\f' ||
			nptr[i] == '\r' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			minus = (-1);
	if (nptr[i] == 0)
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		j = (j * 10) + (nptr[i++] - 48);
		if (++c1 > 4)
			return (-1);
	}
	return ((int)(j * minus));
}
