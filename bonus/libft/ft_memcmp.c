/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:31:23 by aaaraba           #+#    #+#             */
/*   Updated: 2024/12/01 15:31:24 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*p1;
	char	*p2;
	size_t	i;

	i = 0;
	p1 = (char *)s1;
	p2 = (char *)s2;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return ((unsigned char)p1[i] - (unsigned char)p2[i]);
		i++;
	}
	return (0);
}
