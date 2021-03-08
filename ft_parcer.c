#include "cub3D.h"

void	ft_parcer_NO(t_all *all, char *str, int start)
{
	char *ptr;
	char *ptr_end;

	ptr = str;
	while (str[start]== ' ' || str[start]== '	' ||
		str[start]== '\t' || str[start]== '\f' ||
			str[start]== '\r' || str[start]== '\v')
			start++;
	ptr_end = ft_strnstr(str, ".xpm", ft_strlen(str));//
	ptr_end += 4;
	all->win->NO_path = ft_substr(str, start, ft_strlen(ptr_end) - ft_strlen(ptr + start));
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
	ptr_end = ft_strnstr(str, ".xpm", ft_strlen(str));//
	ptr_end += 4;
	all->win->SO_path = ft_substr(str, start, ft_strlen(ptr_end) - ft_strlen(ptr + start));
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
	ptr_end = ft_strnstr(str, ".xpm", ft_strlen(str));// вернул 0, выдаем ошибку
	ptr_end += 4;
	all->win->WE_path = ft_substr(str, start, ft_strlen(ptr_end) - ft_strlen(ptr + start));
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
	ptr_end = ft_strnstr(str, ".xpm", ft_strlen(str));//если вернул 0, то ошибку выдаем
	ptr_end += 4;
	all->win->EA_path = ft_substr(str, start, ft_strlen(ptr_end) - ft_strlen(ptr + start));
}

void	ft_parcer_S(t_all *all, char *str, int start)
{
	char *ptr;
	char *ptr_end;

	ptr = str;
	while (str[start]== ' ' || str[start]== '	' ||
		str[start]== '\t' || str[start]== '\f' ||
			str[start]== '\r' || str[start]== '\v')
			start++;
	ptr_end = ft_strnstr(str, ".xpm", ft_strlen(str));//если вернул 0, то ошибку выдаем
	ptr_end += 4;
	all->win->S_path = ft_substr(str, start, ft_strlen(ptr_end) - ft_strlen(ptr + start));
	//printf("s path = %s\n",all->win->S_path);
}

void	ft_parcer_F(t_all *all, char *str, int start)
{
	char	*ptr;
	char	*ptr_end;
	char	*color;

	ptr = str;
	while (str[start]== ' ' || str[start]== '	' ||
		str[start]== '\t' || str[start]== '\f' ||
			str[start]== '\r' || str[start]== '\v')
			start++;
	ptr_end = ft_strnstr(ptr, ",", ft_strlen(ptr));//если вернул 0, то ошибку выдаем
	color = ft_substr(str, start, ft_strlen(ptr_end) - ft_strlen(ptr + start));
	all->win->F_color = ft_atoi(color) * 16 * 16 * 16 * 16;
	free(color);
	ptr = ptr_end;
	ptr_end = ft_strnstr(ptr + 1, ",", ft_strlen(ptr));
	color = ft_substr(str, ft_strlen(str) - ft_strlen(ptr) + 1,ft_strlen(ptr));
	all->win->F_color += ft_atoi(color) * 16 * 16;
	free(color);
	color = ft_substr(str, ft_strlen(str) - ft_strlen(ptr_end) + 1, ft_strlen(ptr_end));
	all->win->F_color += ft_atoi(color);
	free(color);
	printf("%d\n",all->win->F_color);
}

void	ft_parcer_C(t_all *all, char *str, int start)
{
	char	*ptr;
	char	*ptr_end;
	char	*color;

	ptr = str;
	while (str[start]== ' ' || str[start]== '	' ||
		str[start]== '\t' || str[start]== '\f' ||
			str[start]== '\r' || str[start]== '\v')
			start++;
	ptr_end = ft_strnstr(ptr, ",", ft_strlen(ptr));//если вернул 0, то ошибку выдаем
	color = ft_substr(str, start, ft_strlen(ptr_end) - ft_strlen(ptr + start));
	all->win->C_color = ft_atoi(color) * 16 * 16 * 16 * 16;
	free(color);
	ptr = ptr_end;
	ptr_end = ft_strnstr(ptr + 1, ",", ft_strlen(ptr));
	color = ft_substr(str, ft_strlen(str) - ft_strlen(ptr) + 1,ft_strlen(ptr));
	all->win->C_color += ft_atoi(color) * 16 * 16;
	free(color);
	color = ft_substr(str, ft_strlen(str) - ft_strlen(ptr_end) + 1, ft_strlen(ptr_end));
	all->win->C_color += ft_atoi(color);
	free(color);
	printf("%d\n",all->win->C_color);
}

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
	printf("2 = %d\n", all->win->count_2);
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
				sprite->x = j + 0.5f;
				sprite->y = i + 0.5f;
				all->spr[k++] = sprite;
			}
			j++;
		}
		i++;
	}
	// k = 0;
	// while (all->spr[k])
	// {
	// 	printf("x = %f y = %f\n", all->spr[k]->x, all->spr[k]->y);
	// 	k++;
	// 	/* code */
	// }

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
		size++;
		j++;
	}
	//printf("%d %d\n", size, i);
	map = ft_calloc(size + 1, sizeof(char *));
	//printf("SIZE = %d\n", size);
	size = -1;
	while (all->parcer_map[i])
	{
		if (all->parcer_map[i][0] == '\0')
			break ;
		map[++size] = ft_strdup(all->parcer_map[i++]);
		//printf("!->%s\n", map[size]);
	}
	//здесь чистим parcer map
	all->map = map;
	ft_count_2(all);
}

void	ft_parcer_R(t_all *all, char *str, int j)
{
	char *ptr;
	char *res_x;

	ptr = str;
	all->win->res_x = ft_atoi(ptr + j);
	res_x = ft_itoa(all->win->res_x);
	ptr = ft_strnstr(str, res_x, ft_strlen(str));
	all->win->res_y = ft_atoi(ptr + ft_strlen(res_x));
	free(res_x);
}

void	ft_parcer(t_all *all)
{
	int i = -1;
	int j = 0;

	while (all->parcer_map[++i])
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
		{
			ft_parcer_EA(all, all->parcer_map[i], j + 2);
		}
		else if (all->parcer_map[i][j] == 'F')
			ft_parcer_F(all,all->parcer_map[i], j + 1);
		else if (all->parcer_map[i][j] == 'C')
			ft_parcer_C(all,all->parcer_map[i], j + 1);
		else if (all->parcer_map[i][j] == 'S')
			ft_parcer_S(all,all->parcer_map[i], j + 1);
		else if (all->parcer_map[i][j] == '1')
		{
			ft_parcer_map(all, i);
			break ;
		}
		j = 0;
	}
}
