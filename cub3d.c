/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:14:46 by jmarks            #+#    #+#             */
/*   Updated: 2023/11/30 13:15:35 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_mlx	*cube;

	if (argc != 2)
		error_mess("INVALID NUMBER OF ARGUMENTS");
	cube = init_mlx(argv[1]);
	printf("cube initalised\n");
	// init_map(cube);
	// init_raycast(cube);
	// ft_img_renderer(cube);
	mlx_hook(cube->win, 2, 1L << 0, keypress, cube);
	mlx_hook(cube->win, 17, 0, leave, cube);
	mlx_loop(cube->mlx);
	return (0);
}
