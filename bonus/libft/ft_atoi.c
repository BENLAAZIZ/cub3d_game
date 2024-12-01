
#include "../cub3d_bonus.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				s;
	unsigned long	r;

	i = 0;
	s = 0;
	r = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + str[i] - '0';
		str++;
		if (r > 255)
			return (-1);
	}
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0' && str[i] != '\n' && str[i] != ',')
		return (puts("daaaaaaz"), -1);
	if (s % 2 == 0)
		return (r);
	return (-r);
}
