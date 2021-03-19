/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcer_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 01:27:23 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 01:28:27 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		ft_check_r(char *r, int j)
{
	int		i;
	int		check;
	int		amount;

	i = j;
	while (r[++i] != '\0')
		if (!ft_strrchr(VALID_R_SYMB, r[i]))
			ft_perror("Error\n");
	check = 0;
	amount = 0;
	i = 0;
	while (r[++i] != '\0')
	{
		if (ft_isdigit(r[i]) && check == 0)
			check = 1;
		if (!ft_isdigit(r[i]) && check == 1)
		{
			amount++;
			check = 0;
		}
	}
	if (check == 1)
		amount++;
	if (amount != 2)
		ft_perror("Error\n");
}

void		ft_parcer_r(t_all *all, char *str, int j)
{
	char	*ptr;
	char	*res_x;
	int		height;
	int		width;

	ft_check_r(str, j);
	ptr = str;
	all->win->res_x = ft_atoi(ptr + j);
	if (all->win->res_x <= 0)
		ft_perror("Error\n");
	res_x = ft_itoa(all->win->res_x);
	ptr = ft_strnstr(str, res_x, ft_strlen(str));
	all->win->res_y = ft_atoi(ptr + ft_strlen(res_x));
	if (all->win->res_y <= 0)
		ft_perror("Error\n");
	free(res_x);
	mlx_get_screen_size(&width, &height);
	if (all->win->res_y > height)
		all->win->res_y = height - 1;
	if (all->win->res_x > width)
		all->win->res_x = width - 1;
	if (all->win->res_x == 60 || all->win->res_x == 40)
		all->win->res_x++;
}
