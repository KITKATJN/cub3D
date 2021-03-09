#include "cub3D.h"


unsigned char* ft_fileheader(t_all *all)
{
    int fileSize = 14 + 40 + (all->win->res_x * all->win->res_y);

    static unsigned char fileHeader[] = {
        0,0,     /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize      );
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(14 + 40);

    return fileHeader;
}

unsigned char* ft_infoheader (t_all *all)
{
    static unsigned char infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0,     /// number of color planes
        0,0,     /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

    infoHeader[ 0] = (unsigned char)(40);
    infoHeader[ 4] = (unsigned char)(all->win->res_x      );
    infoHeader[ 5] = (unsigned char)(all->win->res_x >>  8);
    infoHeader[ 6] = (unsigned char)(all->win->res_x >> 16);
    infoHeader[ 7] = (unsigned char)(all->win->res_x >> 24);
    infoHeader[ 8] = (unsigned char)(all->win->res_y      );
    infoHeader[ 9] = (unsigned char)(all->win->res_y >>  8);
    infoHeader[10] = (unsigned char)(all->win->res_y >> 16);
    infoHeader[11] = (unsigned char)(all->win->res_y >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(3 * 8);

    return infoHeader;
}

void	ft_screen_shot(t_all *all)
{
	int fd;
	int x;
	int y;
	unsigned char *fileheader;
	unsigned char *infoheader;

	if ((fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0666)) < 0)
		ft_perror("Can't create or open file for screenshot");
	fileheader = ft_fileheader(all);
	infoheader = ft_infoheader(all);
	write(fd, fileheader, 14);
	write(fd, infoheader, 40);
	y = all->win->res_y;
	while (y >= 0)
	{
		x = 0;
		while (x < all->win->res_x)
		{

			char	*dst;
			int		color;
			dst = all->win->addr + (x * (all->win->bpp / 8) + y * all->win->line_l);
			color = *(unsigned int*)dst;
			write(fd, &color, 3);
			//write(fd, &all->win->addr[y * all->win->line_l / 4 + x], 3);
			x++;
		}
		y--;
	}
	if ((close(fd)) < 0)
		ft_perror("Can't close file for screenshot");
}
