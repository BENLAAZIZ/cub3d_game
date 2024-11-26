/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intercept.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:29:47 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/26 22:17:05 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void    init_vertical_ray_steps(t_data *data, t_ray *ray, t_var *var)
{
      var->xintercept = floor(data->p_x / T_S) * T_S;
    if (ray->lookingright)
        var->xintercept += T_S;   
    var->yintercept = data->p_y + (var->xintercept - data->p_x) * tan(ray->rayangle);
    var->xstep = T_S;
    var->ystep = T_S * tan(ray->rayangle);
    if (ray->lookingleft)
        var->xstep *= -1;
    if (ray->lookingup && var->ystep > 0)
        var->ystep *= -1;
    if (ray->lookingdown && var->ystep < 0)
        var->ystep *= -1;
}

double get_v_intercept(t_data *data, t_ray *ray)
{
    t_var  var;

    init_vertical_ray_steps(data, ray, &var);
    while (var.xintercept >= 0 && var.xintercept <= data->lenght * T_S 
            && var.yintercept >= 0 && var.yintercept <= data->height * T_S)
    {
        if (ray->lookingleft)
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
    var->yintercept = floor(data->p_y / T_S) * T_S;
    if (ray->lookingdown)
        var->yintercept += T_S;
    var->xintercept = data->p_x + (var->yintercept - data->p_y) / tan(ray->rayangle);
    var->ystep = T_S;
    var->xstep = T_S / tan(ray->rayangle); 
    if (ray->lookingup)
        var->ystep *= -1;
    if (ray->lookingleft && var->xstep > 0)
        var->xstep *= -1;
    if (ray->lookingright && var->xstep < 0)
        var->xstep *= -1;
}

double get_h_intercept(t_data *data, t_ray *ray)
{
    t_var  var;

    init_horizontal_ray_steps(data, ray, &var);
    while (var.xintercept >= 0 && var.xintercept <= data->lenght * T_S
            && var.yintercept >= 0 && var.yintercept <= data->height * T_S)
    {
        var.xtocheck = var.xintercept;
        if (ray->lookingup)
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
