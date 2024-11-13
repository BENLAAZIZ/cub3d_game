/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:27:39 by aaaraba           #+#    #+#             */
/*   Updated: 2024/10/09 11:33:36 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
#include <string.h>
#include <stdio.h>

char	*ft_strdup(const char *s1)
{
	int	i;
	char	*copy;
	int	j;

	i = strlen(s1);
	copy = (char *)malloc(i + 1);
	if (copy == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		copy[j] = s1[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*src;
	int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start >= strlen(s))
		return (ft_strdup(""));
	if (start + len > strlen(s))
		len = strlen(s) - start;
	src = (char *)malloc(len + 1);
	if (src == NULL)
		return (NULL);
	while (i < len)
	{
		src[i] = s[start + i];
		i++;
	}
	src[i] = '\0';
	return (src);
}
int main ()
{
	printf("%s\n", ft_substr("a", 0, -3));
}