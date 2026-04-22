NAME    = cub3D
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
MLX_DIR = code/mlx_linux
MLX_URL = https://github.com/42Paris/minilibx-linux.git
MLX     = $(MLX_DIR)/libmlx_Linux.a
LIBFT   = libft/libft.a
LIBS    = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

SRCS    = code/src/main.c \
          code/src/init/init.c \
          code/src/parsing/parse_file.c \
          code/src/parsing/parse_map.c \
          code/src/parsing/parse_textures.c \
          code/src/parsing/validate_map.c \
          code/src/engine/raycaster.c \
          code/src/engine/render.c \
          code/src/engine/textures.c \
          code/src/player/movement.c \
          code/src/player/hooks.c \
          code/src/utils/cleanup.c

OBJS    = $(SRCS:.c=.o)

all: $(MLX) $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(MLX):
	rm -rf $(MLX_DIR)
	git clone $(MLX_URL) $(MLX_DIR)
	make -C $(MLX_DIR)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -I code/includes -I $(MLX_DIR) -c $< -o $@

clean:
	make -C libft clean
	make -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -rf $(MLX_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re