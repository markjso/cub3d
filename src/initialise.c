/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <rmount@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:44:19 by jmarks            #+#    #+#             */
/*   Updated: 2023/12/11 13:57:14 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_map(t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->player_dir = 0;
	map->p_element = 0;
	map->valid = false;
}

t_raycast	init_raycast(void)
{
	t_raycast	ray;

	ray.ray_dir_x = 0;
	ray.ray_dir_y = 0;
	ray.line_height = 0;
	ray.draw_from = 0;
	ray.draw_to = 0;
	ray.map_x = 0;
	ray.map_y = 0;
	ray.tex_x = 0;
	ray.tex_y = 0;
	ray.tex_step = 0;
	ray.tex_pos = 0;
	ray.tex_wall_x = 0;
	ray.side_dist_x = 0;
	ray.side_dist_y = 0;
	ray.delta_dist_x = 0;
	ray.delta_dist_y = 0;
	ray.perp_wall_dist = 0;
	ray.step_x = 0;
	ray.step_y = 0;
	ray.side = 0;
	ray.wall_hit = 0;
	return (ray);
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
	cube->elements = parse_elements(cube, filepath);
	cube->map = map_parser(filepath);
	return (cube);
}
