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

void	ft_parcer_NO(t_all *all, char *str, int start)
{
	char *ptr;
	char *ptr_end;


	ptr = str;
	while (str[start]== ' ' || str[start]== '	' ||
		str[start]== '\t' || str[start]== '\f' ||
			str[start]== '\r' || str[start]== '\v')
			start++;
	ptr_end = ft_strnstr(str, ".xpm", ft_strlen(str));
	ptr_end += 4;
	all->win->NO_path = ft_substr(str, start, ft_strlen(ptr_end) - ft_strlen(ptr + start));
	printf("%s\n", all->win->NO_path);
}

void	ft_parcer_SO(t_all *all, char *str, int start)
{
	char *ptr;
	char *ptr_end;


	ptr = str;
	while (str[start]== ' ' || str[start]== '	' ||
		str[start]== '\t' || str[start]== '\f' ||
			str[start]== '\r' || str[start]== '\v')
			start++;
	ptr_end = ft_strnstr(str, ".xpm", ft_strlen(str));
	ptr_end += 4;
	all->win->SO_path = ft_substr(str, start, ft_strlen(ptr_end) - ft_strlen(ptr + start));
	printf("%s\n", all->win->SO_path);
}

void	ft_parcer_WE(t_all *all, char *str, int start)
{
	char *ptr;
	char *ptr_end;


	ptr = str;
	while (str[start]== ' ' || str[start]== '	' ||
		str[start]== '\t' || str[start]== '\f' ||
			str[start]== '\r' || str[start]== '\v')
			start++;
	ptr_end = ft_strnstr(str, ".xpm", ft_strlen(str));
	ptr_end += 4;
	all->win->WE_path = ft_substr(str, start, ft_strlen(ptr_end) - ft_strlen(ptr + start));
	printf("%s\n", all->win->WE_path);
}

void	ft_parcer_EA(t_all *all, char *str, int start)
{
	char *ptr;
	char *ptr_end;


	ptr = str;
	while (str[start]== ' ' || str[start]== '	' ||
		str[start]== '\t' || str[start]== '\f' ||
			str[start]== '\r' || str[start]== '\v')
			start++;
	ptr_end = ft_strnstr(str, ".xpm", ft_strlen(str));
	ptr_end += 4;
	all->win->EA_path = ft_substr(str, start, ft_strlen(ptr_end) - ft_strlen(ptr + start));
	printf("%s\n", all->win->EA_path);
}

void	ft_parcer_map(t_all *all, int i)
{
	int		size;
	int		j;
	char	**map;

	size = 0;
	j = i;
	while (all->parcer_map[j])
	{
		printf("->%s\n", all->parcer_map[j]);
		//if (all->parcer_map[j][0] != '\0')
		size++;
		j++;
	}
	//printf("%d %d\n", size, i);
	map = ft_calloc(size + 1, sizeof(char *));
	printf("SIZE = %d\n", size);
	size = -1;
	while (all->parcer_map[i])
	{
		map[++size] = ft_strdup(all->parcer_map[i++]);
	}
	//здесь чистим parcer map
	printf("fsd\n");
	all->map = map;
}

void	ft_parcer(t_all *all)
{
	int i = -1;
	int j = 0;

	while (all->parcer_map[++i] != 0)
	{
		if (all->parcer_map[i][j] == '\0')
			continue ;
		while (all->parcer_map[i][j] == ' ' || all->parcer_map[i][j]== '	' ||
		all->parcer_map[i][j]== '\t' || all->parcer_map[i][j]== '\f' ||
			all->parcer_map[i][j]== '\r' || all->parcer_map[i][j]== '\v')
			j++;
		if (all->parcer_map[i][j] == 'R')
			ft_parcer_R(all, all->parcer_map[i], j + 1);
		else if (all->parcer_map[i][j] == 'N' && all->parcer_map[i][j + 1] == 'O')
			ft_parcer_NO(all, all->parcer_map[i], j + 2);
		else if (all->parcer_map[i][j] == 'S' && all->parcer_map[i][j + 1] == 'O')
			ft_parcer_SO(all, all->parcer_map[i], j + 2);
		else if (all->parcer_map[i][j] == 'W' && all->parcer_map[i][j + 1] == 'E')
			ft_parcer_WE(all, all->parcer_map[i], j + 2);
		else if (all->parcer_map[i][j] == 'E' && all->parcer_map[i][j + 1] == 'A')
			ft_parcer_EA(all, all->parcer_map[i], j + 2);
			/*
		else if (all->parcer_map[i][j] == 'S')
			ft_parcer_S(all);
		else if (all->parcer_map[i][j] == 'F')
			ft_parcer_F(all);
		else if (all->parcer_map[i][j] == 'C')
			ft_parcer_C(all);

		else if (all->parcer_map[i][j] == '1')
		{
			ft_parcer_map(all, i);
			break ;
		}
		j = 0;*/
		//printf("%d  %c\n",i, all->parcer_map[i][j]);
	}
}
