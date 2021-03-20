#include <mlx.h>
#include <stdio.h>

typedef struct  s_vars {
        void    *mlx;
        void    *win;
}               t_vars;


int             close(int keycode, t_vars *vars)
{
    if (keycode == 65307)
        mlx_destroy_window(vars->mlx, vars->win);
    else
        printf(" %d\n", keycode);
    printf("");
}

int online_(t_vars *vars)
{
    printf("Hello!\n");
}

int offline_(t_vars *vars)
{
    printf("Bye\n");
}
int             main(void)
{
    t_vars    vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
    mlx_hook(vars.win, 7, 1L<<4, online_, &vars);
    mlx_hook(vars.win, 8, 1L<<5, offline_, &vars);
    mlx_loop(vars.mlx);
}

