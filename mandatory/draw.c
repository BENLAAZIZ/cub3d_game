/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:11:18 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/23 17:58:56 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

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


void draw_wall(t_data *data, t_ray *ray, int column)
{
    double          line_height;
    double          top_y;
    double          bottom_y;
    int             color;
    int             ofsset_x;
    int             offset_y;
    int             distance;
    unsigned int*   pixel;
    

    line_height = (Screen_H / ray->distance) * 5;
    top_y = Screen_H / 2 - line_height / 2;
    bottom_y = Screen_H / 2 + line_height / 2;
    if (point_image_texture(data, ray))
    {
        printf("Failed to load texture\n");
        return;
    }
     if (ray->flag == 1)
        ofsset_x = (int)((ray->y_hit / TILE_SIZE) * data->imgx->texture->width) % data->imgx->texture->width;
    else
        ofsset_x = (int)((ray->x_hit / TILE_SIZE) * data->imgx->texture->width) % data->imgx->texture->width;
    while (top_y < bottom_y)
    {
        if (top_y < 0)
            top_y = 0;
        if (top_y >= Screen_H)
            break;
        distance = (top_y + line_height / 2) - (Screen_H / 2);
        offset_y = distance * (data->imgx->texture->height / line_height);
        pixel =  (unsigned int *)data->imgx->texture->pixels;
        color = pixel[(offset_y * data->imgx->texture->width) + ofsset_x];
        color = ft_pixel(color >> 16, color >> 8, color, 255);
        mlx_put_pixel(data->img, column, top_y, color);
        top_y++;
    }  
}

void draw_floor(t_data *data, double distance, double column)
{
	double  line_height;
   	double  top_y;
   	double  bottom_y;
	double  window_height;
    int     i;

    window_height = Screen_H;
    line_height = (window_height / distance) * 5;
    top_y = window_height / 2 - line_height / 2;
    bottom_y = top_y + line_height;
	i = bottom_y;
	while(i < window_height)
	{
        mlx_put_pixel(data->img, column, i, data->floor_color);
		i++;
	}
	i = 0;
	while (i < top_y)
	{
        mlx_put_pixel(data->img, column, i, data->ceiling_color);
		i++;
	}
}
