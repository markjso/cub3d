/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:44:19 by jmarks            #+#    #+#             */
/*   Updated: 2023/11/30 13:44:25 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_mlx *cube)
{
	cube->map.height = 0;
	cube->map.width = 0;
	cube->map.rows = 0;
	cube->map.cols = 0;
	cube->map.valid = false;
}

void	init_raycast(t_mlx *cube)
{
	cube->raycast.ray_dir_x = 0;
	cube->raycast.ray_dir_y = 0;
	cube->raycast.line_height = 0;
	cube->raycast.draw_from = 0;
	cube->raycast.draw_to = 0;
	cube->raycast.map_x = 0;
	cube->raycast.map_y = 0;
	cube->raycast.tex_x = 0;
	cube->raycast.tex_y = 0;
	cube->raycast.tex_step = 0;
	cube->raycast.tex_pos = 0;
	cube->raycast.tex_wall_x = 0;
	cube->raycast.side_dist_x = 0;
	cube->raycast.side_dist_y = 0;
	cube->raycast.delta_dist_x = 0;
	cube->raycast.delta_dist_y = 0;
	cube->raycast.perp_wall_dist = 0;
	cube->raycast.step_x = 0;
	cube->raycast.step_y = 0;
	cube->raycast.hit = false;
	cube->raycast.wall_hit = false;
}

t_mlx	*init_mlx(char *filepath)
{
	t_mlx	*cube;

	cube = ft_calloc(1, sizeof(t_mlx));
	if (!cube)
		error_mess("struct cub3d malloc failed");
	cube->mlx = mlx_init();
	cube->win = mlx_new_window(cube->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	cube->img = mlx_new_image(cube->mlx, WIN_WIDTH, WIN_HEIGHT);
	cube->addr = mlx_get_data_addr(cube->img, &cube->bits_per_pixel, \
		&cube->line_length, &cube->endian);
	init_map(cube);
	cube->elements = parse_elements(cube, filepath);
	printf("able to parse elements\n");
	cube->map = map_parser(filepath);
	printf("able to parse map\n");
	init_player(cube);
	printf("able to initalise player\n");
	return (cube);
}
