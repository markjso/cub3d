/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:09:56 by jmarks            #+#    #+#             */
/*   Updated: 2023/11/24 14:09:59 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_i(t_mlx *cube)
{
	int	i;

	i = 0;
	if (!cube->map.map)
		return (i);
	else
		while (cube->map.map[++i])
			;
	return (i);
}

int	ft_add_str_to_arr(char *str, t_mlx *cube)
{
	int		i;
	int		j;
	char	**new_arr;
	char	*n_str;

	i = -1;
	j = -1;
	n_str = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (!n_str)
		return (1);
	ft_strcpy(n_str, str);
	i = set_i(cube);
	new_arr = ft_calloc((i + 2), sizeof(char *));
	if (!new_arr)
		return (1);
	while (++j < i)
		new_arr[j] = ft_strdup(cube->map.map[j]);
	new_arr[i] = n_str;
	new_arr[i + 1] = NULL;
	if (cube->map.map)
		ft_clean_arr(cube->map.map);
	cube->map.map = new_arr;
	return (0);
}
