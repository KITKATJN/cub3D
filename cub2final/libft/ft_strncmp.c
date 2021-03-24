/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:46:43 by cmarguer          #+#    #+#             */
/*   Updated: 2020/11/12 11:22:01 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if ((s1[0] == 0 && s2[0] == 0) || n == 0)
		return (0);
	else if (s1[0] != 0 && s2[0] == 0)
		return ((unsigned char)s1[0] - (unsigned char)s2[0]);
	else if (s1[0] == 0 && s2[0] != 0)
		return ((unsigned char)s1[0] - (unsigned char)s2[0]);
	while (i < n && ((s1[i] != '\0')))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s1[i] == 0 && s2[i] != 0 && i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
