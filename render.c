/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:58:15 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/18 12:11:58 by hben-laz         ###   ########.fr       */
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
                while (y < 10)
                {
                    x = 1;
                    while (x < 10)
                    {
                        mlx_pixel_put(data->mlx, data->win, (j * 10) + y, (i * 10) + x, 0x00FFFFFF);
                        x++;
                    }
                    y++;
                }
            }
            else if (data->all_map[i][j] == '0' || data->all_map[i][j] == 'N')
            {
                int y = 1;
                int x = 1;
                while (y < 10)
                {
                    x = 1;
                    while (x < 10)
                    {
                        mlx_pixel_put(data->mlx, data->win, (j * 10) + y, (i * 10) + x, 0x808080);
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
    double x = -2;
    double y = -2;
    double ray_y = data->p_y;
    double ray_x = data->p_x;
    double angle = data->angle;
    double ray_step = 0.5;
    double step_x = cos(angle) * ray_step;
    double step_y = sin(angle) * ray_step;

    while (y < 2)
    {
        x = -2;
        while (x < 2)
        {
            mlx_pixel_put(data->mlx, data->win, data->p_x + x, data->p_y + y, 0xFF0000);
            x++;
        }
        y++;
    }
    double z = 800;
    while (z)
    {
        if (is_wall(data, ray_y, ray_x))
                break;
        mlx_pixel_put(data->mlx, data->win, ray_x, ray_y, 0x40ff00);
        ray_x += step_x;
        ray_y += step_y;
        z--;
    }
    ray_y = data->p_y;
    ray_x = data->p_x;
    step_x = cos(angle - (FOV / 2)) * ray_step;
    step_y = sin(angle - (FOV / 2)) * ray_step;
    z = 800;
    while (z)
    {
        if (is_wall(data, ray_y, ray_x))
                break;
        mlx_pixel_put(data->mlx, data->win, ray_x, ray_y, 0x40ff00);
        ray_x += step_x;
        ray_y += step_y;
        z--;
    }
    ray_y = data->p_y;
    ray_x = data->p_x;
    step_x = cos(angle + (FOV / 2)) * ray_step;
    step_y = sin(angle + (FOV / 2)) * ray_step;
    z = 800;
    while (z)
    {
        if (is_wall(data, ray_y, ray_x))
                break;
        mlx_pixel_put(data->mlx, data->win, ray_x, ray_y, 0x40ff00);
        ray_x += step_x;
        ray_y += step_y;
        z--;
    }
    
}


void draw_floor(t_data *data, double distance, double column)
{
	double line_height;
   	double top_y;
   	double bottom_y;
	double window_height = data->height * 50.00;
    line_height = (window_height  / distance) * 30.0;
    top_y = window_height / 2 - line_height / 2;
    bottom_y = top_y + line_height;

	int i = bottom_y;
	while(i < window_height)
	{
		mlx_pixel_put(data->mlx, data->win_test, column, i, 0x629584);
		i++;
	}
	i = 0;
	while (i < top_y)
	{
		mlx_pixel_put(data->mlx, data->win_test, column, i, 0x243642);
		i++;
	}
}

int point_image_texture(t_data *data, int flag, t_image **img)
{
   
        if (flag == 0)
            *img = &data->image[0];
        if (flag == 1)
            *img = &data->image[1];
        if (flag == 2)
            *img = &data->image[2];
        if (flag == 3)
            *img = &data->image[3];
        if (*img == NULL)
            return (1);
    return (0);
}

void draw_wall(t_data *data, t_ray *ray, int column)
{
    //give me an other method to draw the wall to make it more clear with the texture
    double line_height;
    double top_y, bottom_y;
    double window_height = Scren_H;
    int color, y, tex_y, t_x;
    double texture_x;
    
    // line_height = (window_height / ray->distance) * TILE_SIZE;
    line_height = (window_height / ray->distance)  * TILE_SIZE * 0.5;
    top_y = window_height / 2 - line_height / 2;
    bottom_y = top_y + line_height;
    
    
    int flag = 0;
    if (ray->lookingDown && ray->flag == 1)
        flag = 1;
    else if (ray->lookingUp && ray->flag == 1)
        flag = 0;
    else if (ray->lookingRight && ray->flag == 0)
        flag = 2;
    else if (ray->lookingLeft && ray->flag == 0)
        flag = 3;
    
    t_image *img;
    if (point_image_texture(data, flag, &img))
    {
        printf("Failed to load texture\n");
        return;
    }
    
    if (ray->flag == 1)
        t_x = (int)ray->v_hit_y % 10;
    else
        t_x = (int)ray->h_hit_x % 10;
        
    texture_x = (int)((t_x / 10.00) * img->whith);
    if (texture_x < 0)
        texture_x = 0;
    else if (texture_x >= img->whith)
        texture_x = img->whith - 1;
    
    if (top_y < 0)
        top_y = 0;

    y = top_y;
    while (y < bottom_y )
    {
        tex_y = (y - top_y) * img->height / (bottom_y - top_y);
        // if (tex_y < 0 || tex_y >= img->height)
        // {
        //     y++;
        //     continue;
        // }
        // color = ((int *)img->addr)[img->whith * tex_y + (int)texture_x];
        color = 0xFF5733;
        mlx_pixel_put(data->mlx, data->win_test, column, y, color);
        y++;
    }
}
    