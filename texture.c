/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:12:27 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/14 12:49:53 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



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


// void draw_wall(t_data *data, double distance, double column)
// {
//     double line_height;
//    	double top_y;
//    	double bottom_y;
//     // int color = 0xff6347; 
//     // int image ;
    
// 	double window_height = data->height * 50.00;
//     int color;
    
//     line_height = (window_height  / distance) * 30.0;
//     top_y = window_height / 2 - line_height / 2;
//     bottom_y = top_y + line_height;
//     if (top_y < 0)
//         top_y = 0;
//     if (bottom_y > window_height)
//         bottom_y = window_height;
// 	int i = top_y;
//     while (top_y <= bottom_y)
//     {
//         color = get_color_from_distance(distance); 

//         // draw_textured_wall(data, screen_x, top_y, bottom_y, texture_x);
        
// 		if (top_y < 0)
// 			return ;
//         mlx_pixel_put(data->mlx, data->win_test, column, top_y, color);
//         top_y++;
//     }
// 	top_y = i;
// 	while(i < top_y)
// 	{
// 		mlx_pixel_put(data->mlx, data->win_test, column, i, color);
// 		i++;
// 	}

// }

t_image *point_image_texture(t_data *data, int flag)
{
    flag = 0;
    return (data->image[0].image);
    // while (data->tex)
    // {
    //     if (data->tex->identifier == flag)
    //         return (data->image[0].image);
    //     if (data->tex->identifier == flag)
    //         return (data->image[1].image);
    //     if (data->tex->identifier == flag)
    //         return (data->image[2].image);
    //     if (data->tex->identifier == flag)
    //         return (data->image[3].image);
    //     data->tex = data->tex->next;
    // }
    // return (NULL);
}

int get_texture_pixel_color(int texture_x, int texture_y, t_image *img)
{
    int color;
    char *dst;
  

    // Calculate the address of the pixel in the texture

    dst = img->addr 
            + (texture_y * img->line_length
            + texture_x * (img->bits_per_pixel / 8));
    
    // dst = data->image[0].addr 
    //         + (texture_y * data->image[0].line_length
    //         + texture_x * (data->image[0].bits_per_pixel / 8));

    // Read the color of the pixel from the texture
    color = *(unsigned int *)dst;
    return (color);
}


void draw_wall(t_data *data, t_ray *ray, int column)
{
    double line_height;
   	double top_y;
   	double bottom_y;
	double window_height = data->height * 50.00;
    int color;
     int y;
    int t_x;
    int tex_y;
    int texture_x;
    
    line_height = (window_height  / ray->distance) * 30.0;
    top_y = window_height / 2 - line_height / 2;
    bottom_y = top_y + line_height;
    if (top_y < 0)
        top_y = 0;
    if (bottom_y > window_height)
        bottom_y = window_height;
    if (ray->flag == 1)
        t_x = (int)ray->v_hit_y % 50;
    else
        t_x = (int)ray->h_hit_x % 50;



     int flag = 0;

    // Calculate the address of the pixel in the texture
    if (ray->lookingUp)
        flag = 0;
    else if (ray->lookingDown)
        flag = 1;
    else if (ray->lookingLeft)
        flag = 2;
    else if (ray->lookingRight)
        flag = 3;
        t_image *img = point_image_texture(data, flag);  
        if (img == NULL)
        {
            printf("Failed to load texture\n");
            return ;
        }
         
    texture_x = (int)(t_x * (img->whith / 50));
    
    y = top_y;
    while (y < bottom_y)
    {
        // Calculate the Y coordinate on the texture
        tex_y = (y - top_y) * img->height / (bottom_y - top_y);
        // Get the pixel color from the texture at (texture_x, tex_y)
        color = get_texture_pixel_color(texture_x, tex_y , img);
        // Draw the pixel on the screen
        mlx_pixel_put(data->mlx, data->win_test, column, y, color);
        y++;
    }
}
