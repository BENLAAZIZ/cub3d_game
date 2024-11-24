/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:05:29 by aaaraba           #+#    #+#             */
/*   Updated: 2024/11/25 00:45:02 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*char_a;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	char_a = (char *)malloc(ft_strlen(s) + 1);
	if (char_a == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		char_a[i] = f(i, s[i]);
		i++;
	}
	char_a[i] = '\0';
	return (char_a);
}
