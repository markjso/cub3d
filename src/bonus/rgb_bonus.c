/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <rmount@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:53:05 by jmarks            #+#    #+#             */
/*   Updated: 2023/12/15 09:53:04 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	free_temp_string(char **rgb_split)
{
	char	*temp;

	temp = rgb_split[0];
	rgb_split[0] = ft_strtrim(rgb_split[0], " ");
	free(temp);
	temp = rgb_split[1];
	rgb_split[1] = ft_strtrim(rgb_split[1], " ");
	free(temp);
	temp = rgb_split[2];
	rgb_split[2] = ft_strtrim(rgb_split[2], " ");
	free(temp);
}

bool	is_format_error(char **rgb_split)
{
	if (ft_strlen(rgb_split[0]) == 0 || is_colour_empty(rgb_split[0])
		|| ft_strlen(rgb_split[1]) == 0 || is_colour_empty(rgb_split[1])
		|| ft_strlen(rgb_split[2]) == 0 || is_colour_empty(rgb_split[2])
		|| rgb_split[3] != NULL)
	{
		return (true);
	}
	return (false);
}

bool	is_colour_empty(char *rgb_code)
{
	if (rgb_code == NULL || ft_strchr(rgb_code, '\t'))
	{
		return (true);
	}
	return (false);
}

int	*save_rgb(char *identifier, char *rgb_code)
{
	char	**rgb_split;
	int		*rgb;

	rgb = malloc(sizeof(int) * 3);
	rgb_code = rgb_code + ft_strlen(identifier);
	rgb_split = ft_split(rgb_code, ',');
	free_temp_string(rgb_split);
	if (is_format_error(rgb_split))
		error_mess("rgb format error");
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
