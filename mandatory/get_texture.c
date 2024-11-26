#include "cub3d.h"

void	*check_rgp(char *str, int r, int g, int *color)
{
	int	i;
	int	j;
	int b;
	int	res;
	int comma = 0;
	char *color_str;

	b = -1;
	i = 0;
	res = 0;
	while (str[i] == ' ' && str[i] == '\t')
		i++;
	j = i;
	while (str[i])
	{
		if (str[i] == ',' || str[i + 1] == '\n')
		{
			if (str[i] == ',')
				comma++;
			color_str = ft_substr(str, j + 1, i - j);
			res = ft_atoi(color_str);
			if (res < 0 || res > 255)
				return (free(color_str), NULL);
			if (r == -1)
				r = res;
			else if (g == -1)
				g = res;
			else if (b == -1)
				b = res;
			j = i;
			free(color_str);
		}
		i++;
	}
	if (comma != 2)
		return (NULL);
	*color = ft_pixel(r, g, b, 255);
	return ("ok");
}

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

t_texture	*get_texture(int fd, t_texture *tex, int j, int i)
{
	int		count;
	char	*tmp;
	char	*line;
	t_texture *tex_tmp;

	tex_tmp = NULL;
	count = 0;
	line = get_next_line(fd);
	printf("line = %p\n", line);
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
			{
				free(tmp);
				lst_clear(&tex);
				return (write(2, "wrong texture\n", 14), NULL);
			}
			count++;
			tex_tmp = ft_lstnew(tex_tmp, line, i);
			if (tex_tmp == NULL) 
			{ 
				lst_clear(&tex);
				free(tmp);
				return (NULL);
			}
			lstadd_back(&tex, tex_tmp);
		}
		free(tmp), tmp = NULL;
		if (count == 6)
			break;
		line = get_next_line(fd);
		printf("line = %p\n", line);
	}
		printf("line = [%s]\n", line);
	return(tex);
}
