NAME = cub3D

MLX_DIR = mlx

SRC =		src/parse.c \
			src/rgb.c \
			src/elements.c \
			src/checks.c \
			src/draw.c \
			src/error.c \
			src/floodfill.c \
			src/floodfill_utils.c \
			src/get_next_line.c \
			src/player.c \
			src/movement.c \
			src/raycast.c \
			src/cub3d.c \
			src/initialise.c \
			src/utils.c \
			src/draw_utils.c
	
OBJS=$(SRC:.c=.o)

CC=gcc

MLX=mlx/libmlx.a

LIBFT=libft/libft.a

LIBFT_LIB_DIR = libft

CFLAGS=-Wall -Wextra -Werror -Iinc/ -Ilibft/ -Imlx -g -O0

MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LIBFT) $(MLX)

$(LIBFT_LIB_DIR):
	$(MAKE) -C $(LIBFT_LIB_DIR)

${LIBFT}:
	$(MAKE) -C ${LIBFT_LIB_DIR}

${MLX}:
	$(MAKE) -C ${MLX_DIR} 2>/dev/null

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_LIB_DIR) 
	make clean -C $(MLX_DIR) 
	rm -f $(OBJS)

fclean:	clean
	make fclean -C $(LIBFT_LIB_DIR) 
	rm -f $(NAME)

re:	fclean all

.PHONY:	all	clean fclean re
