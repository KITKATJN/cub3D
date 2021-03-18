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

#include "cub3D.h"

void	ft_parcer_no(t_all *all, char *str, int start)
{
	int i;

	i = -1;
	if (!all->win->no_path)
	{
		while (str[start] == ' ')
			start++;
		all->win->no_path = ft_substr(str, start, ft_strlen(str));
		if (!all->win->no_path)
			ft_perror("Wrong with malloc in no path");
	}
	else
		ft_perror("double NO redefinition!");
}

void	ft_parcer_so(t_all *all, char *str, int start)
{
	int i;

	i = -1;
	if (!all->win->so_path)
	{
		while (str[start] == ' ')
			start++;
		all->win->so_path = ft_substr(str, start, ft_strlen(str));
		if (!all->win->so_path)
			ft_perror("Wrong with malloc in so path");
	}
	else
		ft_perror("double SO redefinition!");
}

void	ft_parcer_we(t_all *all, char *str, int start)
{
	int i;

	i = -1;
	if (!all->win->we_path)
	{
		while (str[start] == ' ')
			start++;
		all->win->we_path = ft_substr(str, start, ft_strlen(str));
		if (!all->win->we_path)
			ft_perror("Wrong with malloc in we path");
	}
	else
		ft_perror("double WE redefinition!");
}

void	ft_parcer_ea(t_all *all, char *str, int start)
{
	int i;

	i = -1;
	if (!all->win->ea_path)
	{
		while (str[start] == ' ')
			start++;
		all->win->ea_path = ft_substr(str, start, ft_strlen(str));
		if (!all->win->ea_path)
			ft_perror("Wrong with malloc in ea path");
	}
	else
		ft_perror("double EA redefinition!");
}

void	ft_parcer_s(t_all *all, char *str, int start)
{
	int i;

	i = -1;
	if (!all->win->s_path)
	{
		while (str[start] == ' ')
			start++;
		all->win->s_path = ft_substr(str, start, ft_strlen(str));
		if (!all->win->s_path)
			ft_perror("Wrong with malloc in s path");
	}
	else
		ft_perror("double S redefinition!");
}
