/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:22:39 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/15 23:22:40 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_perror(char *error, t_all *all)
{
	ft_putstr_fd(error, 2);
	ft_freeall(all);
	exit(-1);
}
