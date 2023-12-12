/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <rmount@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:10:16 by jmarks            #+#    #+#             */
/*   Updated: 2023/12/11 14:41:26 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	find_player(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < ft_strlen(map->map[i]))
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S' \
				|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				map->player_x = i;
				map->player_y = j;
				map->player_dir = map->map[i][j];
				return ;
			}
		}
	}
}

/* 0.66  is the 2D raycaster version of camera plane */

void	assign_player_dir(t_player *player, int direction)
{
	if (direction == DIR_NORTH)
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_y = 0.66;
	}
	else if (direction == DIR_SOUTH)
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_y = -0.66;
	}
	else if (direction == DIR_EAST)
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = 0.66;
	}
	else if (direction == DIR_WEST)
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = -0.66;
	}
}

t_player	init_player(t_map map)
{
	t_player	player;

	player.plane_x = 0;
	player.plane_y = 0;
	if (map.player_dir == 'N')
		assign_player_dir(&player, DIR_NORTH);
	else if (map.player_dir == 'S')
		assign_player_dir(&player, DIR_SOUTH);
	else if (map.player_dir == 'E')
		assign_player_dir(&player, DIR_EAST);
	else if (map.player_dir == 'W')
		assign_player_dir(&player, DIR_WEST);
	player.pos_x = map.player_x + 0.5;
	player.pos_y = map.player_y + 0.5;
	player.old_dir_x = 0;
	player.old_plane_x = 0;
	return (player);
}
