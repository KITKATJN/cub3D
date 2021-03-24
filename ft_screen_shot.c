/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen_shot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarguer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 17:57:53 by cmarguer          #+#    #+#             */
/*   Updated: 2021/03/20 17:57:55 by cmarguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		*ft_fileheader(t_all *all)
{
	int		filesize;
	char	*fileheader;

	fileheader = ft_calloc(14, sizeof(char));
	if (!fileheader)
		ft_perror("Error\n with malloc for file header\n", all);
	fileheader[0] = (unsigned char)('B');
	fileheader[1] = (unsigned char)('M');
	fileheader[2] = (unsigned char)(filesize);
	fileheader[3] = (unsigned char)(filesize >> 8);
	fileheader[4] = (unsigned char)(filesize >> 16);
	fileheader[5] = (unsigned char)(filesize >> 24);
	fileheader[10] = (unsigned char)(14 + 40);
	return (fileheader);
}

char		*ft_infoheader(t_all *all)
{
	char	*infoheader;

	infoheader = ft_calloc(40, sizeof(char));
	if (!infoheader)
		ft_perror("Error\n with malloc for infoheader\n", all);
	infoheader[0] = (unsigned char)(40);
	infoheader[4] = (unsigned char)(all->win->res_x);
	infoheader[5] = (unsigned char)(all->win->res_x >> 8);
	infoheader[6] = (unsigned char)(all->win->res_x >> 16);
	infoheader[7] = (unsigned char)(all->win->res_x >> 24);
	infoheader[8] = (unsigned char)(all->win->res_y);
	infoheader[9] = (unsigned char)(all->win->res_y >> 8);
	infoheader[10] = (unsigned char)(all->win->res_y >> 16);
	infoheader[11] = (unsigned char)(all->win->res_y >> 24);
	infoheader[12] = (unsigned char)(1);
	infoheader[14] = (unsigned char)(32);
	return (infoheader);
}

void		ft_paintshot(t_all *all, int fd, int y, int x)
{
	char	*dst;
	int		color;

	dst = all->win->addr + (x * (all->win->bpp / 8) + y * all->win->line_l);
	color = *(unsigned int*)dst;
	if (write(fd, &color, 4) == -1)
		ft_perror("Error\n with write to file screenshot\n", all);
}

void		ft_screen_shot(t_all *all)
{
	int		fd;
	int		x;
	int		y;
	char	*fileheader;
	char	*infoheader;

	if ((fd = open("screenshottest.bmp", O_CREAT
		| O_WRONLY | O_TRUNC, 0666)) < 0)
		ft_perror("Error\n with open file for screenshot\n", all);
	fileheader = ft_fileheader(all);
	infoheader = ft_infoheader(all);
	if (write(fd, fileheader, 14) == -1 || write(fd, infoheader, 40) == -1)
		ft_perror("Error\n with write in file screenshot\n", all);
	y = all->win->res_y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < all->win->res_x)
			ft_paintshot(all, fd, y, x++);
		y--;
	}
	free(infoheader);
	free(fileheader);
	if ((close(fd)) < 0)
		ft_perror("Error\nwith close file for screen shot\n", all);
}
