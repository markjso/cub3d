/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:10:16 by jmarks            #+#    #+#             */
/*   Updated: 2023/11/24 14:10:19 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_dir(t_mlx *cube, char c)
{
	if (c == 'N')
		cube->player.angle = PI3 + 0.00001;
	else if (c == 'S')
		cube->player.angle = PI2 + 0.00001;
	else if (c == 'E')
		cube->player.angle = PII + 0.00001;
	else if (c == 'W')
		cube->player.angle = PI + 0.00001;
	else
		cube->player.angle = PI3 + 0.00001;
	cube->player.dir_x = cos(cube->player.angle) * 5;
	printf("player.dir_x is %f\n", cube->player.dir_x);
	cube->player.dir_y = sin(cube->player.angle) * 5;
	printf("player.dir_y is %f\n", cube->player.dir_y);
}

void	init_player(t_mlx *cube)
{
	int	i;
	int	j;

	i = -1;
	while (++i < (int)cube->map.height)
	{
		j = -1;
		while (++j < (int)cube->map.width)
		{
			if (ft_strchr("NSEW", cube->map.map[i][j]))
			{
				if (cube->map.map[i][j] == '\0')
					break ;
				cube->player.pos_x = j;
				printf("player.pos_x is %f\n", cube->player.pos_x);
				cube->player.pos_y = i;
				printf("player.pos_y is %f\n", cube->player.pos_y);
				cube->player.fov = 1;
				init_player_dir(cube, cube->map.map[i][j]);
				return ;
			}
		}
	}
}
