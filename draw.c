/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:12:27 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/18 18:28:42 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int _minimap(t_data *data, double y, double x)
{
    if (x < 0 || x > data->lenght * TILE_SIZE || y < 0 || y > data->height * TILE_SIZE)
        return (0);
    
    return (1);
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
	double window_height = Scren_H;
    line_height = (window_height / distance) * 5;
    top_y = window_height / 2 - line_height / 2;
    bottom_y = top_y + line_height;

	int i = bottom_y;
	while(i < window_height)
	{
        if(_minimap(data, i, column))
        {
            i++;
            continue;
        }
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

// int get_color_from_distance(double distance)
// {
//     unsigned char   r;
//     unsigned char   g;
//     unsigned char   b;
//     int             color;

//     r = 255 - distance;
//     g = 191 - distance;
//     b = 200 - distance;
//     color = r << 16 | g << 8 | b;
//     return (color);
// }


int get_texture_pixel_color(t_data *data, int texture_x, int texture_y, t_image *img)
{
    int color;
    // char *dst;
    (void)data;

    
     if (texture_x < 0 || texture_x >= img->whith || texture_y < 0 || texture_y >= img->height)
    {
        printf("Invalid texture coordinates: x=%d, y=%d\n", texture_x, texture_y);
        return 0; // Default color (black)
    }

    // Calculate the address of the pixel in the texture
    int *add = (int *)img->addr;
    color = add[((int)(texture_y * img->height + texture_x))];

    // Read the color of the pixel from the texture
    // color = *(unsigned int *)dst;
    return (color);
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
    double line_height;
    double top_y, bottom_y;
    double window_height = Scren_H;
    double color, y, tex_y, t_x;
    double texture_x;

    line_height = (window_height / ray->distance) * 5;
    top_y = window_height / 2 - line_height / 2;
    bottom_y = window_height / 2 + line_height / 2;

    int flag = 0;
      if ((ray->rayAngle > 0 && ray->rayAngle < M_PI_4) || (ray->rayAngle > 7 * M_PI_4 && ray->rayAngle <= 2 * M_PI))
        flag = 0;
    else if (ray->rayAngle >= M_PI_4 && ray->rayAngle < 3 * M_PI_4)
        flag = 1;
    else if (ray->rayAngle >= 3 * M_PI_4 && ray->rayAngle < 5 * M_PI_4)
        flag = 2;
    else if (ray->rayAngle >= 5 * M_PI_4 && ray->rayAngle <= 7 * M_PI_4)
        flag = 3;

    t_image *img;
    if (point_image_texture(data, flag, &img))
    {
        printf("Failed to load texture\n");
        return;
    }
    if (ray->flag == 1)
        t_x = ray->v_hit_y / 10.0;
    else
        t_x = ray->h_hit_x / 10.0;

    texture_x = t_x - floor(t_x);
    texture_x *= img->whith;

    y = top_y;
    while (y < bottom_y)
    {
        if (y < 0)
            y = 0;
        if (y >= window_height)
            break;
        if (_minimap(data, y, column))
        {
            y++;
            continue;
        }

        tex_y = (y - top_y) / (bottom_y - top_y);
        tex_y *= img->height;
        color = get_texture_pixel_color(data, texture_x, tex_y, img);
        mlx_pixel_put(data->mlx, data->win_test, column, y, color);
        y++;
    }
}
