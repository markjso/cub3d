/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:30:46 by jmarks            #+#    #+#             */
/*   Updated: 2023/11/30 15:30:48 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_ray_directions(t_mlx *cube, int x)
{
	t_raycast	*ray;
	double 		camera_x;

	ray = &cube->raycast;
	camera_x = (2 * x / (double)WIN_WIDTH - 1);
	ray->ray_dir_x = cube->player.dir_x + cube->player.plane_x 
			* camera_x;
	ray->ray_dir_y = cube->player.dir_y + cube->player.plane_y
			* camera_x;
	ray->map_x = (int) cube->player.pos_x;
	ray->map_y = (int) cube->player.pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = ft_abs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = ft_abs(1 / ray->ray_dir_y);
}

static void	calculate_dda(t_mlx *cube)
{
	t_raycast	*ray;

	ray = &cube->raycast;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cube->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cube->player.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cube->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cube->player.pos_y)
			* ray->delta_dist_y;
	}
}

void	perform_dda(t_mlx *cube)
{
	t_raycast	*ray;

	ray = &cube->raycast;
	ray->wall_hit = 0;
	while (!ray->wall_hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cube->map.map[ray->map_x][ray->map_y] == '1')
			ray->wall_hit = 1;
	}
	if (!ray->side)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

static void	calc_line_height(t_mlx *cube)
{
	t_raycast	*ray;

	ray = &cube->raycast;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_from = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_from < 0)
		ray->draw_from = 0;
	ray->draw_to = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_to >= WIN_HEIGHT)
		ray->draw_to = WIN_HEIGHT - 1;
}

void	ft_raycast(t_mlx *cube)
{
	int	x;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		calc_ray_directions(cube, x);
		calculate_dda(cube);
		perform_dda(cube);
		calc_line_height(cube);
		draw_textures(cube, x);
	}
}
