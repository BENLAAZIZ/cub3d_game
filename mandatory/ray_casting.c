/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:26:31 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/23 23:51:37 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void init_ray(t_ray *ray)
{
    if (ray->rayAngle > 2 * M_PI)
        ray->rayAngle -= 2 * M_PI;
    if (ray->rayAngle < 0)
        ray->rayAngle += 2 * M_PI;
    ray->lookingDown = 0;
    ray->lookingUp = 0;
    ray->lookingRight = 0;
    ray->lookingLeft = 0;
}

int  castAllRay(t_data *data)
{
    double  rayAngle;
    double  column;
    t_ray   *ray = NULL;
        
    column = 0;
    rayAngle = data->angle - (FOV / 2);
    while (column < NUM_RAYS)
    {
        ray = malloc(sizeof(t_ray));
        ray->rayAngle = rayAngle;
        oneRay(data, ray);
        if (render_wall(data, ray, column))
            return (1);
        column++;
        rayAngle += FOV / NUM_RAYS;
        free(ray);
    }
    // drawmap(data);
    // drawplayer(data);
    return (0);
}

void oneRay(t_data *data, t_ray *ray)
{   
    init_ray(ray);
    if (ray->rayAngle > 0 && ray->rayAngle < M_PI)
        ray->lookingDown = 1;
    ray->lookingUp = !ray->lookingDown;
    if (ray->rayAngle < M_PI_2 || ray->rayAngle > 3 * M_PI_2)
        ray->lookingRight = 1;
    ray->lookingLeft = !ray->lookingRight;
    ray->v_distance = get_v_intercept(data, ray);
    ray->h_distance = get_h_intercept(data, ray);
    if (ray->v_distance <= ray->h_distance)
    {
        ray->distance = ray->v_distance / TILE_SIZE;
        ray->x_hit = ray->v_hit_x;
        ray->y_hit = ray->v_hit_y;
        ray->flag = 1;
    }
    else
    {
        ray->distance = ray->h_distance / TILE_SIZE;
        ray->x_hit = ray->h_hit_x;
        ray->y_hit = ray->h_hit_y;
        ray->flag = 0;
    }
}

