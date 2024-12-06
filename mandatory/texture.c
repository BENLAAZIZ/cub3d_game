/* ************************************************************************** */
/*	                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 01:48:45 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/30 00:48:53 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_image_texture(t_data *data, t_texture *tex, int i)
{
	while (tex)
	{
		if (tex->identifier != F && tex->identifier != C)
		{
			data->image[i].texture = mlx_load_png(tex->path);
			if (data->image[i].texture == NULL)
				return (1);
			i++;
		}
		tex = tex->next;
	}
	return (0);
}

int	get_image_texture(t_data *data, t_texture *tex, int i)
{
	while (tex)
	{
		if (tex->identifier != F && tex->identifier != C)
		{
			data->image[i].image = mlx_texture_to_image(data->mlx,
					data->image[i].texture);
			if (data->image[i].image == NULL)
				return (1);
			mlx_delete_image(data->mlx, data->image[i].image);
			i++;
		}
		else
		{
			if (tex->identifier == F)
				data->floor_color = tex->color_floor;
			else
				data->ceiling_color = tex->color_ceiling;
		}
		tex = tex->next;
	}
	return (0);
}

int	point_image_texture(t_data *data, t_ray *ray)
{
	if (!ray->flag && !(ray->rayangle > 0 && ray->rayangle < M_PI))
		data->imgx = &data->image[0];
	else if (!ray->flag && ray->rayangle >= 0 && ray->rayangle <= M_PI)
		data->imgx = &data->image[1];
	else if (ray->flag && ray->rayangle >= M_PI_2
		&& ray->rayangle <= 3 * M_PI_2)
		data->imgx = &data->image[2];
	else
		data->imgx = &data->image[3];
	if (data->imgx == NULL)
		return (1);
	return (0);
}
