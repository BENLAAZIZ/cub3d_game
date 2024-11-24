/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:28:18 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/25 00:45:02 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int point_image_texture(t_data *data, t_ray *ray)
{
    if (!ray->flag && !(ray->rayAngle > 0 && ray->rayAngle < M_PI))
        data->imgx = &data->image[0];
    else if (!ray->flag && ray->rayAngle >= 0 && ray->rayAngle <= M_PI)
        data->imgx = &data->image[1];
    else if (ray->flag && ray->rayAngle >= M_PI_2 && ray->rayAngle <= 3 * M_PI_2)
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
        if (var->top_y >= Screen_H)
            break;
        var->distance = (var->top_y + var->line_height / 2) - (Screen_H / 2);
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
    
    var.line_height = (Screen_H / ray->distance) * 5;
    var.top_y = Screen_H / 2 - var.line_height / 2;
    var.bottom_y = Screen_H / 2 + var.line_height / 2;
    if (point_image_texture(data, ray))
    {
        printf("Failed to load texture\n");
        return (1);
    }
     if (ray->flag == 1)
        var.ofsset_var = (int)((ray->y_hit / TILE_SIZE) * data->imgx->texture->width) % data->imgx->texture->width;
    else
        var.ofsset_var = (int)((ray->x_hit / TILE_SIZE) * data->imgx->texture->width) % data->imgx->texture->width; 
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

    window_height = Screen_H;
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


int is_wall_min(t_data *data, double y, double x)
{
    if (x <= 0 || x >= data->lenght || y <= 0 || y >= data->height)
        return (1);
    if (data->all_map[(int)y][(int)x] == '1')
        return (1);
    return (0);
}


void    drawplayer(t_data *data)
{
    t_player    player;
    double      x;
    double      y;

    x = 0;
    y = 0;
    player.ray_step = 0.1;
    player.ray_y = data->p_y / TILE_SIZE;
    player.ray_x = data->p_x / TILE_SIZE;
    player.step_x = cos(data->angle) * player.ray_step;
    player.step_y = sin(data->angle) * player.ray_step;
    player.z = 40;
    draw_rays_minimap(data, &player); 
    while (y < 3)
    {
        x = 0;
        while (x < 3)
        {
			mlx_put_pixel(data->img, player.ray_x * 10.0 + x, player.ray_y * 10.0  + y, ft_pixel(255, 0, 0, 255));
            x++;
        }
        y++;
    }
}

void    draw_rays_minimap(t_data *data, t_player *player)
{
    double rayAngle;

    rayAngle = data->angle - (FOV / 2);
    while (rayAngle < data->angle + (FOV / 2))
    {
        while (player->z)
        {
            if (is_wall_min(data, player->ray_y, player->ray_x))
                    break;
			mlx_put_pixel(data->img, player->ray_x * 10.0 + 1, player->ray_y * 10.0 + 1, ft_pixel(255, 255, 0, 255));
            player->ray_x += player->step_x;
            player->ray_y += player->step_y;
            player->z--;
        }
        player->ray_y = data->p_y / TILE_SIZE;
        player->ray_x = data->p_x / TILE_SIZE;
        rayAngle += 0.01;
        player->step_x = cos(rayAngle) * player->ray_step;
        player->step_y = sin(rayAngle) * player->ray_step;
        player->z = 40;
    }
    
}

void    drawmap(t_data *data)
{
    int i = 0;
    int j = 0;
    int x;
    int y;

    while (data->all_map[i])
    {
        j = 0;
        while (data->all_map[i][j])
        {
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
            else if (data->all_map[i][j] == '0' || data->all_map[i][j] == 'N' || data->all_map[i][j] == 'S' || data->all_map[i][j] == 'E' || data->all_map[i][j] == 'W')
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
            j++;
        }
        i++;
    }
}
