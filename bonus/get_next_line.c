/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:34:09 by aaaraba           #+#    #+#             */
/*   Updated: 2024/12/01 15:34:10 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*ft_cheaknewline(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return ("yes");
		i++;
	}
	return (NULL);
}

char	*readfromfile(int fd, char *buffer, char *new)
{
	char	*freenew;
	int		c;

	c = 1;
	while (c > 0)
	{
		c = read(fd, buffer, BUFFER_SIZE);
		if (c <= 0)
			break ;
		buffer[c] = '\0';
		freenew = new;
		new = ft_strjoin(new, buffer);
		if (new == NULL)
			return (free (freenew), free(buffer), NULL);
		free(freenew);
		if (ft_cheaknewline(buffer) != NULL)
			break ;
	}
	free(buffer);
	return (new);
}

char	*copy_in_newstr(char *new, char *str, int *x)
{
	int	i;

	i = 0;
	while (new[i] != '\n' && new[i])
		i++;
	if (new[i] == '\n')
		i++;
	str = ft_substr(new, 0, i);
	if (str == NULL)
		return (NULL);
	*x = i;
	return (str);
}

char	*check_free_new(char *new)
{
	if (new[0] == '\0')
	{
		free(new);
		return (NULL);
	}
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*new ;
	char		*str;
	char		*buffer;
	char		*temp;
	int			x;

	if (BUFFER_SIZE < 1 || read(fd, "", 0) < 0)
		return (free(new), new = NULL, NULL);
	buffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (buffer == NULL)
		return (free(new), new = NULL, NULL);
	new = readfromfile(fd, buffer, new);
	if (new == NULL)
		return (NULL);
	x = 0;
	str = copy_in_newstr(new, NULL, &x);
	if (str == NULL)
		return (free(new), new = NULL, NULL);
	temp = new;
	new = ft_strdup(new + x);
	if (new == NULL)
		return (free(str), free(temp), NULL);
	free(temp);
	new = check_free_new(new);
	return (str);
}
