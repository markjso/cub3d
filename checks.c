/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:06:09 by jmarks            #+#    #+#             */
/*   Updated: 2023/11/24 14:06:11 by jmarks           ###   ########.fr       */
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

void	set_player(int i, int j, t_mlx *cube)
{
	if (cube->player.p_element != 1)
		quit("NO PLAYER OR TOO MANY PLAYERS DETECTED\n", cube);
	cube->player.pos_x = (double)j;
	cube->player.pos_y = (double)i;
}

static bool	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
		printf("true\n");
	return (false);
	printf("false\n");
}

bool	validate_chr(t_map map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map.height)
	{
		j = -1;
		while (++j < ft_strlen(map.map[i]))
		{
			if (!is_valid_map_char(map.map[i][j]))
			{
				error_mess("INVALID CHARACTER IN MAP FILE");
				return (false);
			}
		}
	}
	return (true);
}

void	validate_map(t_mlx *cube)
{
	int	i;
	int	j;

	cube->player.p_element = 0;
	i = -1;
	while (cube->map.map[++i])
	{
		j = -1;
		while (cube->map.map[i][++j])
		{
			if (ft_strchr("0NSEW", cube->map.map[i][j]))
			{
				if (!check_h(cube, i, j))
					quit("MAP IS NOT ENCLOSED BY WALLS", cube);
				if (!check_v(cube, i, j))
					quit("MAP IS NOT ENCLOSED BY WALLS", cube);
			}
			if (ft_strchr("NSEW", cube->map.map[i][j]))
			{
				cube->player.p_element += 1;
				set_player(i, j, cube);
			}
		}
	}
}

bool	check_h(t_mlx *cube, int i, int j)
{
	bool	left;
	bool	right;
	int		k;

	left = false;
	right = false;
	k = j;
	while (right == false && cube->map.map[i][--k])
	{
		if (ft_strchr(".", cube->map.map[i][k]))
			quit("MAP IS NOT ENCLOSED BY WALLS", cube);
		if (ft_strchr("1", cube->map.map[i][k]))
			right = true;
	}
	k = j;
	while (left == false && cube->map.map[i][++k])
	{
		if (ft_strchr(".", cube->map.map[i][k]))
			quit("MAP IS NOT ENCLOSED BY WALLS", cube);
		if (ft_strchr("1", cube->map.map[i][k]))
			left = true;
	}
	return (right && left);
}

bool	check_v(t_mlx *cube, int i, int j)
{
	bool	up;
	bool	down;
	size_t	k;

	up = false;
	down = false;
	k = i;
	while (up == false && cube->map.map[--k])
	{
		if (ft_strchr(".", cube->map.map[k][j]))
			quit("MAP IS NOT ENCLOSED BY WALLS", cube);
		if (ft_strchr("1", cube->map.map[k][j]))
			up = true;
	}
	k = i;
	while (down == false && cube->map.map[++k])
	{
		if (ft_strchr(".", cube->map.map[k][j]))
			quit("MAP IS NOT ENCLOSED BY WALLS", cube);
		if (ft_strchr("1", cube->map.map[k][j]))
			down = true;
	}
	return (up && down);
}
