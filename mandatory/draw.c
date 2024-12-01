/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:28:18 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/29 21:54:44 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_column(t_data *data, t_var *var, int column)
{
	while (var->top_y < var->bottom_y)
	{
		if (var->top_y < 0)
			var->top_y = 0;
		if (var->top_y >= SCREEN_H)
			break ;
		var->distance = (var->top_y + var->line_height / 2) - (SCREEN_H / 2);
		var->offset_y
			= var->distance * (data->imgx->texture->height / var->line_height);
		var->pixel = (unsigned int *)data->imgx->texture->pixels;
		var->color = var->pixel[(var->offset_y * data->imgx->texture->width)
			+ var->ofsset_x];
		var->color
			= ft_pixel(var->color >> 16, var->color >> 8, var->color, 255);
		mlx_put_pixel(data->img, column, var->top_y, var->color);
		var->top_y++;
	}
}

int	draw_wall(t_data *data, t_ray *ray, int column)
{
	t_var	var;

	var.line_height = (SCREEN_H / ray->distance) * 5;
	var.top_y = SCREEN_H / 2 - var.line_height / 2;
	var.bottom_y = SCREEN_H / 2 + var.line_height / 2;
	if (point_image_texture(data, ray))
	{
		printf("Failed to load texture\n");
		return (1);
	}
	if (ray->flag == 1)
		var.ofsset_x = (int)((ray->y_hit / T_S)
				* data->imgx->texture->width) % data->imgx->texture->width;
	else
		var.ofsset_x = (int)((ray->x_hit / T_S)
				* data->imgx->texture->width) % data->imgx->texture->width;
	draw_wall_column(data, &var, column);
	return (0);
}

void	draw_floor_ceiling(t_data *data, double distance, double column)
{
	double	line_height;
	double	top_y;
	double	bottom_y;
	double	window_height;
	int		i;

	window_height = SCREEN_H;
	line_height = (window_height / distance) * 5;
	top_y = window_height / 2 - line_height / 2;
	bottom_y = top_y + line_height;
	i = bottom_y;
	while (i < window_height)
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
