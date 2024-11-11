/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:12:27 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/11 16:50:02 by hben-laz         ###   ########.fr       */
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

int get_color_from_distance(double distance)
{
    unsigned char   r;
    unsigned char   g;
    unsigned char   b;
    int             color;

    r = 255 - distance;
    g = 191 - distance;
    b = 200 - distance;
    color = r << 16 | g << 8 | b;
    return (color);
}


void draw_wall(t_data *data, double distance, double column)
{
    double line_height;
   	double top_y;
   	double bottom_y;
    // int color = 0xff6347; 
    // int image ;
    
	double window_height = data->height * 50.00;
    int color;
    
    line_height = (window_height  / distance) * 30.0;
    top_y = window_height / 2 - line_height / 2;
    bottom_y = top_y + line_height;
    if (top_y < 0)
        top_y = 0;
    if (bottom_y > window_height)
        bottom_y = window_height;
	int i = top_y;
    while (top_y <= bottom_y)
    {
        color = get_color_from_distance(distance); 

        // draw_textured_wall(data, screen_x, top_y, bottom_y, texture_x);
        
		if (top_y < 0)
			return ;
        mlx_pixel_put(data->mlx, data->win_test, column, top_y, color);
        top_y++;
    }
	top_y = i;
	while(i < top_y)
	{
		mlx_pixel_put(data->mlx, data->win_test, column, i, color);
		i++;
	}

}