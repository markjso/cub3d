/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:05:55 by jmarks            #+#    #+#             */
/*   Updated: 2023/11/24 14:05:57 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		error_mess("missing color");
	if (elements.wall_tex[DIR_NORTH].img == NULL)
		error_mess("missing north texture");
	if (elements.wall_tex[DIR_SOUTH].img == NULL)
		error_mess("missing south texture");
	if (elements.wall_tex[DIR_WEST].img == NULL)
		error_mess("missing west texture");
	if (elements.wall_tex[DIR_EAST].img == NULL)
		error_mess("missing east texture");
}

static void	set_textures(t_mlx *cube, t_elements elements, char *line, int dir)
{
	void	*image;
	int		height;
	int		width;

	height = TEX_HEIGHT;
	width = TEX_WIDTH;
	if (dir == -1)
		error_mess("invalid texture identifier");
	if (elements.wall_tex[dir].img != NULL)
		error_mess("texture already set");
	line += 2;
	line = ft_strtrim(line, " \t\n");
	// if (ft_strncmp(ft_get_file_extension(line), ".xpm", ft_strlen(line)))
	// 	error_mess("invalid texture extension");
	image = mlx_xpm_file_to_image(cube->mlx, line, &width, &height);
	printf("image is %p\n", image);
	free(line);
	if (!image)
		error_mess("texture not found");
	elements.wall_tex[dir].img = image;
	elements.wall_tex[dir].addr = mlx_get_data_addr(image, \
			&elements.wall_tex[dir].bits_per_pixel, \
			&elements.wall_tex[dir].line_length, \
			&elements.wall_tex[dir].endian);
	if (!elements.wall_tex[dir].addr)
		error_mess("mlx_get_data_addr failed");
}

static void	set_color(t_elements *elements, char *line)
{
	int	*rgb;
	if (line[0] == 'C')
	{
		rgb = save_rgb("C", line);
		elements->ceiling = create_rgb(rgb[0], rgb[1], rgb[2]);
		free(rgb);
	}
	if (line[0] == 'F')
	{
		rgb = save_rgb("F", line);
		elements->floor = create_rgb(rgb[0], rgb[1], rgb[2]);
		free(rgb);
	}
}

// char *save_path(char *identifier)
// {
// 	printf("identifier is %s\n", identifier);
// 	char	*tmp;
// 	char	*direction;

// 	direction = identifier + 3;
// 	tmp = strdup(direction);
// 	printf("tmp is %s\n", tmp);
// 	if (!tmp)
// 		perror("TMP");

// 	return (tmp);
// }

t_elements	parse_elements(t_mlx *cube, char *path)
{
	int			fd;
	char		*line;
	t_elements	elements;

	init_elements(&elements);
	printf("elements initialised\n");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		perror("file: ");
	while ((line = get_next_line(fd)))
	{
		line = ft_strtrim(line, "\n\t");
		if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
			set_textures(cube, elements, line, dir_from_id(line));
		if (line[0] == 'C' || line[0] == 'F')
		{
			set_color(&elements, line);
			printf("colour assigned\n");
		}
		free(line);
	}
	close(fd);
	check_elements(elements);
	return (elements);
}