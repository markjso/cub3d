/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:50:38 by jibanez-          #+#    #+#             */
/*   Updated: 2023/11/22 13:38:31 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

/*
**	=============
**	 Structures
**	=============
*/

typedef struct s_mlx  t_mlx;

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
**	Main
*/
t_mlx		*init_mlx(char *filepath);
t_raycast	init_raycast();

/*
**	Parse
*/
void		read_map(t_map *map, int fd);
void		scan_map(t_mlx *cube, char *line);
t_map		map_parser(char *path);
t_elements	parse_elements(t_mlx *cube, char *path);

/*
**	Checks
*/
int			check_file_format(char *file, char *file_format);
bool		validate_chr(t_map map);
void		validate_map(t_mlx *cube);
int			check_valid_line(char *line);
void		check_walls(t_map map);

/*
**	Move
*/
int			keypress(int keycode, t_mlx *cube);

/*
**	Utils
*/
int			dir_from_id(char *identifier);
double		ft_abs(double x);
// char	*ft_free_to_trim(char *s1, const char *set);

/*
**	Draw
*/
void		get_pixel_colour(t_mlx *cube, int x, int y, int rgb);
int			ft_mlx_pixel_put(t_mlx *cube, int x, int y);
int			img_renderer(t_mlx *cube);
void		draw_floor_ceiling(t_mlx *cube, int x, int from);
void		draw_textures(t_mlx *cube, int x);
void		ft_raycast(t_mlx *cube);
int			create_rgb(int r, int g, int b);
int			*save_rgb(char *identifier, char *rgb_code);

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
int			ft_add_str_to_arr(char *str, t_mlx *cube);
void		init_map(t_map *map);
void		get_width(t_map *map);
char		*get_next_line(int fd);

#endif
