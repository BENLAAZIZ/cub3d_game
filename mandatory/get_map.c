#include "cub3d.h"

int	ft_check(char *map)
{
	int	i;
	int player;

	player = 0;
	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] != 'N' && map[i] != 'S' && map[i] != 'E'
			&& map[i] != '\n' && map[i] != 'W' && map[i] != '1' && map[i] != '0' && map[i] != ' ')
			return (write (2, "Invalid map\n", 12), 1);
		if (map[i] == 'S' || map[i] == 'N' || map[i] == 'W' || map[i] == 'E')
			player++;
		i++;
	}
	if (player != 1)
		return (write (1, "Invalid num of player\n", 22), 1);
	return (0);
}

char	**get_map(int fd)
{
	char	**map;
	char 	*rest;
	char	*tmp;
	char	*line;
	char	*tmp_2;

	rest = NULL;
	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	while (line)
	{	
		tmp = line;
		tmp_2 = rest;
		rest = ft_strjoin(rest, line);
		if (rest == NULL)
			return (free(tmp), NULL);
		free(tmp_2);
		free(tmp);
		line = get_next_line(fd);
	}
	// while(1);
	if (ft_check(rest) == 1)
	{
		free(rest);
		return (NULL);
	}
	map = ft_split(rest,'\n');
	if (map == NULL)
		return (free(rest), NULL);
	free(rest);
	return(map);
}
