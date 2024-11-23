/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intercept.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:12:55 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/23 18:34:25 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void    get_v_otils(t_data *data, t_ray *ray, t_var *x)
{
      x->xintercept = floor(data->p_x / TILE_SIZE) * TILE_SIZE;
    if (ray->lookingRight)
        x->xintercept += TILE_SIZE;   
    x->yintercept = data->p_y + (x->xintercept - data->p_x) * tan(ray->rayAngle);
    x->xstep = TILE_SIZE;
    x->ystep = TILE_SIZE * tan(ray->rayAngle);
    if (ray->lookingLeft)
        x->xstep *= -1;
    if (ray->lookingUp && x->ystep > 0)
        x->ystep *= -1;
    if (ray->lookingDown && x->ystep < 0)
        x->ystep *= -1;
}

double get_v_intercept(t_data *data, t_ray *ray)
{
    t_var  x;

    get_v_otils(data, ray, &x);
    while (x.xintercept >= 0 && x.xintercept <= data->lenght * TILE_SIZE 
            && x.yintercept >= 0 && x.yintercept <= data->height * TILE_SIZE)
    {
        if (ray->lookingLeft)
            x.xtocheck = x.xintercept - 0.001;
        else
           x.xtocheck = x.xintercept;
        x.ytocheck = x.yintercept;
        if (is_wall(data, x.ytocheck, x.xtocheck))
        {
            ray->v_hit_var = x.xintercept;
            ray->v_hit_y = x.yintercept;
            x.distance = sqrt(pow(data->p_x - x.xtocheck, 2) + pow(data->p_y - x.ytocheck, 2));
            return (x.distance);
        }
        x.xintercept += x.xstep;
        x.yintercept += x.ystep;
    }
    return (INT_MAX);
}


void    get_h_otils(t_data *data, t_ray *ray, t_var *x)
{
    x->yintercept = floor(data->p_y / TILE_SIZE) * TILE_SIZE;
    if (ray->lookingDown)
        x->yintercept += TILE_SIZE;
    x->xintercept = data->p_x + (x->yintercept - data->p_y) / tan(ray->rayAngle);
    x->ystep = TILE_SIZE;
    x->xstep = TILE_SIZE / tan(ray->rayAngle); 
    if (ray->lookingUp)
        x->ystep *= -1;
    if (ray->lookingLeft && x->xstep > 0)
        x->xstep *= -1;
    if (ray->lookingRight && x->xstep < 0)
        x->xstep *= -1;
}

double get_h_intercept(t_data *data, t_ray *ray)
{
    t_var  x;

    get_h_otils(data, ray, &x);
    while (x.xintercept >= 0 && x.xintercept <= data->lenght * TILE_SIZE
            && x.yintercept >= 0 && x.yintercept <= data->height * TILE_SIZE)
    {
        x.xtocheck = x.xintercept;
        if (ray->lookingUp)
            x.ytocheck = x.yintercept - 0.001;
        else
            x.ytocheck = x.yintercept;
        if (is_wall(data, x.ytocheck, x.xtocheck))
        {
            ray->h_hit_var = x.xintercept;
            ray->h_hit_y = x.yintercept;
            x.distance = sqrt(pow(data->p_x - x.xtocheck, 2) + pow(data->p_y - x.ytocheck, 2));
            return (x.distance);
        }
        x.xintercept += x.xstep;
        x.yintercept += x.ystep;
    }
    return (INT_MAX);
}

