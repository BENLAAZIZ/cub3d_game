/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:12:27 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/03 18:13:12 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void    drawmap(t_data *data)
{
    int i = 0;
    int j = 0;
    while (data->all_map[i])
    {
        j = 0;
        while (data->all_map[i][j])
        {
            if (data->all_map[i][j] == '1')
            {
                int y = 1;
                int x = 1;
                while (y < 50)
                {
                    x = 1;
                    while (x < 50)
                    {
                        mlx_pixel_put(data->mlx, data->win, (j * 50) + y, (i * 50) + x, 0x00FFFFFF);
                        x++;
                    }
                    y++;
                }
            }
            else if (data->all_map[i][j] == '0' || data->all_map[i][j] == 'N')
            {
                int y = 1;
                int x = 1;
                while (y < 50)
                {
                    x = 1;
                    while (x < 50)
                    {
                        mlx_pixel_put(data->mlx, data->win, (j * 50) + y, (i * 50) + x, 0x808080);
                        x++;
                    }
                    y++;
                }
            }
            j++;
        }
        i++;
    }
}



void    drawplayer(t_data *data)
{
    double x = -3;
    double y = -3;
    double ray_y = data->p_y;
    double ray_x = data->p_x;
    double angle = data->angle;
    double ray_step = 0.5;
    double step_x = cos(angle) * ray_step;
    double step_y = sin(angle) * ray_step;

    while (y < 3)
    {
        x = -3;
        while (x < 3)
        {
            mlx_pixel_put(data->mlx, data->win, data->p_x + x, data->p_y + y, 0xFF0000);
            x++;
        }
        y++;
    }
    double z = 400;
    while (z)
    {
        if (is_wall(data, ray_y, ray_x))
                break;
        mlx_pixel_put(data->mlx, data->win, ray_x, ray_y, 0x40ff00);
        ray_x -= step_x;
        ray_y -= step_y;
        z--;
    }
    ray_y = data->p_y;
    ray_x = data->p_x;
    step_x = cos(angle - (FOV / 2)) * ray_step;
    step_y = sin(angle - (FOV / 2)) * ray_step;
    z = 400;
    while (z)
    {
        if (is_wall(data, ray_y, ray_x))
                break;
        mlx_pixel_put(data->mlx, data->win, ray_x, ray_y, 0x40ff00);
        ray_x -= step_x;
        ray_y -= step_y;
        z--;
    }
    ray_y = data->p_y;
    ray_x = data->p_x;
    step_x = cos(angle + (FOV / 2)) * ray_step;
    step_y = sin(angle + (FOV / 2)) * ray_step;
    z = 400;
    while (z)
    {
        if (is_wall(data, ray_y, ray_x))
                break;
        mlx_pixel_put(data->mlx, data->win, ray_x, ray_y, 0x40ff00);
        ray_x -= step_x;
        ray_y -= step_y;
        z--;
    }
    
}


