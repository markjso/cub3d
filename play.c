/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:08:26 by jmarks            #+#    #+#             */
/*   Updated: 2023/11/24 14:08:30 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_loop(t_mlx *c)
{
	// t_coord	p;
	// t_coord	d;

	// p.x = (c->player.pos_x * (TILE_SIZE / 2));
	// p.y = (c->player.pos_y * (TILE_SIZE / 2));
	// d.x = p.x + c->player.dir_x * 5;
	// d.y = p.y + c->player.dir_y * 5;
	// blackout(c);
	draw_floor_ceiling(c);
	// draw_rays_2d(c);
	mlx_put_image_to_window(c->mlx, c->win, c->frame.img, 0, 0);
}

void	player(t_mlx *cube, int keycode)
{
	move_player(cube, keycode);
	if (keycode == LOOK_LEFT)
		cube->player.angle -= 0.0174533 * 5; //1 degree
	if (keycode == LOOK_RIGHT)
		cube->player.angle += 0.0174533 * 5; //1 degree
	fix_angle(&cube->player.angle);
	cube->player.dir_x = cos(cube->player.angle) * 5;
	cube->player.dir_y = sin(cube->player.angle) * 5;
	draw_loop(cube);
}

int	draw_frame(t_mlx *c)
{
	c->frame.img_width = WIN_WIDTH;
	c->frame.img_height = WIN_HEIGHT;
	c->frame.img = mlx_new_image(c->mlx, WIN_WIDTH, WIN_HEIGHT);
	c->frame.data = (int *)mlx_get_data_addr(c->frame.img,
			&c->frame.bpp, &c->frame.size_l, &c->frame.endian);
	draw_loop(c);
	return (0);
}
