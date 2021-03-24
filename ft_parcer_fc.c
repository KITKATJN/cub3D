/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcer_fc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:19:40 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/18 10:44:10 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	lololo(t_all *all, char *str, int start)
{
	if (str[start] != ' ')
		ft_perror("Error\nwith C\n", all);
}

static	void	ft_parcer_f2(t_all *all, char *ptr_end, char *str)
{
	char		*ptr;
	char		*color;

	ptr = ptr_end;
	ptr_end = ft_strnstr(ptr + 1, ",", ft_strlen(ptr));
	if (!ptr_end)
		ft_perror("Error\n with malloc in parcer f2\n", all);
	color = ft_substr(str, ft_strlen(str) - ft_strlen(ptr) + 1, ft_strlen(ptr));
	ft_check_colorf(color, all);
	ft_check_colorf2(color, all);
	all->win->f_color += ft_atoi(color) * 16 * 16;
	free(color);
	color = ft_substr(str, ft_strlen(str)
		- ft_strlen(ptr_end) + 1, ft_strlen(ptr_end));
	ft_check_colorf(color, all);
	ft_check_colorf2(color, all);
	all->win->f_color += ft_atoi(color);
	free(color);
}

void			ft_parcer_f(t_all *all, char *str, int start)
{
	char		*ptr;
	char		*ptr_end;
	char		*color;

	if (all->win->f_color == -1)
	{
		ptr = str;
		lololo(all, str, start);
		while (str[start] == ' ')
			start++;
		ft_check_f(str, all);
		ft_check_number_of_digit(str, all);
		ptr_end = ft_strnstr(ptr, ",", ft_strlen(ptr));
		if (!ptr_end)
			ft_perror("Error\n with malloc in parcer f\n", all);
		color = ft_substr(str, start, ft_strlen(ptr_end)
			- ft_strlen(ptr + start));
		ft_check_colorf(color, all);
		ft_check_colorf2(color, all);
		all->win->f_color = ft_atoi(color) * 16 * 16 * 16 * 16;
		free(color);
		ft_parcer_f2(all, ptr_end, str);
	}
	else
		ft_perror("Error\n redefinition f color\n", all);
}

static	void	ft_parcer_c2(t_all *all, char *ptr_end, char *str)
{
	char		*ptr;
	char		*color;

	ptr = ptr_end;
	ptr_end = ft_strnstr(ptr + 1, ",", ft_strlen(ptr));
	if (!ptr_end)
		ft_perror("Error\nwith malloc parcer c2\n", all);
	color = ft_substr(str, ft_strlen(str) - ft_strlen(ptr) + 1, ft_strlen(ptr));
	ft_check_colorf(color, all);
	ft_check_colorf2(color, all);
	all->win->c_color += ft_atoi(color) * 16 * 16;
	free(color);
	color = ft_substr(str, ft_strlen(str)
		- ft_strlen(ptr_end) + 1, ft_strlen(ptr_end));
	ft_check_colorf(color, all);
	ft_check_colorf2(color, all);
	all->win->c_color += ft_atoi(color);
	free(color);
}

void			ft_parcer_c(t_all *all, char *str, int start)
{
	char		*ptr;
	char		*ptr_end;
	char		*color;

	if (all->win->c_color == -1)
	{
		ptr = str;
		lololo(all, str, start);
		while (str[start] == ' ')
			start++;
		ft_check_f(str, all);
		ft_check_number_of_digit(str, all);
		ptr_end = ft_strnstr(ptr, ",", ft_strlen(ptr));
		if (!ptr_end)
			ft_perror("Error\n with malloc parcer c\n", all);
		color = ft_substr(str, start,
			ft_strlen(ptr_end) - ft_strlen(ptr + start));
		ft_check_colorf(color, all);
		ft_check_colorf2(color, all);
		all->win->c_color = ft_atoi(color) * 16 * 16 * 16 * 16;
		free(color);
		ft_parcer_c2(all, ptr_end, str);
	}
	else
		ft_perror("Error\nredefinition c\n", all);
}
