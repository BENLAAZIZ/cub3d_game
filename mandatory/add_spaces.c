/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:33:37 by aaaraba           #+#    #+#             */
/*   Updated: 2024/12/01 19:10:10 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	max_len(char **map, int *i)
{
	int	max;

	if (!map || !map[0])
		return (0);
	*i = 0;
	max = 0;
	while (map[*i])
	{
		if (max < (int)ft_strlen(map[*i]))
			max = ft_strlen(map[*i]);
		(*i)++;
	}
	return (max);
}

char	**add_spaces(char **map, int i, int j)
{
	int		max_length;
	char	**new_map;

	max_length = max_len(map, &i);
	new_map = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_map)
		return (NULL);
	i = -1;
	while (map[++i])
	{
		j = 0;
		new_map[i] = malloc(max_length + 1);
		if (!new_map[i])
			return (free_double(new_map), NULL);
		while (map[i][j])
		{
			new_map[i][j] = map[i][j];
			j++;
		}
		while (j < max_length)
			new_map[i][j++] = ' ';
		new_map[i][j] = '\0';
	}
	new_map[i] = NULL;
	return (free_double(map), new_map);
}
