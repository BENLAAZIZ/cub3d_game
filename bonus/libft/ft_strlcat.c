/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:40:38 by aaaraba           #+#    #+#             */
/*   Updated: 2024/11/20 12:44:29 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	s;
	size_t	d;
	size_t	ddd;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	s = ft_strlen(src);
	d = ft_strlen(dst);
	ddd = d;
	if (dstsize <= d)
		return (dstsize + s);
	while (src[i] != '\0' && d < dstsize - 1)
	{
		dst[d] = src[i];
		d++;
		i++;
	}
	dst[d] = '\0';
	return (ddd + s);
}
