/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarks <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 14:48:17 by jmarks            #+#    #+#             */
/*   Updated: 2023/11/25 14:48:21 by jmarks           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_valid_line(char *line)
{
	int i;

	i = -1;
	while(line[++i])
	{
		if(line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			break ;
		i++;	
	}
	if (i >= ft_strlen(line))
		return (1);
	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ')
			line[i] = '1';
	}
	return (0);	
}

char	*ft_free_to_trim(char *s1, const char *set)
{
	char	*tmp;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	tmp = ft_strtrim(s1, set);
	free(s1);
	return (tmp);
}

int	ft_strslen(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
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

int	dir_from_id(char *identifier)
{
	if (ft_strncmp(identifier, "NO ", 3) == 0)
		return (DIR_NORTH);
	if (ft_strncmp(identifier, "SO ", 3) == 0)
		return (DIR_SOUTH);
	if (ft_strncmp(identifier, "WE ", 3) == 0)
		return (DIR_WEST);
	if (ft_strncmp(identifier, "EA ", 3) == 0)
		return (DIR_EAST);
	return (-1);
}