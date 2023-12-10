/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:06:09 by jmarks            #+#    #+#             */
/*   Updated: 2023/12/11 07:18:41 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

int	check_file_format(char *file, char *file_format)
{
	char	*dot;

	dot = ft_strrchr(file, '.');
	if (dot != NULL && !ft_strcmp(dot, file_format))
		return (0);
	return (1);
}

bool	validate_chr(t_map map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map.height)
	{
		j = -1;
		while (++j < (int)ft_strlen(map.map[i]))
		{
			if (!ft_strchr("01NSEW", map.map[i][j]))
			{
				error_mess("Invalid character in map file");
				return (false);
			}
			if (ft_strchr("NSEW", map.map[i][j]))
				map.p_element += 1;
		}
	}
	if (map.p_element != 1)
		error_mess("No player or too many players detected");
	return (true);
}

void	check_walls(t_map map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map.height)
	{
		if (map.map[i][0] != '1' || map.map[i][map.width - 1] != '1')
		{
			printf("%i = %c, %i = %c\n", i, map.map[i][0], j, map.map[i][map.width - 1]);
			error_mess("Missing wall/s on the left or right.");
		}
		i++;
	}
	while (j < map.width)
	{
		if (map.map[0][j] != '1' || map.map[map.height - 1][j] != '1')
		{
			error_mess("Missing wall/s on the top or bottom.");
		}
		j++;
	}
}

