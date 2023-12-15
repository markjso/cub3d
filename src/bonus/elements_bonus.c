/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:05:55 by jmarks            #+#    #+#             */
/*   Updated: 2023/12/14 16:40:32 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

static void	init_elements(t_elements *elements)
{
	elements->wall_tex = malloc(sizeof(t_mlx) * 5);
	if (!elements->wall_tex)
		error_mess("malloc error");
	elements->ceiling = -1;
	elements->floor = -1;
	elements->wall_tex[DIR_NORTH].img = NULL;
	elements->wall_tex[DIR_SOUTH].img = NULL;
	elements->wall_tex[DIR_WEST].img = NULL;
	elements->wall_tex[DIR_EAST].img = NULL;
}

static void	check_elements(t_elements elements)
{
	if (elements.ceiling == -1 || elements.floor == -1)
		error_mess("missing colour");
	if (elements.wall_tex[DIR_NORTH].img == NULL)
		error_mess("missing north texture");
	if (elements.wall_tex[DIR_SOUTH].img == NULL)
		error_mess("missing south texture");
	if (elements.wall_tex[DIR_WEST].img == NULL)
		error_mess("missing west texture");
	if (elements.wall_tex[DIR_EAST].img == NULL)
		error_mess("missing east texture");
}

void	set_textures(t_mlx *cube, t_elements elements, char *line, int dir)
{
	void	*image;
	int		height;
	int		width;

	height = TEX_HEIGHT;
	width = TEX_WIDTH;
	if (elements.wall_tex[dir].img != NULL)
		error_mess("texture already set");
	line += 2;
	line = ft_strtrim(line, " \t\n");
	if (check_file_format(line, ".xpm"))
		error_mess("Incorrect texture file format, must be .xpm");
	image = mlx_xpm_file_to_image(cube->mlx, line, &width, &height);
	free(line);
	if (!image)
		error_mess("texture not found");
	elements.wall_tex[dir].img = image;
	elements.wall_tex[dir].addr = mlx_get_data_addr(image, \
			&elements.wall_tex[dir].bits_per_pixel, \
			&elements.wall_tex[dir].line_length, \
			&elements.wall_tex[dir].endian);
}

void	set_colour(t_elements *elements, char *line)
{
	int	*rgb;

	if (line[0] == 'C')
	{
		rgb = save_rgb("C", line);
		elements->ceiling = create_rgb(rgb[0], rgb[1], rgb[2]);
		free(rgb);
	}
	else if (line[0] == 'F')
	{
		rgb = save_rgb("F", line);
		elements->floor = create_rgb(rgb[0], rgb[1], rgb[2]);
		free(rgb);
	}
}

t_elements	parse_elements(t_mlx *cube, char *path)
{
	int			fd;
	char		*line;
	char		*tmp;
	t_elements	elements;

	init_elements(&elements);
	fd = do_file(path);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_strtrim(line, " \t");
		if (is_dir_char(tmp[0]))
			set_textures(cube, elements, tmp, dir_from_id(tmp));
		if (tmp[0] == 'C' || tmp[0] == 'F')
			set_colour(&elements, tmp);
		free(tmp);
		free(line);
	}
	close(fd);
	check_elements(elements);
	return (elements);
}
