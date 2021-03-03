SRCS	= get_next_line.c get_next_line_utils.c

HDR	= get_next_line.h

OBJ	= $(SRCS:.c=.o)

OBJDIR	= objs/

OBJS	= $(addprefix $(OBJDIR), $(OBJ))

CFLAGS	= -Wall -Werror -Wextra -O3

RM	= rm -f

NAME	= gnl.a

$(OBJDIR)%.o: %.c
	mkdir -p $(OBJDIR)
	gcc $(CFLAGS) -c $< -o $@ -I ./re

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re

.SILENT: all fclean re clean $(NAME) $(OBJDIR)%.o $(OBJS)
