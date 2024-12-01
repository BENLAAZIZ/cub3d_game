/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:30:55 by aaaraba           #+#    #+#             */
/*   Updated: 2024/12/01 15:30:56 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	of;

	of = count * size;
	if (count != 0 && of / count != size)
		return (NULL);
	p = malloc (count * size);
	if (p == 0)
		return (NULL);
	ft_bzero(p, (count * size));
	return (p);
}
