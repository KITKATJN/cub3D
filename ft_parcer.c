#include "cub3D.h"

void	ft_parcer_NO(t_all *all, char *str, int start)
{
	char *ptr;
	char *ptr_end;
	int i;

	i = -1;
	if (!all->win->NO_path)
	{
		ptr = str;
		while (str[start]== ' ' || str[start]== '	' ||
			str[start]== '\t' || str[start]== '\f' ||
				str[start]== '\r' || str[start]== '\v')
				start++;
		ptr_end = ft_strnstr(str, ".xpm", ft_strlen(str));//
		if (!ptr_end)
			ft_perror("Wrong NO path or picture expansion");
		ptr_end += 4;
		all->win->NO_path = ft_substr(str, start, ft_strlen(ptr + start) - ft_strlen(ptr_end));
		while (ptr_end[++i] != '\0')
			if (ft_isalpha(ptr_end[i]) || ft_isdigit(ptr_end[i]))
				ft_perror("Wrong amount of arguments NO path");
	}
	else
		ft_perror("double NO redefinition!");
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
	if (!ptr_end)
		ft_perror("Wrong SO path or picture expansion");
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
	if (!ptr_end)
		ft_perror("Wrong WE path or picture expansion");
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
	if (!ptr_end)
		ft_perror("Wrong EA path or picture expansion");
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

void ft_check_colorF2(char *color)
{
	int i;
	int check;

	i = 0;
	check = 0;
	while (color[i] != 0)
	{
		if (color[i] == ',')
			return ;
		if (ft_isdigit(color[i]))
		{
			if (check == 0)
				check = 1;
			if (check == 2)
				ft_perror("Error with , in  F2");//убрать двойку от f
		}
		if (check == 1 && !ft_isdigit(color[i]))
			check = 2;
		i++;
	}
}

int	ft_check_max_int(char *color)
{
	int i;
	size_t check;

	i = 0;
	check = 0;
	while (color[i] != '\0')
	{
		if (ft_isdigit(color[i]))
			check++;
		if (color[i] == ',')
			break;
		i++;
	}
	if (ft_strlen(color) < ft_strlen(MAX_INT))
		return (0);
	if (check > ft_strlen(MAX_INT))
		ft_perror("Wrong value of number in F");
}

void ft_check_colorF(char *color)
{
	int i;
	int check;

	if (!color)
		ft_perror("Error with malloc in F");
	printf("her2 %d \n", ft_atoi(color));
	if (ft_atoi(color) < 0 || ft_atoi(color) > 255 || ft_check_max_int(color))
		ft_perror("Wrong value of number in F");
	i = 0;
	check = 0;
	while (color[i] != 0)
	{
		if (ft_isdigit(color[i]))
		{
			check = 1;
			break ;
		}
		if (!check && color[i] == ',')
			break ;
		i++;
	}
	if (!check)
		ft_perror("Error with , in  F");
}

void ft_check_f(char *f)
{
	int i;
	int check;

	i = 1;
	while (f[i] != '\0')
	{
		if (!ft_strrchr(VALID_FC_SYMB, f[i]))
			ft_perror("Invalid symbol in F");
		i++;
	}
	check = 0;
	i -= 1;
	while (i > 0)
	{
		if (f[i] == ',' && check == 0)
			ft_perror("Error with , in  F");
		if (ft_isdigit(f[i]))
			check = 1;
		i--;
	}
}

void ft_check_number_of_digit(char *f)
{
	int i;
	int check1;
	int amount;

	i = 0;
	amount = 0;
	check1 = 0;
	while (f[i] != '\0')
	{
		if (ft_isdigit(f[i]) && !check1)
			check1 = 1;
		if (!ft_isdigit(f[i]) && check1)
		{
			amount++;
			check1 = 0;
		}
		i++;
	}
	if (check1)
		amount++;
	if (amount != 3)
		ft_perror("Wrong amount of numbers in F");
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
	ft_check_f(str);
	ft_check_number_of_digit(str);
	ptr_end = ft_strnstr(ptr, ",", ft_strlen(ptr));//если вернул 0, то ошибку выдаем
	if (!ptr_end)
		ft_perror("Error in F malloc");
	color = ft_substr(str, start, ft_strlen(ptr_end) - ft_strlen(ptr + start));
	ft_check_colorF(color);
	ft_check_colorF2(color);
	all->win->F_color = ft_atoi(color) * 16 * 16 * 16 * 16;
	free(color);

	ptr = ptr_end;
	ptr_end = ft_strnstr(ptr + 1, ",", ft_strlen(ptr));
	if (!ptr_end)
		ft_perror("Error in F malloc");
	color = ft_substr(str, ft_strlen(str) - ft_strlen(ptr) + 1,ft_strlen(ptr));
	ft_check_colorF(color);
	ft_check_colorF2(color);
	all->win->F_color += ft_atoi(color) * 16 * 16;
	free(color);

	color = ft_substr(str, ft_strlen(str) - ft_strlen(ptr_end) + 1, ft_strlen(ptr_end));
	printf("herer %d \n", ft_atoi(color));
	ft_check_colorF(color);
	ft_check_colorF2(color);
	all->win->F_color += ft_atoi(color);
	free(color);
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
				sprite->x = j + 0.6f;
				sprite->y = i + 0.6f;
				all->spr[k++] = sprite;
			}
			j++;
		}
		i++;
	}
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
	map = ft_calloc(size + 1, sizeof(char *));
	size = -1;
	while (all->parcer_map[i])
	{
		if (all->parcer_map[i][0] == '\0')
			break ;
		map[++size] = ft_strdup(all->parcer_map[i++]);
	}
	//здесь чистим parcer map
	all->map = map;
	ft_count_2(all);
}

void ft_check_r(char *r)
{
	int i;
	int check;
	int amount;

	i = 0;
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

void	ft_parcer_R(t_all *all, char *str, int j)
{
	char *ptr;
	char *res_x;

	ft_check_r(str);
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
}

void	ft_preparcer(t_all *all)
{
	all->win->res_x = 0;
	all->win->res_y = 0;
	all->map = 0;
	all->win->C_color = 0;
	all->win->F_color = 0;
	all->win->S_path = 0;
	all->win->EA_path = 0;
	all->win->SO_path = 0;
	all->win->WE_path = 0;
	all->win->NO_path = 0;
}

void ft_afterparcer(t_all *all)
{
	if (all->win->res_x == 0 || all->win->res_y == 0)
		ft_perror("No R");
	if (all->map == 0)
		ft_perror("No map");
	if (all->win->C_color == 0)
		ft_perror("No c color");
	if (all->win->F_color == 0)
		ft_perror("No f color");
	if (all->win->S_path == 0)
		ft_perror("No s path");
	if (all->win->EA_path == 0)
		ft_perror("No ea path");
	if (all->win->SO_path == 0)
		ft_perror("No so path");
	if (all->win->WE_path == 0)
		ft_perror("No we path");
}

void	ft_parcer(t_all *all)
{
	int i = -1;
	int j = 0;

	ft_preparcer(all);
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
	ft_afterparcer(all);
}
