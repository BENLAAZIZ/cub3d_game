/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 01:48:45 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/25 02:03:19 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int get_image_texture(t_data *data, t_texture *tex, int i)
{
    while (tex)
    {
        if (tex->identifier != F && tex->identifier != C)
		{
			data->image[i].texture = mlx_load_png(tex->Path);
			data->image[i].image = mlx_texture_to_image(data->mlx, data->image[i].texture);
			mlx_delete_image(data->mlx, data->image[i].image);
		}
		else
		{
			if (tex->identifier == F)
				data->floor_color = tex->color_floor;
			else
				data->ceiling_color = tex->color_ceiling;
		}
		i++;
        tex = tex->next;
    }
	i = -1;
	while (++i < 4)
	{
		if (data->image[i].image == NULL || data->image[i].texture == NULL)
			return (1);
	}
    return (0); 
}

int point_image_texture(t_data *data, t_ray *ray)
{
    if (!ray->flag && !(ray->rayAngle > 0 && ray->rayAngle < M_PI))
        data->imgx = &data->image[0];
    else if (!ray->flag && ray->rayAngle >= 0 && ray->rayAngle <= M_PI)
        data->imgx = &data->image[1];
    else if (ray->flag && ray->rayAngle >= M_PI_2 && ray->rayAngle <= 3 * M_PI_2)
        data->imgx = &data->image[2];
    else
        data->imgx = &data->image[3];
    if (data->imgx == NULL)
            return (1);
    return (0);
}

void delete_texture(t_data *data)
{
	int i;

	i = 0;
	while (i < 4)
	{
		mlx_delete_texture(data->image[i].texture);
		i++;
	}
}

