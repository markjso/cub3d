/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:44:54 by jmarks            #+#    #+#             */
/*   Updated: 2023/12/14 16:04:51 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	draw_square(t_mlx *cube, int x, int y, int colour)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_MULT)
	{
		j = 0;
		while (j < MINIMAP_MULT)
		{
			get_pixel_colour(cube, x + i, y + j, colour);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_mlx *cube)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cube->map.height)
	{
		j = -1;
		while (++j < ft_strlen(cube->map.map[i]))
		{
			if (cube->map.map[i][j] == '1')
				draw_square(cube, j * MINIMAP_MULT + 10, i * MINIMAP_MULT + 10,
					create_rgb(0, 0, 0));
			if (cube->map.map[i][j] == '0')
				draw_square(cube, j * MINIMAP_MULT + 10, i * MINIMAP_MULT + 10,
					create_rgb(255, 255, 255));
		}
	}
	draw_square(cube, (int)cube->player.pos_y * MINIMAP_MULT + 10,
		(int)cube->player.pos_x * MINIMAP_MULT + 10, create_rgb(255, 255, 0));
}
