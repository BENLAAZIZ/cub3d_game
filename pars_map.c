#include "cub3d.h"

int check_char(char c)
{
	if (c == '1'
		|| c == '0'
		|| c == 'N'
		||  c == 'S'
		|| c == 'W'
		|| c == 'E')
		return (1);
	return (0);
}

int check_characters(char **map, int i, int j)
{
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N'
				|| map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				if (check_char(map[i - 1][j]) == 0)
					return (ft_putstr_fd("Error: Invalid character", 2), 1);
				if (check_char(map[i + 1][j]) == 0)
					return (ft_putstr_fd("Error: Invalid character", 2), 1);
				if (check_char(map[i][j - 1]) == 0)
					return (ft_putstr_fd("Error: Invalid character", 2), 1);
				if (check_char(map[i][j + 1]) == 0)
					return (ft_putstr_fd("Error: Invalid character", 2), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char **pars_map(char *argv, t_texture **textures, char **map)
{
	int		fd;
	char 	**new_map;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error opening file", 2), NULL);
	*textures = get_texture(fd, *textures, 0, 0);
	if (*textures == NULL)
		return (ft_putstr_fd("Error getting textures", 2), NULL);
	map = get_map(fd);
	if (map == NULL)
		return (ft_putstr_fd("Error getting map", 2), NULL);
	new_map = add_spaces(map);
	if(new_map == NULL)
		return (ft_putstr_fd("Error adding spaces", 2), NULL);
	check_characters(new_map, 0, 0);
	// int i = 0;
	// while(new_map[i])
	// {
	// 	// ft_putstr_fd(new_map[i], 1);
	// 	// ft_putstr_fd("|\n", 1);
	// 	i++;
	// }
	close(fd);
	return (map);
}