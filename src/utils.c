/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 14:48:17 by jmarks            #+#    #+#             */
/*   Updated: 2023/12/14 16:38:06 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*str;

	if (!s1)
	{
		s1 = (char *) malloc(1);
		s1[0] = '\0';
	}
	str = ft_strjoin(s1, s2);
	free(s1);
	return (str);
}

int	dir_from_id(char *identifier)
{
	if (ft_strncmp(identifier, "NO ", 3) == 0)
		return (DIR_NORTH);
	else if (ft_strncmp(identifier, "SO ", 3) == 0)
		return (DIR_SOUTH);
	else if (ft_strncmp(identifier, "WE ", 3) == 0)
		return (DIR_WEST);
	else if (ft_strncmp(identifier, "EA ", 3) == 0)
		return (DIR_EAST);
	else
		return (-1);
}

double	ft_abs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}
