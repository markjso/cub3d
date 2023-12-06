/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:07:34 by jmarks            #+#    #+#             */
/*   Updated: 2023/11/24 14:07:37 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	error_mess(char *msg)
{
	printf("Error\n%s\n", msg);
	exit(EXIT_FAILURE);
}

void	ft_clean_arr(char **arr)
{
	size_t	i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i])
			free(arr[i++]);
	}
	free(arr);
	arr = NULL;
}

int	quit(char *msg, t_mlx *cube)
{
	printf("Error\n%s\n", msg);
	ft_clean_arr(cube->map.map);
	if (cube->win)
	{
		mlx_clear_window(cube->mlx, cube->win);
		mlx_destroy_window(cube->mlx, cube->win);
	}
	exit(EXIT_FAILURE);
}

int	leave(t_mlx *cube)
{
	ft_clean_arr(cube->map.map);
	if (cube->win)
	{
		mlx_clear_window(cube->mlx, cube->win);
		mlx_destroy_window(cube->mlx, cube->win);
	}
	exit(EXIT_SUCCESS);
}
