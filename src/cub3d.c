/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <rmount@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:14:46 by jmarks            #+#    #+#             */
/*   Updated: 2023/12/11 13:11:49 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_mlx	*cube;

	if (argc != 2)
		error_mess("Invalid number of arguments, must be two");
	cube = init_mlx(argv[1]);
	cube->player = init_player(cube->map);
	cube->raycast = init_raycast();
	img_renderer(cube);
	mlx_hook(cube->win, 2, 1L << 0, keypress, cube);
	mlx_hook(cube->win, 17, 0, leave, cube);
	mlx_loop(cube->mlx);
	return (0);
}
