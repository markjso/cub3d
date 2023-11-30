/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:07:11 by jmarks            #+#    #+#             */
/*   Updated: 2023/11/24 14:07:21 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_pixel(t_mlx *cube, int rgb, int x, int y)
{
	char	*dst;
	if (y < 0 || x < 0 || y > WIN_HEIGHT || x > WIN_WIDTH)
		return ;
	dst = cube->addr + (y * cube->line_length + x
							* (cube->bits_per_pixel / 8));
		*(unsigned int *) dst = rgb;
}

int	ft_mlx_pixel_put(t_mlx *cube, int x, int y)
{
	char	*dst;

	dst = cube->addr + (y * cube->line_length + x * (cube->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void	draw_floor_ceiling(t_mlx *cube)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (y > (WIN_HEIGHT / 2))
				add_pixel(cube, cube->elements.floor, x, y);
			else if (y < (WIN_HEIGHT / 2))
				add_pixel(cube, cube->elements.ceiling, x, y);
		}
	}
}

void	ft_apply_texture(t_mlx *cube, int direction, int x)
{
	int	colour;

	colour = ft_mlx_pixel_put(&cube->elements.wall_tex[direction], \
		cube->raycast.tex_x, cube->raycast.tex_y);
	add_pixel(cube, colour, x, cube->raycast.draw_from);
}

static void	ft_calc_tex_positions(t_mlx *cube)
{
	t_raycast	*ray;

	ray = &cube->raycast;
	if (!ray->hit)
		ray->tex_wall_x = cube->player.pos_y + ray->perp_wall_dist \
			* ray->ray_dir_y;
	else
		ray->tex_wall_x = cube->player.pos_x + ray->perp_wall_dist \
			* ray->ray_dir_x;
	ray->tex_wall_x -= floor(ray->tex_wall_x);
	ray->tex_x = ray->tex_wall_x * TEX_WIDTH;
	if (!ray->hit && ray->ray_dir_x > 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	if (ray->hit && ray->ray_dir_y < 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	ray->tex_step = 1.0 * TEX_HEIGHT / ray->line_height;
	ray->tex_pos = (ray->draw_from - WIN_HEIGHT / 2 \
		+ ray->line_height / 2) * ray->tex_step;
}

void	draw_textures(t_mlx *cube, int x)
{
	t_raycast	*ray;

	ray = &cube->raycast;
	ft_calc_tex_positions(cube);
	while (ray->draw_from++ < ray->draw_to)
	{
		ray->tex_y = (int)ray->tex_pos & (TEX_HEIGHT - 1);
		ray->tex_pos += ray->tex_step;
		if (!ray->hit && cube->player.pos_x < ray->map_x)
			ft_apply_texture(cube, DIR_SOUTH, x);
		else if (!ray->hit && cube->player.pos_x > ray->map_x)
			ft_apply_texture(cube, DIR_NORTH, x);
		else if (ray->hit && cube->player.pos_y < ray->map_y)
			ft_apply_texture(cube, DIR_EAST, x);
		else if (ray->hit && cube->player.pos_y > ray->map_y)
			ft_apply_texture(cube, DIR_WEST, x);
	}
}

int	ft_img_renderer(t_mlx *cube)
{
	mlx_destroy_image(cube->mlx, cube->img);
	cube->img = mlx_new_image(cube->mlx, WIN_WIDTH, WIN_HEIGHT);
	cube->addr = mlx_get_data_addr(cube->img, &cube->bits_per_pixel,
			&cube->line_length, &cube->endian);
	// ft_raycast(cube);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->img, 0, 0);
	return (0);
}