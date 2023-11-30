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

int	quit(char *msg, t_mlx *cube)
{
	printf("Error\n%s\n", msg);
	ft_clean_arr(cube->map.map);
	// if (cube->elements.no)
	// 	free(cube->elements.no);
	// if (cube->elements.so)
	// 	free(cube->elements.so);
	// if (cube->elements.ea)
	// 	free(cube->elements.ea);
	// if (cube->elements.we)
	// 	free(cube->elements.we);
	// if (cube->win)
	// {
	// 	mlx_clear_window(cube->mlx, cube->ptr);
	// 	mlx_destroy_window(cube->mlx, cube->ptr);
	// }
	exit(EXIT_FAILURE);
	return (true);
}

int	leave(t_mlx *cube)
{
	ft_clean_arr(cube->map.map);
	// free(cube->elements.no);
	// free(cube->elements.so);
	// free(cube->elements.ea);
	// free(cube->elements.we);
	// if (cube->win)
	// {
		mlx_clear_window(cube->mlx, cube->win);
		mlx_destroy_window(cube->mlx, cube->win);
	// }
	exit(EXIT_SUCCESS);
	return (true);
}
