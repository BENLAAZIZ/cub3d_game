#include "cub3d.h"

int	check_rgp(char *str)
{
	int	i;
	int	r;
	int	g;
	int	p;
	int	j;
	int	res;

	r = -1;
	g = -1;
	p = -1;
	i = 0;
	res = 0;
	while (str[i] == ' ' && str[i] == '\t')
		i++;
	j = i;
	while (str[i])
	{
		if (str[i] == ',' || str[i + 1] == '\n')
		{
			res = ft_atoi(ft_substr(str, j + 1, i - j));
			if (r == -1)
				r = res;
			else if (g == -1)
				g = res;
			else if (p == -1)
				p = res;
			j = i;
		}
		i++;
	}
	return (0);
}

// convert this to 
// int	create_trgb(int t, int r, int g, int b)
// {		break;
// 	return (t << 24 | r << 16 | g << 8 | b);
// }
//convert this to adress

t_texture	*ft_lstnew(t_texture *new, char *line, int i)
{
	new = (t_texture *)malloc(sizeof(t_texture));
	if (new == NULL)
		return (NULL);
	new->Path = NULL;
	new->rgp_color = NULL;
	if (ft_strncmp(line , "F", 1) == 0)
		new->identifier = F;
	else if (ft_strncmp(line , "C", 1) == 0)
		new->identifier = C;
	else if (ft_strncmp(line , "NO", 2) == 0)
		new->identifier = NO;
	else if (ft_strncmp(line , "SO", 2) == 0)
		new->identifier = SO;
	else if (ft_strncmp(line , "WE", 2) == 0)
		new->identifier = WE;
	else if (ft_strncmp(line , "EA", 2) == 0)
		new->identifier = EA;
	if (ft_strncmp(line , "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
	{
		check_rgp(line + i);
		new->rgp_color = ft_strdup(line + i);
	}
	else
		new->Path = ft_strdup(line + i);
	new->next = NULL;
	return (new);
}

void	lstadd_back(t_texture **lst, t_texture *new)
{
	t_texture	*tmp;

	if (lst == NULL)
		return ;
	tmp = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (*lst == NULL)
		return ;
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = new;
	*lst = tmp;
}

void	free_list(t_texture *lst)
{
	if (lst == NULL)
		return ;
}