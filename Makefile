
NAME		= cub3D


SRCS		= parser.c ft_rays.c \
		map.c ft_parcer.c \
		ft_perror.c ft_screen_shot.c \
		count_vert_hor_dist.c ft_draw_wall.c \
		set_img_param.c get_colors.c \
		sprites.c \


#BONUS_S		= movin_bonus.c


OBJ		= $(SRCS:.c=.o)
OBJS		= $(addprefix $(OBJRID), $(OBJ))


CFLAGS		= -Wall -Werror -Wextra #-g -fsanitize=address
#MLX_FLAGS	= -framework OpenGL -framework AppKit
MLX_FLAGS = -lXext -lX11 -lm #linux
OPTFLAGS	= -O3
LEAKFLAGS	= -ggdb3 -std=c11


MLX_A		= libmlx.a
MLX_LINUX	= libmlx_Linux.a
LIBFT_A		= libft.a
GNL_A		= gnl.a


LIBFTD		= libft/
#MLXD		= mlx/#mac
MLXD		= minilibx-linux/
GNLD		= get_next_line/
OBJRID		= objs/

CUB_H		= -I cub3d.h
#LIBS		= $(GNLD)$(GNL_A) $(MLXD)$(MLX_A) $(LIBFTD)$(LIBFT_A) #mac
LIBS		= $(GNLD)$(GNL_A) $(MLXD)$(MLX_A) $(MLXD)$(MLX_LINUX) $(LIBFTD)$(LIBFT_A) #linux

all:	$(NAME)

$(NAME): $(OBJS) #cub3d.h
	@make -C $(MLXD)
	@make -C $(LIBFTD)
	@make -C $(LIBFTD) bonus
	@make -C $(GNLD)
	gcc $(CFLAGS) $(OBJS) $(LIBS) $(MLX_FLAGS) -o $(NAME)
	@echo "\n\tcub3D created\t\n"

$(OBJRID)%.o: %.c
	@mkdir -p $(OBJRID)
	gcc $(OPTFLAGS) -c $< -o $@ $(CUB_H)

clean:
	@rm -rf $(OBJRID)
	@make -C $(GNLD) clean
	@make -C $(MLXD) clean
	@make -C $(LIBFTD) clean
	echo "\n cub3D cleaned\n"

fclean:	clean
	rm -f $(NAME)
	@make -C $(LIBFTD) fclean
	@make -C $(GNLD) fclean
	echo "\ncub3D fully cleaned\n"

re:	fclean all

.PHONY:	fclean all re clean

.SILENT: fclean clean all re $(NAME) $(OBJS) $(OBJRID)
