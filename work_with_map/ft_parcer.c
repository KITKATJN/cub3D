#include "../cub3D.h"

void	ft_parcer_R(t_all *all, char *str, int j)
{
	char *ptr;

	ptr = str;
	//printf("%s %d\n", str, j);
	all->win->res_x = ft_atoi(ptr + j);
	printf("%d ", all->win->res_x);
	ptr = ft_strnstr(ptr, ft_itoa(all->win->res_x), ft_strlen(str));
	//printf(" *ptr = %s", ptr);
	all->win->res_y = ft_atoi(ptr + ft_strlen(ft_itoa(all->win->res_x)));
	printf("%d\n", all->win->res_y);
}
void	ft_parcer(t_all *all)
{
	int i = -1;
	int j = 0;

	while (all->map[++i] != 0)
	{
		while(all->map[i][j] == ' ')
			j++;
		if (all->map[i][j] == 'R')
			ft_parcer_R(all, all->map[i], j + 1);
		/*
		else if (all->map[i][j] == 'N' && all->map[i][j + 1] == 'O')
			ft_parcer_NO(all);
		else if (all->map[i][j] == 'S' && all->map[i][j + 1] == 'O')
			ft_parcer_SO(all);
		else if (all->map[i][j] == 'W' && all->map[i][j + 1] == 'E')
			ft_parcer_NE(all);
		else if (all->map[i][j] == 'E' && all->map[i][j + 1] == 'A')
			ft_parcer_EA(all);
		else if (all->map[i][j] == 'S')
			ft_parcer_S(all);
		else if (all->map[i][j] == 'F')
			ft_parcer_F(all);
		else if (all->map[i][j] == 'C')
			ft_parcer_C(all);
			*/
	}
}
