NAME := so_long

CC := gcc

CFLAGS := -Wall -Wextra -Werror -g

SOURCE := src/controls.c src/map_check.c src/render.c \
			src/map.c src/so_long.c src/path_check.c inc/get_next_line.c

LIBFT := inc/libft/libft.a
PRINTF := inc/ft_printf/ft_printf.a
MINILIBX := minilibx/
MINILIBX_FLAGS := -L$(MINILIBX) -lmlx -L/usr/lib/X11 -lXext -lX11

OBJS := $(SOURCE:.c=.o)

all: libft printf minilibx $(NAME)

libft:
	@make -C inc/libft

printf:
	@make -C inc/ft_printf

minilibx:
	@make -C $(MINILIBX)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) \
	$(MINILIBX_FLAGS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	
fclean: clean
	@rm -rf $(NAME)
	@make clean -C $(MINILIBX)
	@make fclean -C inc/libft
	@make fclean -C inc/ft_printf

re: fclean all

.PHONY: all libft printf minilibx clean fclean re