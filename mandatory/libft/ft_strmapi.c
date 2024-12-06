/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:32:18 by aaaraba           #+#    #+#             */
/*   Updated: 2024/12/06 17:22:11 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
