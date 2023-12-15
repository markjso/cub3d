/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:32:53 by rmount            #+#    #+#             */
/*   Updated: 2023/12/14 10:53:37 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	fl_init_visited(bool **visited, t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			visited[i][j] = false;
			j++;
		}
		i++;
	}
}

void	floodfill(t_map map, bool **visited, int i, int j)
{
	if (i < 0 || i >= map.height || j < 0 || j >= map.width)
		return ;
	if (visited[i][j] || map.map[i][j] == '1')
		return ;
	visited[i][j] = true;
	floodfill(map, visited, i + 1, j);
	floodfill(map, visited, i - 1, j);
	floodfill(map, visited, i, j + 1);
	floodfill(map, visited, i, j - 1);
}

void	fl_find_player(t_map map, int *sr, int *sc)
{
	int	i;
	int	j;

	*sr = -1;
	*sc = -1;
	i = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			if (map.map[i][j] == 'N' || map.map[i][j] == 'S'
				|| map.map[i][j] == 'E' || map.map[i][j] == 'W')
			{
				*sr = i;
				*sc = j;
				break ;
			}
			j++;
		}
		i++;
	}
}

bool	map_can_be_exited(t_map map)
{
	bool	**visited;
	int		i;
	int		sr;
	int		sc;
	bool	can_exit;

	visited = malloc(map.height * sizeof(bool *));
	i = 0;
	while (i < map.height)
	{
		visited[i] = malloc(map.width * sizeof(bool));
		i++;
	}
	fl_init_visited(visited, map);
	fl_find_player(map, &sr, &sc);
	if (sr == -1)
		return (false);
	floodfill(map, visited, sr, sc);
	can_exit = fl_visited_boundary(visited, map);
	fl_free(visited, map);
	return (can_exit);
}
