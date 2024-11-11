#include "cub3d.h"

int	check_double_texture(char	*texture)
{
	static int	check;
	static int	count;

	if (ft_strncmp(texture , "NO", 2) == 0)
		check++;
	else if (ft_strncmp(texture , "SO", 2) == 0)
		check+=2;
	else if (ft_strncmp(texture , "WE", 2) == 0)
		check+=3;
	else if (ft_strncmp(texture , "EA", 2) == 0)
		check+=4;
	else if (ft_strncmp(texture , "F", 1) == 0)
		check+=5;
	else if (ft_strncmp(texture , "C", 1) == 0)
		check+=6;
	count++;
	if (count == 6)
	{
		if (check != 21)
			return (-1);
	}
	return (0); 
}

t_texture	*get_texture(int fd, t_texture *tex)
{
	int		count;
	char	*tmp;
	char	*line;
	int		i = 0;
	int		j = 0;
	t_texture *tex_tmp = NULL;

	count = 0;
	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	while (line && count < 6)
	{	
		tmp = line;
		i = 0;
		if (line[0] != '\n')
		{
			while (line[i] != '\0' && line[i] != '\n' && line[i] != ' ' && line[i] != '\t')
				i++;
			j = 0;
			if (check_double_texture(line) == -1)
				return (write(2, "wrong texture\n", 14), NULL);
			count++;
			tex_tmp = ft_lstnew(tex_tmp, line, i);
			lstadd_back(&tex, tex_tmp);
			free(tmp);
		}
		line = get_next_line(fd);
	}
	return(tex);
}

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
			return (write (1, "Error\nInvalid map\n", 18), 1);
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

	rest = NULL;
	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	while (line)
	{	
		tmp = line;
		rest = ft_strjoin(rest, line);
		if (rest == NULL)
			free(tmp);
		free(tmp);
		line = get_next_line(fd);
	}
	if (ft_check(rest) == 1)
		return (NULL);
	map = ft_split(rest,'\n');
	free(rest);
	if (map == NULL)
		return (NULL);
	return(map);
}

int	ft_strlen_nspance(char	*str)
{
	int	i = 0;
	while(str[i])
		i++;
	return (i);
}

int check_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' ||  c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}



int main (int argc, char **argv)
{
	if (argc != 2)
		return (1);
	t_texture *tex = NULL;
	
	char	**map;
	int		fd;
	int		length;
	int		max_length;
	int		height;

	if (ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub") != 0)
		return (1);
	fd = open(argv[1], O_RDONLY);
	tex = get_texture(fd, tex);
	if (tex == NULL)
		return (1);
	int i = 0;
	map = get_map(fd);
	close(fd);
	if (map == NULL)
		return (1);
	length = ft_strlen_nspance(map[0]);
	i = 0;
	while (map[i])
	{
		if (max_length < (int)ft_strlen(map[i]))
			max_length = ft_strlen(map[i]);
		i++;
	}
	char	**new_map = (char **)malloc(sizeof(char *) * (i + 1));
	height = i;
	int j = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		new_map[i] = malloc(max_length + 1);
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
	i = 0;
	j = 0;
	while (new_map[i])
	{
		j = 0;
		while (new_map[i][j])
		{
			if (new_map[i][j] == '0' || new_map[i][j] == 'N' || new_map[i][j] == 'S' || new_map[i][j] == 'E'
				|| new_map[i][j] == 'W')
			{
				if (check_char(new_map[i - 1][j]) == 0)
					return (write(2, "er\n", 3), 1);
				if (check_char(new_map[i + 1][j]) == 0)
					return (write(2, "er\n", 3),1);
				if (check_char(new_map[i][j + 1]) == 0)
					return (write(2, "er\n", 3),1);
				if (check_char(new_map[i][j - 1]) == 0)
					return (write(2, "er\n", 3),1);
			}
			j++;
		}
		i++;
	}
		
		


		
	create_window(new_map);
}
