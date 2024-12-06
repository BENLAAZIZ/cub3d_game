/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:30:48 by aaaraba           #+#    #+#             */
/*   Updated: 2024/12/06 17:22:11 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	skip_spaces(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

int	ft_atoi(char *str)
{
	int				i;
	int				s;
	unsigned long	r;

	if (!str)
		return (-1);
	i = 0;
	s = 0;
	r = 0;
	skip_spaces(str, &i);
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + str[i] - '0';
		i++;
		if (r > 255)
			return (-1);
	}
	skip_spaces(str, &i);
	if (str[i] != '\0' && str[i] != '\n' && str[i] != ',')
		return (-1);
	return (r);
}
