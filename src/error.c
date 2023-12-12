/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <rmount@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:07:34 by jmarks            #+#    #+#             */
/*   Updated: 2023/12/11 13:09:42 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	error_mess(char *msg)
{
	printf("Error\n%s\n", msg);
	exit(EXIT_FAILURE);
}

void	ft_free_map(t_mlx *cube)
{
	int	i;

	i = -1;
	while (++i < cube->map.height)
		free(cube->map.map[i]);
	free(cube->map.map);
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

void	free_textures(t_mlx *cube)
{
	if (!cube->elements.wall_tex)
		return ;
	if (cube->elements.wall_tex[DIR_NORTH].img)
		mlx_destroy_image(cube->mlx,
			cube->elements.wall_tex[DIR_NORTH].img);
	if (cube->elements.wall_tex[DIR_SOUTH].img)
		mlx_destroy_image(cube->mlx,
			cube->elements.wall_tex[DIR_SOUTH].img);
	if (cube->elements.wall_tex[DIR_EAST].img)
		mlx_destroy_image(cube->mlx,
			cube->elements.wall_tex[DIR_EAST].img);
	if (cube->elements.wall_tex[DIR_WEST].img)
		mlx_destroy_image(cube->mlx,
			cube->elements.wall_tex[DIR_WEST].img);
	free(cube->elements.wall_tex);
}

int	quit(char *msg, t_mlx *cube)
{
	printf("Error\n%s\n", msg);
	// ft_clean_arr(cube->map.map);
	free_textures(cube);
	if (cube->win)
	{
		mlx_clear_window(cube->mlx, cube->win);
		mlx_destroy_window(cube->mlx, cube->win);
	}
	exit(EXIT_FAILURE);
}

int	leave(t_mlx *cube)
{
	if (cube->win)
	{
		mlx_clear_window(cube->mlx, cube->win);
		mlx_destroy_window(cube->mlx, cube->win);
	}
	ft_free_map(cube);
	free_textures(cube);
	exit(EXIT_SUCCESS);
}
