NAME = cub3d

MLX_DIR = mlx

SRC =		src/parse.c \
			src/rgb.c \
			src/elements.c \
			src/checks.c \
			src/draw.c \
			src/error.c \
			src/get_next_line.c \
			src/player.c \
			src/movement.c \
			src/raycast.c \
			src/cub3d.c \
			src/initialise.c \
			src/utils.c \
			src/draw_utils2.c
	
OBJS=$(SRC:.c=.o)

CC=gcc

LIBFT=libft/libft.a

LIBFT_LIB_DIR = libft

CFLAGS=-Wall -Wextra -Werror -Iincludes/ -Ilibft/

MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LIBFT)

$(LIBFT_LIB_DIR):
	$(MAKE) -C $(LIBFT_LIB_DIR)

${LIBFT}:
	$(MAKE) -C ${LIBFT_LIB_DIR}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_LIB_DIR)
	rm -f $(OBJS)

fclean:	clean
	make fclean -C $(LIBFT_LIB_DIR)
	rm -f $(NAME)

re:	fclean all

.PHONY:	all	clean fclean re