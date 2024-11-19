/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:12:27 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/19 22:53:12 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int _minimap(t_data *data, double y, double x)
// {
//     if (x <= 0 || x > data->lenght * TILE_SIZE || y <= 0 || y > data->height * TILE_SIZE)
//         return (0);
//     return (1);
// }



void    drawmap(t_data *data)
{
    int i;
    int j;
    int y;
    int x;
    
    i = 0;
    while (data->all_map[i])
    {
        j = 0;
        while (data->all_map[i][j])
        {
            if (data->all_map[i][j] == '1')
            {
                y = 0;
                while (y < TILE_SIZE)
                {
                    x = 0;
                    while (x < TILE_SIZE)
                    {
                        mlx_pixel_put(data->mlx, data->win_test, (j * TILE_SIZE) + y, (i * TILE_SIZE) + x, 0x00FFFFFF);
                        x++;
                    }
                    y++;
                }
            }
            else if (data->all_map[i][j] == '0' || data->all_map[i][j] == 'N')
            {
                y = 0;
                while (y < TILE_SIZE)
                {
                    x = 0;
                    while (x < TILE_SIZE)
                    {
                        mlx_pixel_put(data->mlx, data->win_test, (j * TILE_SIZE) + y, (i * TILE_SIZE) + x, 0x808080);
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


void    draw_rays_minimap(t_data *data, t_player *player)
{
     double rayAngle;
     rayAngle = data->angle - (FOV / 2);
    while (rayAngle < data->angle + (FOV / 2))
    {
        while (player->z)
        {
            if (is_wall(data, player->ray_y, player->ray_x))
                    break;
            mlx_pixel_put(data->mlx, data->win_test, player->ray_x, player->ray_y, 0x40ff00);
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


void    drawplayer(t_data *data)
{
    t_player    player;
    double      x;
    double      y;

    x = -2;
    y = -2;
    player.ray_y = data->p_y;
    player.ray_x = data->p_x;
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
            mlx_pixel_put(data->mlx, data->win_test, data->p_x  + x, data->p_y + y, 0xFF0000);
            x++;
        }
        y++;
    }
}


void draw_floor(t_data *data, double distance, double column)
{
	double line_height;
   	double top_y;
   	double bottom_y;
	
    line_height = (Scren_H / distance) * 5;
    top_y = Scren_H / 2 - line_height / 2;
    bottom_y = top_y + line_height;

	int i = bottom_y - 1;
	while(++i < Scren_H)
		mlx_pixel_put(data->mlx, data->win_test, column, i, 0x629584);
	i = -1;
	while (++i < top_y)
		mlx_pixel_put(data->mlx, data->win_test, column, i, 0x243642);
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


int get_texture_pixel_color(int texture_x, int texture_y, t_image *img)
{
    int color;
    // char *dst;
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
        else if (flag == 1)
            *img = &data->image[1];
        else if (flag == 2)
            *img = &data->image[2];
        else if (flag == 3)
            *img = &data->image[3];
        else if (*img == NULL)
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
    t_image *img;

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

    // if (ray->lookingDown && ray->flag == 1)
    //     flag = 0;
    // else if (ray->lookingUp && ray->flag == 1) 
    //     flag = 1;
    // else if (ray->lookingRight && ray->flag == 0)
    //     flag = 2;
    // else if (ray->lookingLeft && ray->flag == 0)
    //     flag = 3;

    if (point_image_texture(data, flag, &img))
    {
        printf("Failed to load texture\n");
        return;
    }
    if (ray->flag == 1)
        t_x = ray->v_hit_y / TILE_SIZE;
    else
        t_x = ray->h_hit_x / TILE_SIZE;

    texture_x = t_x - floor(t_x);
    texture_x *= img->whith;

    y = top_y;
    while (y < bottom_y)
    {
        if (y < 0)
            y = 0;
        if (y >= window_height)
            break;
        tex_y = (y - top_y) / (bottom_y - top_y);
        tex_y *= img->height;
        color = get_texture_pixel_color(texture_x, tex_y, img);
        mlx_pixel_put(data->mlx, data->win_test, column, y, color);
        y++;
    }  
}
