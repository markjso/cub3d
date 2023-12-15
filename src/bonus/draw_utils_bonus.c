/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <rmount@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:09:56 by jmarks            #+#    #+#             */
/*   Updated: 2023/12/11 13:08:53 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

char	**ft_strsjoin(char **strs, char *str)
{
	int		i;
	char	**new_strs;

	i = 0;
	new_strs = malloc(sizeof(char *) * (ft_strslen(strs) + 2));
	if (!new_strs)
		error_mess("malloc error");
	while (strs[i])
	{
		new_strs[i] = strs[i];
		i++;
	}
	new_strs[i] = str;
	new_strs[i + 1] = NULL;
	free(strs);
	return (new_strs);
}

void	get_pixel_colour(t_mlx *cube, int x, int y, int rgb)
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
	return (*(unsigned int *)dst);
}
