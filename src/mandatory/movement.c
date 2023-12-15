/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <rmount@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:16:25 by jmarks            #+#    #+#             */
/*   Updated: 2023/12/11 13:58:28 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_wall(float x, float y, t_mlx *cube)
{
	char	**worldmap;

	if (!cube->map.map)
		error_mess("map not found");
	worldmap = cube->map.map;
	if (worldmap[(int)x][(int)y] == '1')
		return (0);
	else
		return (1);
}

void	move_up_down(int keycode, t_mlx *cube)
{
	if (keycode == UP)
	{
		if (is_wall(cube->player.pos_x + cube->player.dir_x * \
				(MOVE_SPEED + 0.1), cube->player.pos_y, cube) == 1)
			cube->player.pos_x += cube->player.dir_x * MOVE_SPEED;
		if (is_wall(cube->player.pos_x, cube->player.pos_y + \
				cube->player.dir_y * (MOVE_SPEED + 0.1), cube) == 1)
			cube->player.pos_y += cube->player.dir_y * MOVE_SPEED;
	}
	if (keycode == DOWN)
	{
		if (is_wall(cube->player.pos_x - cube->player.dir_x * \
				(MOVE_SPEED + 0.1), cube->player.pos_y, cube) == 1)
			cube->player.pos_x -= cube->player.dir_x * MOVE_SPEED;
		if (is_wall(cube->player.pos_x, cube->player.pos_y - \
				cube->player.dir_y * (MOVE_SPEED + 0.1), cube) == 1)
			cube->player.pos_y -= cube->player.dir_y * MOVE_SPEED;
	}
}

void	move_left_right(int keycode, t_mlx *cube)
{
	if (keycode == LEFT)
	{
		if (is_wall(cube->player.pos_x - cube->player.dir_y * \
				(MOVE_SPEED + 0.1), cube->player.pos_y, cube) == 1)
			cube->player.pos_x -= cube->player.dir_y * MOVE_SPEED;
		if (is_wall(cube->player.pos_x, cube->player.pos_y + \
				cube->player.dir_x * (MOVE_SPEED + 0.1), cube) == 1)
			cube->player.pos_y += cube->player.dir_x * MOVE_SPEED;
	}
	if (keycode == RIGHT)
	{
		if (is_wall(cube->player.pos_x + cube->player.dir_y * \
				(MOVE_SPEED + 0.1), cube->player.pos_y, cube) == 1)
			cube->player.pos_x += cube->player.dir_y * MOVE_SPEED;
		if (is_wall(cube->player.pos_x, cube->player.pos_y - \
				cube->player.dir_x * (MOVE_SPEED + 0.1), cube) == 1)
			cube->player.pos_y -= cube->player.dir_x * MOVE_SPEED;
	}
}

void	rotate_left_right(int keycode, t_mlx *cube)
{
	cube->player.old_dir_x = cube->player.dir_x;
	cube->player.old_plane_x = cube->player.plane_x;
	if (keycode == LOOK_LEFT)
	{
		cube->player.dir_x = cube->player.dir_x * cos(ROT_SPEED) - \
			cube->player.dir_y * sin(ROT_SPEED);
		cube->player.dir_y = cube->player.old_dir_x * sin(ROT_SPEED) + \
			cube->player.dir_y * cos(ROT_SPEED);
		cube->player.plane_x = cube->player.plane_x * cos(ROT_SPEED) - \
			cube->player.plane_y * sin(ROT_SPEED);
		cube->player.plane_y = cube->player.old_plane_x * sin(ROT_SPEED) + \
			cube->player.plane_y * cos(ROT_SPEED);
	}
	if (keycode == LOOK_RIGHT)
	{
		cube->player.dir_x = cube->player.dir_x * cos(-ROT_SPEED) - \
			cube->player.dir_y * sin(-ROT_SPEED);
		cube->player.dir_y = cube->player.old_dir_x * sin(-ROT_SPEED) + \
			cube->player.dir_y * cos(-ROT_SPEED);
		cube->player.plane_x = cube->player.plane_x * cos(-ROT_SPEED) - \
			cube->player.plane_y * sin(-ROT_SPEED);
		cube->player.plane_y = cube->player.old_plane_x * sin(-ROT_SPEED) + \
			cube->player.plane_y * cos(-ROT_SPEED);
	}
}

int	keypress(int keycode, t_mlx *cube)
{
	if (keycode == ESC)
		leave(cube);
	rotate_left_right(keycode, cube);
	move_up_down(keycode, cube);
	move_left_right(keycode, cube);
	img_renderer(cube);
	return (0);
}
