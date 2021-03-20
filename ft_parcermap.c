/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcermap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 13:47:43 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/18 22:58:32 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	ft_checkmap3(t_all *all, char **map, int j, int i)
{
	all->plr->check = 0;
	all->plr->x_m = i;
	all->plr->y_m = j;
	while (map[all->plr->y_m][all->plr->x_m]
		!= '\0' && all->plr->y_m < all->map_height)
		if (map[all->plr->y_m++][all->plr->x_m] == '1')
		{
			all->plr->check = 1;
			break ;
		}
	if (!all->plr->check)
		ft_perror("Error\n");
	all->plr->x_m = i;
	all->plr->y_m = j;
	all->plr->check = 0;
	while (map[all->plr->y_m][all->plr->x_m] && all->plr->y_m >= 0)
	{
		if (map[all->plr->y_m--][all->plr->x_m] == '1')
		{
			all->plr->check = 1;
			break ;
		}
	}
	if (!all->plr->check)
		ft_perror("Error\n");
}

static	void	ft_checkmap2(t_all *all, char **map, int y, int x)
{
	int			i;
	int			j;
	int			check;

	i = x;
	j = y;
	check = 0;
	while (map[y][x] != '\0')
		if (map[y][x++] == '1')
			check = 1;
	if (!check)
		ft_perror("Error\n");
	x = i;
	y = j;
	check = 0;
	while (map[y][x])
		if (map[y][x--] == '1')
			check = 1;
	if (!check)
		ft_perror("Error\n");
	ft_checkmap3(all, map, j, i);
}

static	void	ft_checkmap4(char **map, t_all *all, int y, int x)
{
	if (!ft_strrchr(VALID_MAP_SYMB, map[y][x]))
		ft_perror("Error\n");
	if (map[y][x] == '0' || map[y][x] == '2' ||
		map[y][x] == 'S' || map[y][x] == 'N'
			|| map[y][x] == 'W' || map[y][x] == 'E')
	{
		ft_checkmap2(all, map, y, x);
		if (map[y + 1][x] == ' ')
			ft_perror("Error\n");
		if (map[y][x + 1] == ' ')
			ft_perror("Error\n");
		if (map[y - 1][x] == ' ')
			ft_perror("Error\n");
		if (map[y][x - 1] == ' ')
			ft_perror("Error\n");
	}
}

static	void	ft_checkmap(char **map, t_all *all)
{
	int			x;
	int			y;
	int			i;

	y = -1;
	i = 0;
	while (map[++y] != 0)
	{
		if (map[y][0] == '\0' && y < all->map_height - 1)
			while (y + i < all->map_height - 1)
			{
				if (map[y][0] != '\0')
				{
					i = 2 * all->map_height;
					break ;
				}
				i++;
			}
		if (i == 2 * all->map_height)
			ft_perror("Error\n");
		x = -1;
		while (map[y][++x] != '\0')
			ft_checkmap4(map, all, y, x);
	}
}

void			ft_parcer_map(t_all *all, int i)
{
	int			size;
	int			j;
	char		**map;

	size = 0;
	j = i;
	while (all->parcer_map[j])
	{
		size++;
		j++;
	}
	all->map_height = size;
	map = ft_calloc(size + 1, sizeof(char *));
	if (!map)
		ft_perror("Error\n");
	size = -1;
	while (all->parcer_map[i])
	{
		map[++size] = ft_strdup(all->parcer_map[i++]);
	}
	ft_checkmap(map, all);
	all->map = map;
	ft_count_2(all);
}
