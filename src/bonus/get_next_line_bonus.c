/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <rmount@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:41:39 by jmarks            #+#    #+#             */
/*   Updated: 2023/12/11 13:55:36 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int	is_dir_char(char letter)
{
	if (letter == 'N' || letter == 'E' || letter == 'S' || letter == 'W')
	{
		return (1);
	}
	return (0);
}

void	*ft_calloc(size_t nmeb, size_t size)
{
	char	*buf;
	size_t	i;

	i = 0;
	buf = (char *) malloc(nmeb * size);
	if (!buf)
		return (NULL);
	while (i < (nmeb * size))
		buf[i++] = '\0';
	return ((void *) buf);
}

static char	*ft_get_line_from_file(int fd, char *buffer, char *saved)
{
	int		read_size;
	char	*temp;

	read_size = 1;
	while (read_size != '\0')
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size == -1)
			return (0);
		else if (read_size == 0)
			break ;
		buffer[read_size] = '\0';
		if (!saved)
			saved = ft_strdup("");
		temp = saved;
		saved = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (saved);
}

static char	*ft_get_new_line(char *line)
{
	size_t	i;
	char	*remainder;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (NULL);
	remainder = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*remainder == '\0')
	{
		free(remainder);
		remainder = NULL;
	}
	line[i + 1] = '\0';
	return (remainder);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*saved;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *) ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	line = ft_get_line_from_file(fd, buffer, saved);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	saved = ft_get_new_line(line);
	return (line);
}
