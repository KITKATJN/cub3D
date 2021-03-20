/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcermap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 13:47:43 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 09:36:35 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	ft_checkmap3(t_all *all, char **map, int j, int i)
{
	all->plr->map_check = 0;
	all->plr->map_x = i;
	all->plr->map_y = j;
	while (map[all->plr->map_y][all->plr->map_x]
			!= '\0' && all->plr->map_y < all->map_height)
		if (map[all->plr->map_y++][all->plr->map_x] == '1')
		{
			all->plr->map_check = 1;
			break ;
		}
	if (!all->plr->map_check)
		ft_perror("Error\n");
	all->plr->map_x = i;
	all->plr->map_y = j;
	all->plr->map_check = 0;
	while (map[all->plr->map_y][all->plr->map_x] && y >= 0)
	{
		if (map[all->plr->map_y--][all->plr->map_x] == '1')
		{
			all->plr->map_check = 1;
			break ;
		}
	}
	if (!all->plr->map_check)
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

static	void	ft_checkmap4(t_all *all, char **map, int y, int x)
{
	x = -1;
	while (map[y][++x] != '\0')
	{
		if (!ft_strrchr(VALID_MAP_SYMB, map[y][x]))
			ft_perror("Error\n");
		if (map[y][x] == '0' || map[y][x] == '2'
			|| map[y][x] == 'S' || map[y][x] == 'N'
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
		ft_checkmap4(all, map, y, -1);
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
