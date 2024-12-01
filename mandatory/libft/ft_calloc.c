

#include "../cub3d.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	of;

	of = count * size;
	if (count != 0 && of / count != size)
		return (NULL);
	p = malloc (count * size);
	if (p == 0)
		return (NULL);
	ft_bzero(p, (count * size));
	return (p);
}
