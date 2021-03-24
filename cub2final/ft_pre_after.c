/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_after.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:10:43 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 17:10:46 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_preparcer(t_all *all)
{
	all->win->res_x = 0;
	all->win->res_y = 0;
	all->map = 0;
	all->win->c_color = -1;
	all->win->f_color = -1;
	all->win->s_path = 0;
	all->win->ea_path = 0;
	all->win->so_path = 0;
	all->win->we_path = 0;
	all->win->no_path = 0;
	all->plr->x = -1;
}

void			ft_afterparcer(t_all *all, int parametr)
{
	if (all->win->res_x == 0 || all->win->res_y == 0)
		ft_perror("Error\n wrong res x or res y\n", all);
	if (all->map == 0)
		ft_perror("Error\n no  map\n", all);
	if (all->win->c_color == 0)
		ft_perror("Error\n errot with c color\n", all);
	if (all->win->f_color == 0)
		ft_perror("Error\n error with f color\n", all);
	if (all->win->s_path == 0)
		ft_perror("Error\n error with s path\n", all);
	if (all->win->ea_path == 0)
		ft_perror("Error\n error with ea pth\n", all);
	if (all->win->so_path == 0)
		ft_perror("Error\n error with so path\n", all);
	if (all->win->we_path == 0)
		ft_perror("Error\n error with we path\n", all);
	if (parametr != 8)
		ft_perror("Error\n wrong numbers of parametr before map\n", all);
}

static	void	ft_check_r(char *r, int j, t_all *all)
{
	int			i;
	int			check;
	int			amount;

	i = j;
	if (r[j] != ' ')
		ft_perror("Error\nwith R\n", all);
	while (r[++i] != '\0')
		if (!ft_strrchr(VALID_R_SYMB, r[i]))
			ft_perror("Error\n invalid symbol in r\n", all);
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
	ft_checkamountaft(all, check, amount);
}

void			ft_parcer_r(t_all *all, char *str, int j)
{
	char	*ptr;
	char	*res_x;
	int		height;
	int		width;

	ft_check_r(str, j, all);
	ptr = str;
	all->win->res_x = ft_atoi(ptr + j);
	if (all->win->res_x == -1)
		ft_perror("Error\n res x wrong over int\n", all);
	res_x = ft_itoa(all->win->res_x);
	if (!res_x)
		ft_perror("Error\n error with maloc in parcer r\n", all);
	ptr = ft_strnstr(str, res_x, ft_strlen(str));
	if (!ptr)
		ft_perror("Error\n error with maloc in parcer r\n", all);
	all->win->res_y = ft_atoi(ptr + ft_strlen(res_x));
	if (all->win->res_y <= 0)
		ft_perror("Error\n res y wrong\n", all);
	free(res_x);
	mlx_get_screen_size(&width, &height);
	ft_setheiwifth(all, height, width);
}
