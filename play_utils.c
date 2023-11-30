/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:09:36 by jmarks            #+#    #+#             */
/*   Updated: 2023/11/24 14:09:40 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	xpm_to_image_wrapper(t_mlx *cube, t_img *img, char *filename)
{
	img->img = mlx_xpm_file_to_image(cube->mlx, filename,
			&img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp,
			&img->size_l, &img->endian);
	if (!img)
		return (0);
	return (1);
}

void	load_img(t_mlx *c)
{
	printf("NO is %s\n", c->elements.no);
	printf("SO is %s\n", c->elements.so);
	printf("EA is %s\n", c->elements.ea);
	printf("WE is %s\n", c->elements.we);
	bool	err;

	err = false;
	if (!xpm_to_image_wrapper(c, &c->img_no, c->elements.no))
		err = true;
	if (!xpm_to_image_wrapper(c, &c->img_so, c->elements.so))
		err = true;
	if (!xpm_to_image_wrapper(c, &c->img_ea, c->elements.ea))
		err = true;
	if (!xpm_to_image_wrapper(c, &c->img_we, c->elements.we))
		err = true;
	if (err)
		quit("COULDN'T LOAD IMG", c);
}

