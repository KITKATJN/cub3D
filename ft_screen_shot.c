#include "cub3D.h"

void ft_screen_shot(t_all *all)
{
	int fd;
	int x;
	int y;
	unsigned char *fileheader;
	unsigned char *infoheader;

	if ((fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0666)) < 0)
		ft_perror("Can't create or open file for screenshot : ");
	fileheader = fheader(all);
	infoheader = iheader(all);
	write(fd, fileheader, 14);
	write(fd, infoheader, 40);
	y = all->win->res_y;
	while (y >= 0)
	{
		x = 0;
		while (x < all->win->res_x)
		{
			write(fd, &all->win->addr[y * all->win->line_l / 4 + x], 3);
			x++;
		}
		y--;
	}
	if ((close(fd)) < 0)
		ft_perror("Can't close file for screenshot : ");
}
