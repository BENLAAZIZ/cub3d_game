/* ************************************************************************** */
/*	                                                                  */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:26:31 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/29 22:53:44 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_ray *ray)
{
	if (ray->rayangle > 2 * M_PI)
		ray->rayangle -= 2 * M_PI;
	if (ray->rayangle < 0)
		ray->rayangle += 2 * M_PI;
	ray->lookingdown = 0;
	ray->lookingup = 0;
	ray->lookingright = 0;
	ray->lookingleft = 0;
}

int	render_wall(t_data *data, t_ray *ray, double column)
{
	ray->distance *= cos(ray->rayangle - data->angle);
	ray->distance = ray->distance * 5;
	if (draw_wall(data, ray, column))
		return (1);
	draw_floor_ceiling(data, ray->distance, column);
	return (0);
}

void	one_ray(t_data *data, t_ray *ray)
{
	init_ray(ray);
	if (ray->rayangle > 0 && ray->rayangle < M_PI)
		ray->lookingdown = 1;
	ray->lookingup = !ray->lookingdown;
	if (ray->rayangle < M_PI_2 || ray->rayangle > 3 * M_PI_2)
		ray->lookingright = 1;
	ray->lookingleft = !ray->lookingright;
	ray->v_distance = get_v_intercept(data, ray);
	ray->h_distance = get_h_intercept(data, ray);
	if (ray->v_distance <= ray->h_distance)
	{
		ray->distance = ray->v_distance / T_S;
		ray->x_hit = ray->v_hit_x;
		ray->y_hit = ray->v_hit_y;
		ray->flag = 1;
	}
	else
	{
		ray->distance = ray->h_distance / T_S;
		ray->x_hit = ray->h_hit_x;
		ray->y_hit = ray->h_hit_y;
		ray->flag = 0;
	}
}

int	cast_rays(t_data *data)
{
	double	rayangle;
	double	column;
	t_ray	*ray;

	ray = NULL;
	column = 0;
	rayangle = data->angle - (FOV / 2);
	while (column < NUM_RAYS)
	{
		ray = malloc(sizeof(t_ray));
		if (ray == NULL)
			return (1);
		ray->rayangle = rayangle;
		one_ray(data, ray);
		if (render_wall(data, ray, column))
			return (1);
		column++;
		rayangle += FOV / NUM_RAYS;
		free(ray);
	}
	return (0);
}
