#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include <fcntl.h>
#include <mlx.h>

typedef struct  s_vars {
        void    *mlx;
        void    *win;
}               t_vars;

char	**make_map(t_list **head, int size)
{
	char	  **map = ft_calloc(size + 1, sizeof(char *));
	int		  i = -1;
	t_list	*tmp = *head;


	while (tmp)
	{
		map[++i] = tmp->content;
		tmp = tmp->next;
	}
	i = -1;
	//printf("HI");
	//while (map[++i])
	//	ft_putendl_fd(map[i],1);
	return (map);
}

void	write_map(char **map)
{

	t_vars vars;
	//t_data  img;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
    //img.img = mlx_new_image(mlx, 192, 108);
    //img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
    //                             &img.endian);

    int i = 0;
    int j = 0;
    while (map[i][j])
    {
        j = 0;
        while (map[i][j] != '\0')
        {
			if (map[i][j] == '1')
				mlx_pixel_put(vars.mlx, vars.win, i, j, 0x00FF0000);
			if (map[i][j] == '0')
				mlx_pixel_put(vars.mlx, vars.win, i, j, 0x0000FF00);
			if (map[i][j] == 'N')
				mlx_pixel_put(vars.mlx, vars.win, i, j, 0x00FFFFFF);
            j++;
        }
		j = 0;
        i++;
    }
    //mlx_pixel_put(vars.mlx, vars.win, 0, 0, 0x00FF0000);
    //mlx_loop_hook(vars.mlx, close, &vars);
    //my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
    //mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(vars.mlx);

}

int		main(int argc, char **argv)
{
	int      fd = open(argv[1], O_RDONLY);
	char	  *line = NULL;
	t_list	*head = NULL;

	while (get_next_line(fd, &line) && argc > 0)
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));

	write_map(make_map(&head, ft_lstsize(head)));
}
