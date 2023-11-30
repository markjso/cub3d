/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:16:25 by jmarks            #+#    #+#             */
/*   Updated: 2023/11/24 14:16:27 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	keypress(int keycode, t_mlx *cube)
{
	if (keycode == ESC)
		leave(cube);
	player(cube, keycode);
	return (0);
}

void	strafe_left(t_mlx *c, int keycode)
{
	if (keycode == LEFT)
	{
		if (c->player.angle > 0 && c->player.angle < PI)
		{
			c->player.pos_x -= cos(c->player.angle + PI / 2) / TILE_SIZE;
			c->player.pos_y -= sin(c->player.angle + PI / 2) / TILE_SIZE;
		}
		else
		{
			c->player.pos_x += cos(c->player.angle - PI / 2) / TILE_SIZE;
			c->player.pos_y += sin(c->player.angle - PI / 2) / TILE_SIZE;
		}
	}
}

void	strafe_right(t_mlx *c, int keycode)
{
	if (keycode == RIGHT)
	{
		if (c->player.angle > 0 && c->player.angle < PI)
		{
			c->player.pos_x -= cos(c->player.angle - PI / 2) / TILE_SIZE;
			c->player.pos_y -= sin(c->player.angle - PI / 2) / TILE_SIZE;
		}
		else
		{
			c->player.pos_x += cos(c->player.angle + PI / 2) / TILE_SIZE;
			c->player.pos_y += sin(c->player.angle + PI / 2) / TILE_SIZE;
		}
	}
}

void	move_player(t_mlx *c, int keycode)
{
	t_player	tmp;
	int		floor_x;
	int		floor_y;

	tmp.x = c->player.pos_x;
	tmp.y = c->player.pos_y;
	if (keycode == UP)
	{
		c->player.pos_y += (c->player.dir_y / TILE_SIZE) * 0.5;
		c->player.pos_x += (c->player.dir_x / TILE_SIZE) * 0.5;
	}
	if (keycode == DOWN)
	{
		c->player.pos_y -= c->player.dir_y / TILE_SIZE;
		c->player.pos_x -= c->player.dir_x / TILE_SIZE;
	}
	strafe_left(c, keycode);
	strafe_right(c, keycode);
	floor_x = (int)floor(c->player.pos_x);
	floor_y = (int)floor(c->player.pos_y);
	if (c->map.map[floor_y][floor_x] == '1')
	{
		c->player.pos_x = tmp.x;
		c->player.pos_y = tmp.y;
	}
}