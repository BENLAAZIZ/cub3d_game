#include "cub3d.h"

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
		check_rgp(line + i, -1, -1, -1);
		new->rgp_color = ft_strdup(line + i);
	}
	else
		new->Path = ft_strtrim(line + i, " \n");
	new->next = NULL;
	return (new);
}