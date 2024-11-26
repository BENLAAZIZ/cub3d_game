/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:28:18 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/26 22:17:05 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int point_image_texture(t_data *data, t_ray *ray)
{
    if (!ray->flag && !(ray->rayangle > 0 && ray->rayangle < M_PI))
        data->imgx = &data->image[0];
    else if (!ray->flag && ray->rayangle >= 0 && ray->rayangle <= M_PI)
        data->imgx = &data->image[1];
    else if (ray->flag && ray->rayangle >= M_PI_2 && ray->rayangle <= 3 * M_PI_2)
        data->imgx = &data->image[2];
    else
        data->imgx = &data->image[3];
    if (data->imgx == NULL)
            return (1);
    return (0);
}


void draw_wall_column(t_data *data, t_var *var, int column)
{
    while (var->top_y < var->bottom_y)
    {
        if (var->top_y < 0)
            var->top_y = 0;
        if (var->top_y >= SCREEN_H)
            break;
        var->distance = (var->top_y + var->line_height / 2) - (SCREEN_H / 2);
        var->offset_y = var->distance * (data->imgx->texture->height / var->line_height);
        var->pixel =  (unsigned int *)data->imgx->texture->pixels;
        var->color = var->pixel[(var->offset_y * data->imgx->texture->width) + var->ofsset_var];
        var->color = ft_pixel(var->color >> 16, var->color >> 8, var->color, 255);
        mlx_put_pixel(data->img, column, var->top_y, var->color);
        var->top_y++;
    }  
}


int draw_wall(t_data *data, t_ray *ray, int column)
{
   t_var    var;
    
    var.line_height = (SCREEN_H / ray->distance) * 5;
    var.top_y = SCREEN_H / 2 - var.line_height / 2;
    var.bottom_y = SCREEN_H / 2 + var.line_height / 2;
    if (point_image_texture(data, ray))
    {
        printf("Failed to load texture\n");
        return (1);
    }
     if (ray->flag == 1)
        var.ofsset_var = (int)((ray->y_hit / T_S) * data->imgx->texture->width) % data->imgx->texture->width;
    else
        var.ofsset_var = (int)((ray->x_hit / T_S) * data->imgx->texture->width) % data->imgx->texture->width; 
    draw_wall_column(data, &var, column);
    return (0);
}

void draw_floor(t_data *data, double distance, double column)
{
	double  line_height;
   	double  top_y;
   	double  bottom_y;
	double  window_height;
    int     i;

    window_height = SCREEN_H;
    line_height = (window_height / distance) * 5;
    top_y = window_height / 2 - line_height / 2;
    bottom_y = top_y + line_height;
	i = bottom_y;
	while(i < window_height)
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

// void    drawplayer(t_data *data)
// {
//     t_player    player;
//     double      x;
//     double      y;

//     x = -2;
//     y = -2;
//     player.ray_y = data->p_y / T_S;
//     player.ray_x = data->p_x / T_S;
//     player.step_x = cos(data->angle - (FOV / 2)) * player.ray_step;
//     player.step_y = sin(data->angle - (FOV / 2)) * player.ray_step;
//     player.ray_step = 0.5;
//     player.z = 100;
//     draw_rays_minimap(data, &player); 
//     while (y < 2)
//     {
//         x = -2;
//         while (x < 2)
//         {
// 			mlx_put_pixel(data->img, data->p_x + x, data->p_y + y, ft_pixel(0, 0, 255, 255));
//             x++;
//         }
//         y++;
//     }
// }

// void    draw_rays_minimap(t_data *data, t_player *player)
// {
//      double rayangle;

//     rayangle = data->angle - (FOV / 2);
//     while (rayangle < data->angle + (FOV / 2))
//     {
//         while (player->z)
//         {
//             if (is_wall(data, player->ray_y, player->ray_x))
//                     break;
// 			mlx_put_pixel(data->img, player->ray_x, player->ray_y, ft_pixel(0, 255, 0, 255));
//             player->ray_x += player->step_x;
//             player->ray_y += player->step_y;
//             player->z--;
//         }
//         player->ray_y = data->p_y;
//         player->ray_x = data->p_x;
//         rayangle += 0.01;
//         player->step_x = cos(rayangle) * player->ray_step;
//         player->step_y = sin(rayangle) * player->ray_step;
//         player->z = 100;
//     }
    
// }
// void    drawmap(t_data *data)
// {
//     int i = 0;
//     int j = 0;

//     while (data->all_map[i])
//     {
//         j = 0;
//         while (data->all_map[i][j])
//         {
//             if (data->all_map[i][j] == '1')
//             {
//                 int y = 1;
//                 int x = 1;
//                 while (y < T_S)
//                 {
//                     x = 1;
//                     while (x < T_S)
//                     {
// 						mlx_put_pixel(data->img, (j * T_S) + y, (i * T_S) + x, ft_pixel(255, 255, 255, 255));
//                         x++;
//                     }
//                     y++;
//                 }
//             }
//             else if (data->all_map[i][j] == '0' || data->all_map[i][j] == 'N' || data->all_map[i][j] == 'S' || data->all_map[i][j] == 'E' || data->all_map[i][j] == 'W')
//             {
//                 int y = 0;
//                 int x = 0;
//                 while (y < T_S)
//                 {
//                     x = 0;
//                     while (x < T_S)
//                     {
// 						mlx_put_pixel(data->img, (j * T_S) + y, (i * T_S) + x, ft_pixel(0, 0, 0, 255));
//                         x++;
//                     }
//                     y++;
//                 }
//             }
//             j++;
//         }
//         i++;
//     }
// }