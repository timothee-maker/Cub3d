NAME	= Cub3d
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
INCLUDE	= -I includes -I libft -I minilibx-linux
MLX	= minilibx-linux/libmlx_Linux.a minilibx-linux/libmlx.a
LIBFT	= libft/libft.a
OBJS	= $(patsubst srcs/%.c, objs/%.o, $(SRCS))
DEPS	= $(wildcard includes/*.h)

SRCS_FILES = main player hook formule parsing mlx_utils init
SRCS := $(addprefix srcs/, $(addsuffix .c, $(SRCS_FILES)))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -Llibft -lft -Lminilibx-linux -lmlx -lXext -lX11 -lm -o $(NAME)

$(LIBFT):
	make -C libft

$(MLX):
	@if [ ! -f minilibx-linux/libmlx_Linux.a ] && [ ! -f minilibx-linux/libmlx.a ]; then \
		make -C minilibx-linux; \
	fi


objs/%.o: srcs/%.c $(DEPS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf objs
	make -C libft clean
	make -C minilibx-linux clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean
	make -C minilibx-linux clean

re: fclean all

.PHONY: all clean fclean re
