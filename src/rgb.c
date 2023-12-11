/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:53:05 by jmarks            #+#    #+#             */
/*   Updated: 2023/11/30 13:53:08 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	*save_rgb(char *identifier, char *rgb_code)
{
	char	**rgb_split;
	int		*rgb;

	rgb = malloc(sizeof(int) * 3);
	rgb_code = rgb_code + ft_strlen(identifier);
	rgb_split = ft_split(rgb_code, ',');
	rgb[0] = ft_atoi(rgb_split[0]);
	rgb[1] = ft_atoi(rgb_split[1]);
	rgb[2] = ft_atoi(rgb_split[2]);
	if ((rgb[0] < 0 || rgb[0] > 255)
		|| (rgb[1] < 0 || rgb[1] > 255)
		|| (rgb[2] < 0 || rgb[2] > 255))
	error_mess("Not a valid rgb number");
	ft_clean_arr(rgb_split);
	rgb_split = NULL;
	return (rgb);
}