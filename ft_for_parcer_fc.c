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

#include "cub3D.h"

void		ft_check_colorf2(char *color)
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
				ft_perror("Error with , in  F or C");
		}
		if (check == 1 && !ft_isdigit(color[i]))
			check = 2;
		i++;
	}
}

int			ft_check_max_int(char *color)
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
		ft_perror("Wrong value of number in F or C");
}

void		ft_check_colorf(char *color)
{
	int		i;
	int		check;

	if (!color)
		ft_perror("Error with malloc in F");
	printf("her2 %d \n", ft_atoi(color));
	if (ft_atoi(color) < 0 || ft_atoi(color) > 255 || ft_check_max_int(color))
		ft_perror("Wrong value of number in F or C");
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
		ft_perror("Error with , in  F or C");
}

void		ft_check_f(char *f)
{
	int		i;
	int		check;

	i = 1;
	while (f[i] != '\0')
	{
		if (!ft_strrchr(VALID_FC_SYMB, f[i]))
			ft_perror("Invalid symbol in F or C");
		i++;
	}
	check = 0;
	i -= 1;
	while (i > 0)
	{
		if (f[i] == ',' && check == 0)
			ft_perror("Error with , in  F or C");
		if (ft_isdigit(f[i]))
			check = 1;
		i--;
	}
}

void		ft_check_number_of_digit(char *f)
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
		ft_perror("Wrong amount of numbers in F or C");
}
