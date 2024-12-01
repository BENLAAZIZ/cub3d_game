/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaaraba <aaaraba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:56:22 by aaaraba           #+#    #+#             */
/*   Updated: 2024/12/01 17:31:48 by aaaraba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	give_id(char *line, t_texture *new)
{
	new->color_ceiling = -1;
	new->color_floor = -1;
	new->path = NULL;
	new->next = NULL;
	if (ft_strncmp(line, "F", 1) == 0)
		new->identifier = F;
	else if (ft_strncmp(line, "C", 1) == 0)
		new->identifier = C;
	else if (ft_strncmp(line, "NO", 2) == 0)
		new->identifier = NO;
	else if (ft_strncmp(line, "SO", 2) == 0)
		new->identifier = SO;
	else if (ft_strncmp(line, "WE", 2) == 0)
		new->identifier = WE;
	else if (ft_strncmp(line, "EA", 2) == 0)
		new->identifier = EA;
}

t_texture	*ft_lstnew(t_texture *new, char *line, int i)
{
	new = (t_texture *)malloc(sizeof(t_texture));
	if (new == NULL)
		return (NULL);
	give_id(line, new);
	if (ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
	{
		if (new->identifier == F)
		{
			if (!check_rgp(line + i, -2, -2, &new->color_floor))
				return (lst_clear(&new), NULL);
		}
		else
		{
			if (!check_rgp(line + i, -2, -2, &new->color_ceiling))
				return (lst_clear(&new), NULL);
		}
	}
	else
	{
		new->path = ft_strtrim(line + i, " \n");
		if (new->path == NULL)
			return (lst_clear(&new), NULL);
	}
	return (new);
}
