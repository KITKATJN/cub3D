/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 07:28:58 by cmarguer          #+#    #+#             */
/*   Updated: 2020/11/13 12:55:52 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_len(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static	char	*ft_witcher(int n)
{
	size_t	len;
	char	*str;

	len = ft_len(n);
	str = malloc(len + 1);
	return (str);
}

static	char	*ft_reverse(char *str, size_t len)
{
	char	c;
	size_t	i;

	i = 0;
	len = len - 1;
	if (str[0] == '-')
		i++;
	while (i < len)
	{
		c = str[len];
		str[len] = str[i];
		str[i] = c;
		i++;
		len--;
	}
	return (str);
}

char			*ft_itoa(int n)
{
	size_t	len;
	char	*str;
	size_t	i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = ft_witcher(n);
	len = ft_len(n);
	if (str)
	{
		i = 0;
		while (i < len)
		{
			if (n < 0 && i == 0)
			{
				n = n * (-1);
				str[i++] = '-';
			}
			str[i++] = n % 10 + 48;
			n = n / 10;
		}
		str[i] = '\0';
		return (ft_reverse(str, len));
	}
	return (0);
}
