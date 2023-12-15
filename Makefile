NAME = cub3D

MLX_DIR = mlx

SRC_M			= parse.c \
			rgb.c \
			elements.c \
			checks.c \
			draw.c \
			error.c \
			floodfill.c \
			floodfill_utils.c \
			get_next_line.c \
			player.c \
			movement.c \
			raycast.c \
			cub3d.c \
			initialise.c \
			utils.c \
			draw_utils.c
SRC_M_D=$(addprefix mandatory/,$(SRC_M))

SRC_B		= parse_bonus.c \
			rgb_bonus.c \
			elements_bonus.c \
			checks_bonus.c \
			draw_bonus.c \
			error_bonus.c \
			floodfill_bonus.c \
			floodfill_utils_bonus.c \
			get_next_line_bonus.c \
			player_bonus.c \
			movement_bonus.c \
			raycast_bonus.c \
			cub3d_bonus.c \
			initialise_bonus.c \
			utils_bonus.c \
			minimap_bonus.c \
			draw_utils_bonus.c
SRC_BONUS_D=$(addprefix bonus/,$(SRC_B))

SRC_DIR=$(addprefix src/,$(SRC_M_D))
BONUS_SRC=$(addprefix src/,$(SRC_BONUS_D))

OBJS=$(SRC_DIR:.c=.o)
BONUS_OBJS=$(BONUS_SRC:.c=.o)

CC=gcc

MLX=mlx/libmlx.a

LIBFT=libft/libft.a

LIBFT_LIB_DIR = libft

CFLAGS=-Wall -Wextra -Werror -Iinc/ -Ilibft/ -Imlx

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

bonus: $(OBJS) $(BONUS_OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJS) $(MLX_FLAGS) $(LIBFT) $(MLX)

clean:
	make clean -C $(LIBFT_LIB_DIR) 
	make clean -C $(MLX_DIR) 
	rm -f $(OBJS) $(BONUS_OBJS)

fclean:	clean
	make fclean -C $(LIBFT_LIB_DIR) 
	rm -f $(NAME)

re:	fclean all

.PHONY:	all	clean fclean re
