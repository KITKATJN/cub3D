/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 12:31:07 by cmarguer          #+#    #+#             */
/*   Updated: 2020/11/12 19:47:22 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[0] != '\0')
	{
		while (i < len && haystack[i] != '\0')
		{
			if (needle[0] == haystack[i])
			{
				j = 1;
				while (needle[j] == haystack[i + j] && needle[j] != '\0'
						&& (i + j) < len)
					j++;
				if (needle[j] == '\0')
					return ((char*)&haystack[i]);
			}
			i++;
		}
		return (0);
	}
	return ((char*)(haystack));
}
