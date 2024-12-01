/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:32:05 by aaaraba           #+#    #+#             */
/*   Updated: 2024/12/01 19:08:24 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	copystring(char *newstr, const char *s2, int totalsize, int i)
{
	int	x;

	x = 0;
	while (i < totalsize)
	{
		newstr[i++] = s2[x++];
	}
	newstr[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	totalsize;
	size_t	i;

	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	totalsize = ft_strlen(s1) + ft_strlen(s2);
	newstr = (char *)malloc((sizeof(char) * totalsize + 1));
	if (newstr == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		newstr[i] = s1[i];
		i++;
	}
	copystring(newstr, s2, totalsize, i);
	return (newstr);
}
