/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:32:35 by aaaraba           #+#    #+#             */
/*   Updated: 2024/12/01 19:08:24 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		sizes1;
	char	*newstr;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	sizes1 = ft_strlen(s1);
	while (i < sizes1 && ft_strchr(set, s1[i]) != NULL)
		i++;
	while (i < sizes1 && ft_strrchr(set, s1[sizes1 - 1]) != NULL)
	{
		sizes1--;
	}
	newstr = (char *)malloc (sizeof(char) * ((sizes1 - i) + 1));
	if (newstr == NULL)
		return (NULL);
	j = 0;
	while (i < sizes1)
	{
		newstr[j++] = s1[i++];
	}
	newstr[j] = '\0';
	return (newstr);
}
