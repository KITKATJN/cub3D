/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcer_no.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 09:54:21 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/18 10:26:37 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parcer_no(t_all *all, char *str, int start)
{
	int i;

	i = -1;
	if (!all->win->no_path)
	{
		if (str[start] != ' ')
			ft_perror("Error\nwith no\n", all);
		while (str[start] == ' ')
			start++;
		all->win->no_path = ft_substr(str, start, ft_strlen(str));
		if (!all->win->no_path)
			ft_perror("Error\n with malloc to no path\n", all);
	}
	else
		ft_perror("Error\n redefinition no path\n", all);
}

void	ft_parcer_so(t_all *all, char *str, int start)
{
	int i;

	i = -1;
	if (!all->win->so_path)
	{
		if (str[start] != ' ')
			ft_perror("Error\nwith so\n", all);
		while (str[start] == ' ')
			start++;
		all->win->so_path = ft_substr(str, start, ft_strlen(str));
		if (!all->win->so_path)
			ft_perror("Error\n with malloc to so path\n", all);
	}
	else
		ft_perror("Error\n redefinition so path\n", all);
}

void	ft_parcer_we(t_all *all, char *str, int start)
{
	int i;

	i = -1;
	if (!all->win->we_path)
	{
		if (str[start] != ' ')
			ft_perror("Error\nwith we\n", all);
		while (str[start] == ' ')
			start++;
		all->win->we_path = ft_substr(str, start, ft_strlen(str));
		if (!all->win->we_path)
			ft_perror("Error\n with malloc we path\n", all);
	}
	else
		ft_perror("Error\n redefinition we\n", all);
}

void	ft_parcer_ea(t_all *all, char *str, int start)
{
	int i;

	i = -1;
	if (!all->win->ea_path)
	{
		if (str[start] != ' ')
			ft_perror("Error\nwith ea\n", all);
		while (str[start] == ' ')
			start++;
		all->win->ea_path = ft_substr(str, start, ft_strlen(str));
		if (!all->win->ea_path)
			ft_perror("Error\n with malloc ea path\n", all);
	}
	else
		ft_perror("Error\n redefinition ea path\n", all);
}

void	ft_parcer_s(t_all *all, char *str, int start)
{
	int i;

	i = -1;
	if (!all->win->s_path)
	{
		if (str[start] != ' ')
			ft_perror("Error\nwith s\n", all);
		while (str[start] == ' ')
			start++;
		all->win->s_path = ft_substr(str, start, ft_strlen(str));
		if (!all->win->s_path)
			ft_perror("Error\n with malloc s path\n", all);
	}
	else
		ft_perror("Error\n redefinition s path\n", all);
}
