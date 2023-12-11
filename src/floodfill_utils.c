/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <rmount@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:44:02 by rmount            #+#    #+#             */
/*   Updated: 2023/12/11 13:54:52 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	fl_visited_boundary(bool **visited, t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.height)
	{
		if (visited[i][0] || visited[i][map.width - 1])
			return (true);
		i++;
	}
	j = 0;
	while (j < map.width)
	{
		if (visited[0][j] || visited[map.height - 1][j])
			return (true);
		j++;
	}
	return (false);
}

void	fl_free(bool **visited, t_map map)
{
	int	i;

	i = 0;
	while (i < map.height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

int	do_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror ("file: ");
	}
	return (fd);
}
