#include <mlx.h>
#include <stdio.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct  s_vars {
        void    *mlx;
        void    *win;
}               t_vars;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             close(int keycode, t_vars *vars)
{
    //if (keycode == 119)
        printf("%d\n", keycode);
   return 0;
}

int go(int keycode, t_data data, t_vars *vars)
{
    if (keycode == 119)
    {
        printf("sfd");
    }
    mlx_hook(vars->win, 2, 1L<<0, close, &vars);
}

int             main(void)
{
    t_vars vars;
    t_data  img;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
    //img.img = mlx_new_image(mlx, 192, 108);
    //img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
    //                             &img.endian);
    /*
    int i = 0;
    int j = 0;
    while (i < 100)
    {
        j = 0;
        while (j < 100)
        {
            mlx_pixel_put(mlx, mlx_win, i, j, 0x00FF0000);
            j++;
        }
        i++;
    }
    */
    mlx_pixel_put(vars.mlx, vars.win, 0, 0, 0x00FF0000);
    mlx_loop_hook(vars.mlx, close, &vars);
    //my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
    //mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(vars.mlx);
}
