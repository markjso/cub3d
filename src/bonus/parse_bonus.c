/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:07:47 by jmarks            #+#    #+#             */
/*   Updated: 2023/12/14 16:36:10 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

t_map	init_map(void)
{
	t_map	map;

	map.map = ft_calloc(1, sizeof(char *));
	map.height = 0;
	map.width = 0;
	map.p_element = 0;
	if (!map.map)
		error_mess("malloc failed");
	return (map);
}

void	read_map(t_map *map, int fd)
{
	char		*line;
	char		*tmp;
	int			map_started;

	map_started = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_strtrim(line, " \t\n");
		if (tmp[0] == '1' || tmp[0] == '0')
			map_started = 1;
		if (map_started && (tmp[0] != '1' && tmp[0] != '0'))
			error_mess("Map content must be at the end of the file");
		check_valid_line(tmp, line);
		if (map_started)
		{
			map->map = ft_strsjoin(map->map, ft_strdup(tmp));
			if (ft_strlen(tmp) > map->width)
				map->width = ft_strlen(tmp);
			map->height++;
		}
		free(tmp);
	}
}

void	ft_normalise_width(t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.height)
	{
		j = ft_strlen(map.map[i]);
		while (j < map.width)
		{
			map.map[i] = ft_strjoin_and_free(map.map[i], "1");
			j++;
		}
		i++;
	}
}

t_map	map_parser(char *path)
{
	int			fd;
	t_map		map;

	if (check_file_format(path, ".cub"))
		error_mess("Incorrect file format, must be .cub");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_mess("No such file or directory");
	map = init_map();
	read_map(&map, fd);
	close(fd);
	ft_map_valid(map);
	ft_normalise_width(map);
	find_player(&map);
	return (map);
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
