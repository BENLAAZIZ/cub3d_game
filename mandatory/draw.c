/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:11:18 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/23 18:34:25 by hben-laz         ###   ########.fr       */
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

void dr(t_data *data, t_var *x, int column)
{
        while (x->top_y < x->bottom_y)
    {
        if (x->top_y < 0)
            x->top_y = 0;
        if (x->top_y >= Screen_H)
            break;
        x->distance = (x->top_y + x->line_height / 2) - (Screen_H / 2);
        x->offset_y = x->distance * (data->imgx->texture->height / x->line_height);
        x->pixel =  (unsigned int *)data->imgx->texture->pixels;
        x->color = x->pixel[(x->offset_y * data->imgx->texture->width) + x->ofsset_var];
        x->color = ft_pixel(x->color >> 16, x->color >> 8, x->color, 255);
        mlx_put_pixel(data->img, column, x->top_y, x->color);
        x->top_y++;
    }  
}


void draw_wall(t_data *data, t_ray *ray, int column)
{
   t_var x;
    

    x.line_height = (Screen_H / ray->distance) * 5;
    x.top_y = Screen_H / 2 - x.line_height / 2;
    x.bottom_y = Screen_H / 2 + x.line_height / 2;
    if (point_image_texture(data, ray))
    {
        printf("Failed to load texture\n");
        return;
    }
     if (ray->flag == 1)
        x.ofsset_var = (int)((ray->y_hit / TILE_SIZE) * data->imgx->texture->width) % data->imgx->texture->width;
    else
        x.ofsset_var = (int)((ray->x_hit / TILE_SIZE) * data->imgx->texture->width) % data->imgx->texture->width; 
    dr(data, &x, column);
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
