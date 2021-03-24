/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_for_parcer_fc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:18:37 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/18 10:42:12 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_check_colorf2(char *color, t_all *all)
{
	int		i;
	int		check;

	i = 0;
	check = 0;
	while (color[i] != 0)
	{
		if (color[i] == ',')
			return ;
		if (ft_isdigit(color[i]))
		{
			if (check == 0)
				check = 1;
			if (check == 2)
				ft_perror("Error\n with amount of num in f or c\n", all);
		}
		if (check == 1 && !ft_isdigit(color[i]))
			check = 2;
		i++;
	}
}

int			ft_check_max_int(char *color, t_all *all)
{
	int		i;
	size_t	check;

	i = 0;
	check = 0;
	while (color[i] != '\0')
	{
		if (ft_isdigit(color[i]))
			check++;
		if (color[i] == ',')
			break ;
		i++;
	}
	if (ft_strlen(color) < ft_strlen(MAX_INT))
		return (0);
	if (check > ft_strlen(MAX_INT))
		ft_perror("Error\n parametr in f or c over big\n", all);
	return (0);
}

void		ft_check_colorf(char *color, t_all *all)
{
	int		i;
	int		check;

	if (!color)
		ft_perror("Error\n with  malloc for color f or c\n", all);
	if (ft_atoi(color) < 0 || ft_atoi(color) > 255 ||
		ft_check_max_int(color, all))
		ft_perror("Error\n wrong parametr for f or c\n", all);
	i = 0;
	check = 0;
	while (color[i] != 0)
	{
		if (ft_isdigit(color[i]))
		{
			check = 1;
			break ;
		}
		if (!check && color[i] == ',')
			break ;
		i++;
	}
	if (!check)
		ft_perror("Error\n with f or c\n", all);
}

void		ft_check_f(char *f, t_all *all)
{
	int		i;
	int		check;

	i = 1;
	while (f[i] != '\0')
	{
		if (!ft_strrchr(VALID_FC_SYMB, f[i]))
			ft_perror("Error\n invalid symb in f or c\n", all);
		i++;
	}
	check = 0;
	i -= 1;
	while (i > 0)
	{
		if (f[i] == ',' && check == 0)
			ft_perror("Error\n with , in f or c\n", all);
		if (ft_isdigit(f[i]))
			check = 1;
		i--;
	}
}

void		ft_check_number_of_digit(char *f, t_all *all)
{
	int		i;
	int		check1;
	int		amount;

	i = 0;
	amount = 0;
	check1 = 0;
	while (f[i] != '\0')
	{
		if (ft_isdigit(f[i]) && !check1)
			check1 = 1;
		if (!ft_isdigit(f[i]) && check1)
		{
			amount++;
			check1 = 0;
		}
		i++;
	}
	if (check1)
		amount++;
	if (amount != 3)
		ft_perror("Error\n with amount of numbers in f or c\n", all);
}
