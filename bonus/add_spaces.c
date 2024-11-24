#include "cub3d_bonus.h"

int max_len(char **map, int *i)
{
	int max;

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

char	**add_spaces(char **map)
{
	int	max_length;
	int	i;
	char	**new_map;
	int j;

	j = 0;
	max_length = max_len(map, &i);
	if (max_length == 0)
		return (NULL);
	new_map = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		j = 0;
		new_map[i] = malloc(max_length + 1);
		if (!new_map[i])
		{
			free_double(new_map);
			return (NULL);
		}
		while (map[i][j])
		{
			new_map[i][j] = map[i][j]; 
			j++;
		}
		while (j < max_length)
		{
			new_map[i][j] = ' ';
			j++;
		}
		new_map[i][j] = '\0';
		i++;
	}
	new_map[i] = NULL;
	free_double(map);
	return (new_map);
}
