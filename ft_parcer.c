#include "cub3D.h"


void	ft_count_2(t_all *all)
{
	int i;
	int j;
	int k;
	t_sprite *sprite;

	i = 0;
	j = 0;
	all->win->count_2 = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j] != '\0')
		{
			if (all->map[i][j++] == '2')
				all->win->count_2++;
		}
		i++;
	}
	all->spr = ft_calloc(all->win->count_2, sizeof(t_sprite));
	i = 0;
	j = 0;
	k = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j] != '\0')
		{
			if (all->map[i][j] == '2')
			{
				sprite = malloc(sizeof(t_sprite));
				if (!sprite)
					ft_perror("Error with malloc in ft_count2");
				sprite->x = j + 0.5f;
				sprite->y = i + 0.5f;
				all->spr[k++] = sprite;
			}
			j++;
		}
		i++;
	}
}


void ft_check_r(char *r, int j)
{
	int i;
	int check;
	int amount;

	i = j;
	while (r[++i] != '\0')
		if (!ft_strrchr(VALID_R_SYMB, r[i]))
			ft_perror("Invalid symbol in R");
	check = 0;
	amount = 0;
	i = 0;
	while (r[++i] != '\0')
	{
		if (ft_isdigit(r[i]) && check == 0)
			check = 1;
		if (!ft_isdigit(r[i]) && check == 1)
		{
			printf("g = %c\n", r[i-3]);
			amount++;
			check = 0;
		}
	}
	if (check == 1)
		amount++;
	if (amount != 2)
		ft_perror("Wrong amount of numbers in R");
}

void	ft_parcer_r(t_all *all, char *str, int j)
{
	char *ptr;
	char *res_x;
	int height;
	int width;

	ft_check_r(str, j);
	ptr = str;
	all->win->res_x = ft_atoi(ptr + j);
	if (all->win->res_x <= 0)
		ft_perror("Res_x not positive");
	res_x = ft_itoa(all->win->res_x);
	ptr = ft_strnstr(str, res_x, ft_strlen(str));
	all->win->res_y = ft_atoi(ptr + ft_strlen(res_x));
	if (all->win->res_y <= 0)
		ft_perror("Res_y not positive");
	free(res_x);
	mlx_get_screen_size(&width, &height);
	if (all->win->res_y > height)
		all->win->res_y = height - 1;
	if (all->win->res_x > width)
		all->win->res_x = width - 1;
	if (all->win->res_x == 60 || all->win->res_x == 40)
		all->win->res_x++;
	//printf("width %d  %d  nashi %d %d del %f\n", width, height, all->win->res_x, all->win->res_y, (float)((float)all->win->res_y / (float)all->win->res_x));
	//mlx_get_screen_size(&all->win->res_y, &all->win->res_y);
}

void	ft_preparcer(t_all *all)
{
	all->win->res_x = 0;
	all->win->res_y = 0;
	all->map = 0;
	all->win->c_color = -1;
	all->win->f_color = -1;
	all->win->s_path = 0;
	all->win->ea_path = 0;
	all->win->so_path = 0;
	all->win->we_path = 0;
	all->win->no_path = 0;
	all->plr->x = -1;
}

void ft_afterparcer(t_all *all, int parametr)
{
	if (all->win->res_x == 0 || all->win->res_y == 0)
		ft_perror("No R");
	if (all->map == 0)
		ft_perror("No map");
	if (all->win->c_color == 0)
		ft_perror("No c color");
	if (all->win->f_color == 0)
		ft_perror("No f color");
	if (all->win->s_path == 0)
		ft_perror("No s path");
	if (all->win->ea_path == 0)
		ft_perror("No ea path");
	if (all->win->so_path == 0)
		ft_perror("No so path");
	if (all->win->we_path == 0)
		ft_perror("No we path");
	if (parametr != 8)
		ft_perror("Wrong numbers of parametrs before map");
}

void	ft_parcer(t_all *all)
{
	int i = -1;
	int j = 0;
	int parametr;

	ft_preparcer(all);
	parametr = 0;
	while (all->parcer_map[++i])
	{
		if (all->parcer_map[i][j] == '\0')
		{
			parametr--;
			continue ;
		}
		while (all->parcer_map[i][j] == ' ')
			j++;
		if (all->parcer_map[i][j] == 'R')
			ft_parcer_r(all, all->parcer_map[i], j + 1);
		else if (all->parcer_map[i][j] == 'N' && all->parcer_map[i][j + 1] == 'O')
			ft_parcer_no(all, all->parcer_map[i], j + 2);
		else if (all->parcer_map[i][j] == 'S' && all->parcer_map[i][j + 1] == 'O')
			ft_parcer_so(all, all->parcer_map[i], j + 2);
		else if (all->parcer_map[i][j] == 'W' && all->parcer_map[i][j + 1] == 'E')
			ft_parcer_we(all, all->parcer_map[i], j + 2);
		else if (all->parcer_map[i][j] == 'E' && all->parcer_map[i][j + 1] == 'A')
			ft_parcer_ea(all, all->parcer_map[i], j + 2);
		else if (all->parcer_map[i][j] == 'F')
			ft_parcer_f(all,all->parcer_map[i], j + 1);
		else if (all->parcer_map[i][j] == 'C')
			ft_parcer_c(all,all->parcer_map[i], j + 1);
		else if (all->parcer_map[i][j] == 'S')
			ft_parcer_s(all,all->parcer_map[i], j + 1);
		else if (all->parcer_map[i][j] == '1')
		{
			ft_parcer_map(all, i);
			parametr += i;
			break ;
		}
		j = 0;
	}
	ft_afterparcer(all, parametr);
}
