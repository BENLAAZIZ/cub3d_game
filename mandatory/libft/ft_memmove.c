/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:31:29 by aaaraba           #+#    #+#             */
/*   Updated: 2024/12/06 17:22:11 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	d = (char *)dst;
	s = (char *)src;
	if (d == NULL && s == NULL)
		return (NULL);
	while (i < len && d < s)
	{
		d[i] = s[i];
		i++;
	}
	while (len && d > s)
	{
		d[len - 1] = s[len - 1];
		len--;
	}
	return (dst);
}
