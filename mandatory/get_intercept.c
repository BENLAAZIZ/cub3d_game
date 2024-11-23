/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intercept.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:29:47 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/23 23:48:02 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_vertical_ray_steps(t_data *data, t_ray *ray, t_var *var)
{
      var->xintercept = floor(data->p_x / TILE_SIZE) * TILE_SIZE;
    if (ray->lookingRight)
        var->xintercept += TILE_SIZE;   
    var->yintercept = data->p_y + (var->xintercept - data->p_x) * tan(ray->rayAngle);
    var->xstep = TILE_SIZE;
    var->ystep = TILE_SIZE * tan(ray->rayAngle);
    if (ray->lookingLeft)
        var->xstep *= -1;
    if (ray->lookingUp && var->ystep > 0)
        var->ystep *= -1;
    if (ray->lookingDown && var->ystep < 0)
        var->ystep *= -1;
}

double get_v_intercept(t_data *data, t_ray *ray)
{
    t_var  var;

    init_vertical_ray_steps(data, ray, &var);
    while (var.xintercept >= 0 && var.xintercept <= data->lenght * TILE_SIZE 
            && var.yintercept >= 0 && var.yintercept <= data->height * TILE_SIZE)
    {
        if (ray->lookingLeft)
            var.xtocheck = var.xintercept - 0.001;
        else
           var.xtocheck = var.xintercept;
        var.ytocheck = var.yintercept;
        if (is_wall(data, var.ytocheck, var.xtocheck))
        {
            ray->v_hit_x = var.xintercept;
            ray->v_hit_y = var.yintercept;
            var.distance = sqrt(pow(data->p_x - var.xtocheck, 2) + pow(data->p_y - var.ytocheck, 2));
            return (var.distance);
        }
        var.xintercept += var.xstep;
        var.yintercept += var.ystep;
    }
    return (INT_MAX);
}


void    init_horizontal_ray_steps(t_data *data, t_ray *ray, t_var *var)
{
    var->yintercept = floor(data->p_y / TILE_SIZE) * TILE_SIZE;
    if (ray->lookingDown)
        var->yintercept += TILE_SIZE;
    var->xintercept = data->p_x + (var->yintercept - data->p_y) / tan(ray->rayAngle);
    var->ystep = TILE_SIZE;
    var->xstep = TILE_SIZE / tan(ray->rayAngle); 
    if (ray->lookingUp)
        var->ystep *= -1;
    if (ray->lookingLeft && var->xstep > 0)
        var->xstep *= -1;
    if (ray->lookingRight && var->xstep < 0)
        var->xstep *= -1;
}

double get_h_intercept(t_data *data, t_ray *ray)
{
    t_var  var;

    init_horizontal_ray_steps(data, ray, &var);
    while (var.xintercept >= 0 && var.xintercept <= data->lenght * TILE_SIZE
            && var.yintercept >= 0 && var.yintercept <= data->height * TILE_SIZE)
    {
        var.xtocheck = var.xintercept;
        if (ray->lookingUp)
            var.ytocheck = var.yintercept - 0.001;
        else
            var.ytocheck = var.yintercept;
        if (is_wall(data, var.ytocheck, var.xtocheck))
        {
            ray->h_hit_x = var.xintercept;
            ray->h_hit_y = var.yintercept;
            var.distance = sqrt(pow(data->p_x - var.xtocheck, 2) + pow(data->p_y - var.ytocheck, 2));
            return (var.distance);
        }
        var.xintercept += var.xstep;
        var.yintercept += var.ystep;
    }
    return (INT_MAX);
}
