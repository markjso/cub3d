/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <rmount@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:07:47 by jmarks            #+#    #+#             */
/*   Updated: 2023/12/11 14:41:03 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_max_width(int a, int b)
{
	int	z;

	z = 0;
	if (a > b)
		z = a;
	else
		z = b;
	return (z);
}

void	read_map(t_map *map, int fd)
{
	int		i;
	char	*line;
	char	**tmp;

	line = get_next_line(fd);
	while (line)
	{
		check_valid_line(line);
		line = ft_strtrim(line, "\n");
		tmp = (char **)ft_calloc(map->height + 1, sizeof(char *));
		i = -1;
		while (++i < map->height)
			tmp[i] = map->map[i];
		free(map->map);
		map->map = tmp;
		if (line[0] == ' ' || ft_isdigit(line[0]))
		{
			map->map[map->height] = ft_strdup(line);
			map->width = ft_max_width(map->width, ft_strlen(line));
			free(line);
			map->height++;
		}
		line = get_next_line(fd);
	}
	close(fd);
}

t_map	map_parser(char *path)
{
	int		fd;
	t_map	map;

	init_map(&map);
	if (check_file_format(path, ".cub"))
		error_mess("Incorrect file format, must be .cub");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		perror("FILE: ");
	map.map = (char **)ft_calloc(1, sizeof(char *));
	map.height = 0;
	read_map(&map, fd);
	close(fd);
	ft_map_valid(map);
	find_player(&map);
	return (map);
}

void	scan_map(t_mlx *cube, char *line)
{
	if (cube->map.width < (int)ft_strlen(line))
		cube->map.width = (int)ft_strlen(line);
	if (ft_add_str_to_arr(line, cube))
	{
		free(line);
		quit("COULDN'T ALLOCATE MAP LINE", cube);
	}
}

bool	ft_map_valid(t_map map)
{
	if (!validate_chr(map))
		return (false);
	if (map_can_be_exited(map))
	{
		error_mess("Map is not closed in by walls.");
		return (false);
	}
	return (true);
}
