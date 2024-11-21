/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersiction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:56:12 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/20 21:52:39 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_wall(t_data *data, double y, double x)
{
    if (x < 0 || x > data->lenght * TILE_SIZE || y < 0 || y > data->height * TILE_SIZE)
        return (1);
    if (data->all_map[(int)y / (int)TILE_SIZE][(int)x / (int)TILE_SIZE] == '1')
        return (1);
      
    return (0);
}


double get_v_intercept(t_data *data, t_ray *ray, double xstep, double ystep)
{
    double xintercept;
    double yintercept;
    double xtocheck;
    double ytocheck;
    double v_distance;
  
    xintercept = floor(data->p_x / TILE_SIZE) * TILE_SIZE;
    if (ray->lookingRight)
        xintercept += TILE_SIZE;   
    yintercept = data->p_y + (xintercept - data->p_x) * tan(ray->rayAngle);
    xstep = TILE_SIZE;
    ystep = TILE_SIZE * tan(ray->rayAngle);
    if (ray->lookingLeft)
        xstep *= -1;
    if (ray->lookingUp && ystep > 0)
        ystep *= -1;
    if (ray->lookingDown && ystep < 0)
        ystep *= -1;
    while (xintercept >= 0 && xintercept <= data->lenght * TILE_SIZE && yintercept >= 0 && yintercept <= data->height * TILE_SIZE)
    {
        if (ray->lookingLeft)
            xtocheck = xintercept - 1;
        else
           xtocheck = xintercept;
        ytocheck = yintercept;
        if (is_wall(data, ytocheck, xtocheck))
        {
            ray->v_hit_x = xintercept;
            ray->v_hit_y = yintercept;
            v_distance = sqrt(pow(data->p_x - xtocheck, 2) + pow(data->p_y - ytocheck, 2));
            return (v_distance);
        }
        xintercept += xstep;
        yintercept += ystep;
    }
    return (INT_MAX);
}


double get_h_intercept(t_data *data, t_ray *ray, double xstep, double ystep)
{
    double xintercept;
    double yintercept;
    double xtocheck;
    double ytocheck;
    double h_distance;

    yintercept = floor(data->p_y / TILE_SIZE) * TILE_SIZE;
    if (ray->lookingDown)
        yintercept += TILE_SIZE;
    xintercept = data->p_x + (yintercept - data->p_y) / tan(ray->rayAngle);
    ystep = TILE_SIZE;
    xstep = TILE_SIZE / tan(ray->rayAngle); 
    if (ray->lookingUp)
        ystep *= -1;
    if (ray->lookingLeft && xstep > 0)
        xstep *= -1;
    if (ray->lookingRight && xstep < 0)
        xstep *= -1;
    while (xintercept >= 0 && xintercept <= data->lenght * TILE_SIZE && yintercept >= 0 && yintercept <= data->height * TILE_SIZE)
    {
        xtocheck = xintercept;
        if (ray->lookingUp)
            ytocheck = yintercept - 1;
        else
            ytocheck = yintercept;
        if (is_wall(data, ytocheck, xtocheck))
        {
            ray->h_hit_x = xintercept;
            ray->h_hit_y = yintercept;
            h_distance = sqrt(pow(data->p_x - xtocheck, 2) + pow(data->p_y - ytocheck, 2));
            return (h_distance);
        }
        xintercept += xstep;
        yintercept += ystep;
    }
    return (INT_MAX);
}
