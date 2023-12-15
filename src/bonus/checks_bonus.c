/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:06:09 by jmarks            #+#    #+#             */
/*   Updated: 2023/12/14 16:42:28 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	check_file_format(char *file, char *file_format)
{
	char	*dot;

	dot = ft_strrchr(file, '.');
	if (dot != NULL && !ft_strcmp(dot, file_format))
		return (0);
	return (1);
}

void	ft_free_map(t_mlx *cube)
{
	int	i;

	i = -1;
	while (++i < cube->map.height)
		free(cube->map.map[i]);
	free(cube->map.map);
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

bool	check_valid_line(char *line, char *delete)
{
	int	i;

	i = -1;
	free (delete);
	while (line[++i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			break ;
		i++;
	}
	if (i >= (int)ft_strlen(line))
		return (false);
	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ')
			line[i] = '1';
	}
	return (true);
}
