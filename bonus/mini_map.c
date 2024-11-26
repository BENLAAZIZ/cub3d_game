/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 01:33:30 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/26 22:17:05 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d_bonus.h"


void    drawplayer(t_data *data)
{
    t_player    player;
    double      x;
    double      y;

    x = 0;
    y = 0;
    player.ray_step = 0.1;
    player.ray_y = data->p_y / T_S;
    player.ray_x = data->p_x / T_S;
    player.step_x = cos(data->angle) * player.ray_step;
    player.step_y = sin(data->angle) * player.ray_step;
    player.z = 40;
    draw_rays_minimap(data, &player); 
    while (y < 3)
    {
        x = 0;
        while (x < 3)
        {
			mlx_put_pixel(data->img, player.ray_x * 10.0 + x, player.ray_y * 10.0  + y
                        , ft_pixel(255, 0, 0, 255));
            x++;
        }
        y++;
    }
}

void    draw_rays_minimap(t_data *data, t_player *player)
{
    double rayangle;

    rayangle = data->angle - (FOV / 2);
    while (rayangle < data->angle + (FOV / 2))
    {
        while (player->z)
        {
            if (is_wall_min(data, player->ray_y, player->ray_x))
                    break;
			mlx_put_pixel(data->img, player->ray_x * 10.0 + 1, player->ray_y * 10.0 + 1
                        , ft_pixel(255, 255, 0, 255));
            player->ray_x += player->step_x;
            player->ray_y += player->step_y;
            player->z--;
        }
        player->ray_y = data->p_y / T_S;
        player->ray_x = data->p_x / T_S;
        rayangle += 0.01;
        player->step_x = cos(rayangle) * player->ray_step;
        player->step_y = sin(rayangle) * player->ray_step;
        player->z = 40;
    }
    
}


void    map_suit_if(t_data *data, int i, int j)
{
    int x;
    int y;
    if (data->all_map[i][j] == '1')
    {
        y = 0;
        x = 0;
        while (y < 10)
        {
            x = 0;
            while (x < 10)
            {
                mlx_put_pixel(data->img, (j * 10) + y, (i * 10) + x, ft_pixel(255, 255, 255, 255));
                x++;
            }
            y++;
        }
    }
}

void    map_suit_else(t_data *data, int i, int j)
{
    int x;
    int y;

    if (data->all_map[i][j] == '0' 
        || data->all_map[i][j] == 'N' 
        || data->all_map[i][j] == 'S' 
        || data->all_map[i][j] == 'E' 
        || data->all_map[i][j] == 'W')
    {
        y = 0;
        x = 0;
        while (y < 10)
        {
            x = 0;
            while (x < 10)
            {
                mlx_put_pixel(data->img, (j * 10) + y, (i * 10) + x, ft_pixel(0, 0, 0, 200));
                x++;
            }
            y++;
        }
    }
}

void    drawmap(t_data *data)
{
    int i = 0;
    int j = 0;

    while (data->all_map[i])
    {
        j = 0;
        while (data->all_map[i][j])
        {
            map_suit_if(data, i, j);
            map_suit_else(data, i, j);
            j++;
        }
        i++;
    }
}
