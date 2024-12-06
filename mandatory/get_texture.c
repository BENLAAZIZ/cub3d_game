/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:56:58 by aaaraba           #+#    #+#             */
/*   Updated: 2024/12/06 17:22:33 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	remplir_rgb(int *r, int *g, int *b, char *str)
{
	if (*r == -2)
		*r = ft_atoi(str);
	else if (*g == -2)
		*g = ft_atoi(str);
	else if (*b == -2)
		*b = ft_atoi(str);
	free(str);
}

void	*check_rgp(char *str, int r, int g, int *color)
{
	int		i;
	int		j;
	int		b;
	int		comma;

	comma = 0;
	b = -2;
	i = 0;
	j = i;
	while (str[i])
	{
		if (str[i] == ',' || str[i + 1] == '\n')
		{
			if (str[i] == ',')
				comma++;
			remplir_rgb(&r, &g, &b, ft_substr(str, j + 1, i - j));
			j = i;
		}
		i++;
	}
	if (comma != 2 || r < 0 || g < 0 || b < 0)
		return (NULL);
	*color = ft_pixel(r, g, b, 255);
	return ("ok");
}

int	check_double_texture(char	*texture, int i, int count)
{
	static int	check;
	char		*tmp;

	tmp = ft_substr(texture, 0, i);
	if (tmp == NULL)
		return (-1);
	if (ft_strcmp(tmp, "NO") == 0)
		check++;
	else if (ft_strcmp(tmp, "SO") == 0)
		check += 2;
	else if (ft_strcmp(tmp, "WE") == 0)
		check += 3;
	else if (ft_strcmp(tmp, "EA") == 0)
		check += 4;
	else if (ft_strcmp(tmp, "F") == 0)
		check += 5;
	else if (ft_strcmp(tmp, "C") == 0)
		check += 6;
	if (count == 5)
	{
		if (check != 21)
			return (free(tmp), -1);
	}
	return (free(tmp), 0);
}

void	skip_char(char *str, int *i)
{
	*i = 0;
	if (str == NULL)
		return ;
	while (str[*i] != '\0' && str[*i] != '\t'
		&& str[*i] != '\n' && str[*i] != ' ')
	{
		(*i)++;
	}
}

t_texture	*get_texture(int fd, t_texture *tex, int i, int count)
{
	char		*line;
	t_texture	*tex_tmp;

	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	while (line && count < 6)
	{
		if (line[0] != '\n')
		{
			skip_char(line, &i);
			if (check_double_texture(line, i, count) == -1)
				return (free(line), lst_clear(&tex), NULL);
			count++;
			tex_tmp = ft_lstnew(NULL, line, i);
			if (tex_tmp == NULL)
				return (lst_clear(&tex), free(line), NULL);
			lstadd_back(&tex, tex_tmp);
		}
		free(line);
		if (count == 6)
			break ;
		line = get_next_line(fd);
	}
	return (tex);
}
