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
	printf("rgb %s\n", rgb_code);
	printf("identifier is %s\n", identifier);
	char	**rgb_decoded;
	int		*rgb;

	rgb = malloc(sizeof(int) * 3);
	rgb_code = rgb_code + ft_strlen(identifier);
	rgb_decoded = ft_split(rgb_code, ',');
	rgb[0] = ft_atoi(rgb_decoded[0]);
	rgb[1] = ft_atoi(rgb_decoded[1]);
	rgb[2] = ft_atoi(rgb_decoded[2]);
	if ((rgb[0] < 0 || rgb[0] > 255)
		|| (rgb[1] < 0 || rgb[1] > 255)
		|| (rgb[2] < 0 || rgb[2] > 255))
	{
		write(1, "RGB VALUES ARE INCORRECT, RESETING VALUES\n", 43);
		rgb[0] = 42;
		rgb[1] = 42;
		rgb[2] = 42;
	}
	ft_clean_arr(rgb_decoded);
	rgb_decoded = NULL;
	return (rgb);
}