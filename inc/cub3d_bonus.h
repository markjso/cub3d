/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:56:18 by rmount            #+#    #+#             */
/*   Updated: 2023/12/14 20:56:23 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <math.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <stdbool.h>
# include "../mlx/mlx.h"
# include <sys/wait.h>
# include "../libft/libft.h"

# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define ESC 53
# define LOOK_LEFT 123
# define LOOK_RIGHT 124
# define WIN_WIDTH 1280
# define WIN_HEIGHT 800
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define DIR_NORTH		0
# define DIR_SOUTH		1
# define DIR_WEST		2
# define DIR_EAST		3
# define MOVE_SPEED 0.125
# define ROT_SPEED 0.075
# define MINIMAP_MULT 10

/*
**	=============
**	 Structures
**	=============
*/

typedef struct s_mlx	t_mlx;

typedef struct s_player
{
	double	dir_x;
	double	dir_y;
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
	double	old_dir_x;
	double	old_plane_x;
}				t_player;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	int		player_x;
	int		player_y;
	int		p_element;
	char	player_dir;
	bool	valid;
}				t_map;

typedef struct s_raycast
{
	int		side;
	int		wall_hit;
	int		line_height;
	int		tex_x;
	int		tex_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		draw_from;
	int		draw_to;
	double	tex_step;
	double	tex_pos;
	double	tex_wall_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
}				t_raycast;

typedef struct s_elements
{
	t_mlx	*wall_tex;
	int		floor;
	int		ceiling;
}	t_elements;

typedef struct s_mlx
{
	t_map		map;
	t_player	player;
	t_elements	elements;
	t_raycast	raycast;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_mlx;

/*
**	=============
**		Files
**	=============
*/

/*
**	Initialise
*/
t_mlx		*init_mlx(char *filepath);
t_raycast	init_raycast(void);

/*
**	Parse
*/
void		ft_normalise_width(t_map map);
t_map		map_parser(char *path);
bool		ft_map_valid(t_map map);
int			do_file(char *path);

/*
**	Checks
*/
int			check_file_format(char *file, char *file_format);
bool		validate_chr(t_map map);
//void		validate_map(t_mlx *cube);
bool		check_valid_line(char *line, char *delete);
//void		check_walls(t_map map);
//bool		ft_is_valid_map_char(char c);
void		ft_free_map(t_mlx *cube);

/*
** Floodfill
*/
bool		map_can_be_exited(t_map map);
bool		fl_visited_boundary(bool **visited, t_map map);
void		fl_init_visited(bool **visited, t_map map);
void		floodfill(t_map map, bool **visited, int i, int j);
void		fl_find_player(t_map map, int *sr, int *sc);
void		fl_free(bool **visited, t_map map);

/*
**	Move
*/
int			keypress(int keycode, t_mlx *cube);

/*
**	Utils
*/
int			dir_from_id(char *identifier);
double		ft_abs(double x);
char		*ft_free_to_trim(char *s1, const char *set);
int			ft_strslen(char **strs);
char		**ft_strsjoin(char **strs, char *str);
char		*ft_strjoin_and_free(char *s1, char *s2);

/*
**	Draw
*/
void		get_pixel_colour(t_mlx *cube, int x, int y, int rgb);
int			ft_mlx_pixel_put(t_mlx *cube, int x, int y);
int			img_renderer(t_mlx *cube);
void		draw_floor_ceiling(t_mlx *cube, int x, int from);
void		draw_textures(t_mlx *cube, int x);
t_elements	parse_elements(t_mlx *cube, char *path);
void		ft_raycast(t_mlx *cube);
int			create_rgb(int r, int g, int b);
int			*save_rgb(char *identifier, char *rgb_code);
bool		is_colour_empty(char *rgb_code);
void		free_temp_string(char **rgb_split);
bool		is_format_error(char **rgb_split);

/*
**	Error handling
*/
void		error_mess(char *msg);
void		ft_clean_arr(char **arr);
int			quit(char *msg, t_mlx *cube);
int			leave(t_mlx *cube);

/*
**	Player
*/
void		find_player(t_map *map);
t_player	init_player(t_map map);

/*
**	Map
*/
t_map		init_map(void);
char		*get_next_line(int fd);
int			is_dir_char(char letter);
void		draw_minimap(t_mlx *cube);

#endif
