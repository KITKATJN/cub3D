/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:33:21 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 17:33:23 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_qsort(t_all *all, int left, int right)
{
	t_sprite	*pivot;
	int			tmp;

	all->plr->l_hold = left;
	all->plr->r_hold = right;
	pivot = all->spr[left];
	while (left < right)
	{
		while ((all->spr[right]->dist <= pivot->dist) && (left < right))
			right--;
		if (left != right)
			all->spr[left++] = all->spr[right];
		while ((all->spr[left]->dist >= pivot->dist) && (left < right))
			left++;
		if (left != right)
			all->spr[right--] = all->spr[left];
	}
	all->spr[left] = pivot;
	tmp = left;
	left = all->plr->l_hold;
	right = all->plr->r_hold;
	if (left < tmp)
		ft_qsort(all, left, tmp - 1);
	if (right > tmp)
		ft_qsort(all, tmp + 1, right);
}
