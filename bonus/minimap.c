/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:33:53 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/23 19:47:47 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



void    drawplayer(t_data *data)
{
    t_player    player;
    double      x;
    double      y;

    x = -2;
    y = -2;
    // player.ray_y = data->p_y / TILE_SIZE;
    // player.ray_x = data->p_x / TILE_SIZE;

     player.ray_y = data->p_y / data->tile_size_map;
    player.ray_x = data->p_x / data->tile_size_map;
    player.step_x = cos(data->angle - (FOV / 2)) * player.ray_step;
    player.step_y = sin(data->angle - (FOV / 2)) * player.ray_step;
    player.ray_step = 0.5;
    player.z = 100;
    draw_rays_minimap(data, &player); 
    while (y < 2)
    {
        x = -2;
        while (x < 2)
        {
			mlx_put_pixel(data->img, data->p_x + x, data->p_y + y, ft_pixel(0, 0, 255, 255));
            x++;
        }
        y++;
    }
}

int is_wall_map(t_data *data, double y, double x)
{
    if (x <= 0 || x >= data->lenght * data->tile_size_map || y <= 0 || y >= data->height * data->tile_size_map)
        return (1);
    if (data->all_map[(int)y / (int)data->tile_size_map][(int)x / (int)data->tile_size_map] == '1')
        return (1);
      
    return (0);
}

void    draw_rays_minimap(t_data *data, t_player *player)
{
     double rayAngle;

    rayAngle = data->angle - (FOV / 2);
    while (rayAngle < data->angle + (FOV / 2))
    {
        while (player->z)
        {
            if (is_wall_map(data, player->ray_y, player->ray_x))
                    break;
			mlx_put_pixel(data->img, player->ray_x, player->ray_y, ft_pixel(0, 255, 0, 255));
            player->ray_x += player->step_x;
            player->ray_y += player->step_y;
            player->z--;
        }
        player->ray_y = data->p_y;
        player->ray_x = data->p_x;
        rayAngle += 0.01;
        player->step_x = cos(rayAngle) * player->ray_step;
        player->step_y = sin(rayAngle) * player->ray_step;
        player->z = 100;
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
            if (data->all_map[i][j] == '1')
            {
                int y = 1;
                int x = 1;
                while (y < data->tile_size_map)
                {
                    x = 1;
                    while (x < data->tile_size_map)
                    {
						mlx_put_pixel(data->img, (j * data->tile_size_map) + y, (i * data->tile_size_map) + x, ft_pixel(255, 255, 255, 255));
                        x++;
                    }
                    y++;
                }
            }
            else if (data->all_map[i][j] == '0' || data->all_map[i][j] == 'N' || data->all_map[i][j] == 'S' || data->all_map[i][j] == 'E' || data->all_map[i][j] == 'W')
            {
                int y = 0;
                int x = 0;
                while (y < data->tile_size_map)
                {
                    x = 0;
                    while (x < data->tile_size_map)
                    {
						mlx_put_pixel(data->img, (j * data->tile_size_map) + y, (i * data->tile_size_map) + x, ft_pixel(0, 0, 0, 255));
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