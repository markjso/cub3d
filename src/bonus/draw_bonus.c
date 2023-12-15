/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <rmount@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:07:11 by jmarks            #+#    #+#             */
/*   Updated: 2023/12/11 13:20:39 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	draw_floor_ceiling(t_mlx *cube, int x, int from)
{
	int	y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		if (y <= from)
			get_pixel_colour(cube, x, y, cube->elements.ceiling);
		else
			get_pixel_colour(cube, x, y, cube->elements.floor);
	}
}

void	apply_texture(t_mlx *cube, int direction, int x)
{
	int	colour;

	colour = ft_mlx_pixel_put(&cube->elements.wall_tex[direction], \
		cube->raycast.tex_x, cube->raycast.tex_y);
	get_pixel_colour(cube, x, cube->raycast.draw_from, colour);
}

static void	calc_tex_positions(t_mlx *cube)
{
	t_raycast	*ray;

	ray = &cube->raycast;
	if (!ray->side)
		ray->tex_wall_x = cube->player.pos_y + ray->perp_wall_dist \
			* ray->ray_dir_y;
	else
		ray->tex_wall_x = cube->player.pos_x + ray->perp_wall_dist \
			* ray->ray_dir_x;
	ray->tex_wall_x -= floor(ray->tex_wall_x);
	ray->tex_x = ray->tex_wall_x * TEX_WIDTH;
	if (!ray->side && ray->ray_dir_x > 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	if (ray->side && ray->ray_dir_y < 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	ray->tex_step = 1.0 * TEX_HEIGHT / ray->line_height;
	ray->tex_pos = (ray->draw_from - WIN_HEIGHT / 2 \
		+ ray->line_height / 2) * ray->tex_step;
}

void	draw_textures(t_mlx *cube, int x)
{
	t_raycast	*ray;

	ray = &cube->raycast;
	calc_tex_positions(cube);
	draw_floor_ceiling(cube, x, ray->draw_from);
	while (ray->draw_from++ < ray->draw_to)
	{
		ray->tex_y = (int)ray->tex_pos & (TEX_HEIGHT - 1);
		ray->tex_pos += ray->tex_step;
		if (!ray->side && cube->player.pos_x < ray->map_x)
			apply_texture(cube, DIR_SOUTH, x);
		else if (!ray->side && cube->player.pos_x > ray->map_x)
			apply_texture(cube, DIR_NORTH, x);
		else if (ray->side && cube->player.pos_y < ray->map_y)
			apply_texture(cube, DIR_EAST, x);
		else if (ray->side && cube->player.pos_y > ray->map_y)
			apply_texture(cube, DIR_WEST, x);
	}
}

int	img_renderer(t_mlx *cube)
{
	mlx_destroy_image(cube->mlx, cube->img);
	cube->img = mlx_new_image(cube->mlx, WIN_WIDTH, WIN_HEIGHT);
	cube->addr = mlx_get_data_addr(cube->img, &cube->bits_per_pixel,
			&cube->line_length, &cube->endian);
	ft_raycast(cube);
	draw_minimap(cube);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->img, 0, 0);
	return (0);
}
