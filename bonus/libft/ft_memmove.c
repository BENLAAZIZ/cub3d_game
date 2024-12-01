
#include "../cub3d_bonus.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*d;
	char	*s;

	i = 0;
	d = (char *)dst;
	s = (char *)src;
	if (d == NULL && s == NULL)
		return (NULL);
	while (i < len && d < s)
	{
		d[i] = s[i];
		i++;
	}
	while (len && d > s)
	{
		d[len - 1] = s[len - 1];
		len--;
	}
	return (dst);
}
