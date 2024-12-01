

#include "cub3d.h"

void	free_double(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	lst_clear(t_texture **lst)
{
	t_texture	*tmp;
	t_texture	*tmp2;

	tmp = *lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp->path);
		free(tmp);
		tmp = tmp2;
	}
	*lst = NULL;
}

int	check_char(char c)
{
	if (c == '1'
		|| c == '0'
		|| c == 'N'
		|| c == 'S'
		|| c == 'W'
		|| c == 'E')
		return (1);
	return (0);
}

int	check_characters(char **map, int i, int j)
{
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N'
				|| map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (i == 0 || map[i + 1] == NULL
					|| j == 0 || j == (int)ft_strlen(map[i]) - 1)
					return (ft_putstr_fd("Error: Invalid map", 2), 1);
				if (i > 0 && check_char(map[i - 1][j]) == 0)
					return (ft_putstr_fd("Error: Invalid character", 2), 1);
				if (map[i + 1] && check_char(map[i + 1][j]) == 0)
					return (ft_putstr_fd("Error: Invalid character", 2), 1);
				if (j > 0 && check_char(map[i][j - 1]) == 0)
					return (ft_putstr_fd("Error: Invalid character", 2), 1);
				if (map[i][j + 1] && check_char(map[i][j + 1]) == 0)
					return (ft_putstr_fd("Error: Invalid character", 2), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	**pars_map(char *argv, t_texture **textures, char **map)
{
	int		fd;
	char	**new_map;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error opening file", 2), NULL);
	*textures = get_texture(fd, *textures, 0, 0);
	if (*textures == NULL)
		return (close(fd), ft_putstr_fd("Error getting ytextures", 2), NULL);
	map = get_map(fd, NULL, NULL, NULL);
	if (map == NULL)
		return (close(fd), lst_clear(textures), ft_putstr_fd("Error", 2), NULL);
	close(fd);
	new_map = add_spaces(map, 0, 0);
	if (new_map == NULL)
	{
		lst_clear(textures);
		return (ft_putstr_fd("Error adding spaces", 2), NULL);
	}
	if (check_characters(new_map, 0, 0) == 1)
		return (free_double(new_map), lst_clear(textures), NULL);
	return (new_map);
}
