/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:31:13 by aaaraba           #+#    #+#             */
/*   Updated: 2024/12/01 15:31:14 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static int	ft_nlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = -n;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	ft_return(int n)
{
	int	size;

	if (n == 0)
		size = 1;
	if (n < 0)
		size = ft_nlen(n) + 1;
	else if (n > 0)
		size = ft_nlen(n);
	return (size);
}

char	*ft_itoa(int n)
{
	char	*c;
	size_t	size;
	long	l;

	l = 0;
	size = ft_return(n);
	c = (char *)malloc(sizeof(char) * (size + 1));
	if (c == NULL)
		return (NULL);
	c[size] = '\0';
	if (n == 0)
		c[0] = 0 + '0';
	else if (n < 0)
	{
		c[0] = '-';
		l = (long)n * -1;
	}
	else
		l = (long)n;
	while (l > 0)
	{
		c[--size] = l % 10 + '0';
		l = l / 10;
	}
	return (c);
}
