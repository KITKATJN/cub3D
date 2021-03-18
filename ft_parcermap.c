/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcermap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 13:47:43 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/18 16:33:14 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static	void	ft_checkmap3(char **map, int j, int i, int check)
{
	int			x;
	int			y;

	x = i;
	y = j;
	while (map[y][x] != '\0')
		if (map[y++][x] == '1')
		{
			check = 1;
			break ;
		}
	if (!check)
		ft_perror("Error with map");
	x = i;
	y = j;
	check = 0;
	while (map[y][x])
		if (map[y--][x] == '1')
		{
			check = 1;
			break ;
		}
	if (!check)
		ft_perror("Error with map");
}

static	void	ft_checkmap2(char **map, int y, int x)
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
		ft_perror("Error with map");
	x = i;
	y = j;
	check = 0;
	while (map[y][x])
		if (map[y][x--] == '1')
			check = 1;
	if (!check)
		ft_perror("Error with map");
	ft_checkmap3(map, j, i, 0);
}

static	void	ft_checkmap(char **map)
{
	int			x;
	int			y;

	y = -1;
	while (map[++y] != 0)
	{
		x = -1;
		while (map[y][++x] != '\0')
		{
			if (!ft_strrchr(VALID_MAP_SYMB, map[y][x]))
				ft_perror("Invalid map symbol");
			if (map[y][x] == '0' || map[y][x] == '2')
			{
				ft_checkmap2(map, y, x);
				if (map[y + 1][x] == ' ')
					ft_perror("Error in map");
				if (map[y][x + 1] == ' ')
					ft_perror("Error in map");
				if (map[y - 1][x] == ' ')
					ft_perror("Error in map");
				if (map[y][x - 1] == ' ')
					ft_perror("Error in map");
			}
		}
	}
}

void			ft_freemap(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
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
		ft_perror("Error with malloc in ft_parcer_map");
	size = -1;
	while (all->parcer_map[i])
		map[++size] = ft_strdup(all->parcer_map[i++]);
	ft_freemap(all->parcer_map);
	ft_checkmap(map);
	all->map = map;
	ft_count_2(all);
}
