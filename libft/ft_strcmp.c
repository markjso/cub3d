/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmount <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:29:37 by rmount            #+#    #+#             */
/*   Updated: 2023/11/11 22:18:43 by rmount           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *first_str, char *second_str)
{
	int	index;

	index = 0;
	if (!first_str || !second_str)
		return (0);
	while (first_str[index] || second_str[index])
	{
		if (first_str[index] == second_str[index])
			index++;
		else
		{
			if (first_str[index] > second_str[index])
				return (1);
			else
				return (-1);
		}
	}
	return (0);
}
