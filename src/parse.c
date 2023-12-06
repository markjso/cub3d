/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:07:47 by jmarks            #+#    #+#             */
/*   Updated: 2023/11/24 14:07:52 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	validation(t_mlx *c)
// {
// 	if (!c->map.map || !*c->map.map || !c->map.map[0])
// 		quit("INVALID MAP", c);
// 	if (c->player.p_element != 1)
// 		quit("PLAYER MISSING OR TOO MANY PLAYERS", c);
// 	if (c->map.valid == false)
// 		quit("INVALID MAP - MISSING AN ELEMENT", c);
// }

int ft_max_width(int a, int b)
{
	int	z;

	z = 0;
	if (a > b)
	z = a;
	else
	z = b;
	return (z);
}

void read_map(t_map *map, int fd)
{
	int		i;
	char	*line;

	map->height = 0;
	i = 0;

	while ((line = get_next_line(fd)))
	{
		check_valid_line(line);
		line = ft_strtrim(line, "\n");
		map->map = (char **)realloc(map->map, (map->height + 1) * sizeof(char *));
		if (line[0] == ' ' || ft_isdigit(line[0]))
		{
			map->map[map->height] = ft_strdup(line);
			map->width = ft_max_width(map->width, ft_strlen(line));
			free(line);
			map->height++;
		}
	}
	close(fd);
}

t_map	map_parser(char *path)
{
	int	fd;
	t_map	map;
	if (check_file_format(path, ".cub"))
		error_mess("INCORRECT FILE FORMAT, MUST BE .CUB");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		perror("FILE: ");
	map.map = ft_calloc(1, sizeof(char *));
	read_map(&map, fd);
	close(fd);
	validate_chr(map);
	printf("able to validate_chr map\n");
	printf("map_width is %d\n", map.width);
	printf("map_height is %d\n", map.height);
	return (map);
}

void	scan_map(t_mlx *cube, char *line)
{
	if (cube->map.width < ft_strlen(line))
		cube->map.width = ft_strlen(line);
	if (ft_add_str_to_arr(line, cube))
	{
		free(line);
		quit("COULDN'T ALLOCATE MAP LINE", cube);
	}
}
