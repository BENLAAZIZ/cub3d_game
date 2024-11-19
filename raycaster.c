/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:38:53 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/20 00:35:17 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

int     get_player_direction(t_data *data)
{
    if (data->all_map[(int)data->p_y][(int)data->p_x] == 'N')
    {
        data->angle = 3 * M_PI_2;
        return (1);
    }
    if (data->all_map[(int)data->p_y][(int)data->p_x] == 'S')
    {
        data->angle = M_PI_2;
        return (1);
    }
    if (data->all_map[(int)data->p_y][(int)data->p_x] == 'E')
    {
        data->angle = 0;
        return (1);
    }
    if (data->all_map[(int)data->p_y][(int)data->p_x] == 'W')
    {
        data->angle = M_PI;
        return (1);
    }
    return (0);
}

void    get_player_position(t_data *data)
{
    if (data->all_map == NULL)
        return ;
    while (data->all_map[(int)data->p_y])
    {
        data->p_x = 0;
        while (data->all_map[(int)data->p_y][(int)data->p_x])
        {
            if (get_player_direction(data))
                break;
            data->p_x++;
        }
        if (data->all_map[(int)data->p_y][(int)data->p_x] == 'N')
            break;
        data->p_y++;
    }
    data->p_x = (data->p_x * TILE_SIZE) + TILE_SIZE / 2;
    data->p_y = (data->p_y * TILE_SIZE) + TILE_SIZE / 2;
}

void    init_ray(t_ray *ray)
{
    if (ray->rayAngle > 2 * M_PI)
        ray->rayAngle -= 2 * M_PI;
    if (ray->rayAngle < 0)
        ray->rayAngle += 2 * M_PI;
    ray->v_distance = 0;
    ray->h_distance = 0;
    ray->v_hit_x = 0;
    ray->v_hit_y = 0;
    ray->h_hit_x = 0;
    ray->h_hit_y = 0;
    ray->lookingDown = 0;
    ray->lookingUp = 0;
    ray->lookingRight = 0;
    ray->lookingLeft = 0;
}


void oneRay(t_data *data, t_ray *ray)
{   
    init_ray(ray);
    if (ray->rayAngle > 0 && ray->rayAngle < M_PI)
        ray->lookingDown = 1;
    ray->lookingUp = !ray->lookingDown;
    if (ray->rayAngle < M_PI_2 || ray->rayAngle > 3 * M_PI_2)
        ray->lookingRight = 1;
    ray->lookingLeft = !ray->lookingRight;
    ray->v_distance = get_v_intercept(data, ray, 0, 0);
    ray->h_distance = get_h_intercept(data, ray, 0, 0);
    if (ray->v_distance <= ray->h_distance)
    {
        ray->distance = ray->v_distance / TILE_SIZE;
        ray->x_hit = ray->v_hit_x;
        ray->y_hit = ray->v_hit_y;
        ray->flag = 1;
    }
    else
    {
        ray->distance = ray->h_distance / TILE_SIZE;
        ray->x_hit = ray->h_hit_x / TILE_SIZE;
        ray->y_hit = ray->h_hit_y / TILE_SIZE;
        ray->flag = 0;
    }
}

void render_wall(t_data *data, t_ray *ray, double column)
{
     ray->distance *= cos(ray->rayAngle - data->angle);
     ray->distance = ray->distance * 5;
     draw_wall(data, ray  , column);
     draw_floor(data, ray->distance , column);
}

// void  castAllRay(t_data *data)
// {
//     double  rayAngle;
//     t_ray   ray;
//     double column;
        
//     column = 0;
//     rayAngle = data->angle - (FOV / 2);
//     while (column < NUM_RAYS)
//     {
//         ray.rayAngle = rayAngle;
//         oneRay(data, &ray);
//         render_wall(data, &ray, column);
//         column++;
//         rayAngle += FOV / NUM_RAYS;
//     }
//     drawmap(data);
//     drawplayer(data);
// }


void  castAllRay(t_data *data)
{
    double  rayAngle;
    t_ray   ray;
    double column;
        
    column = 0;
    data->image->image = mlx_new_image(data->mlx, Scren_W + 1, Scren_H + 1);
	// if (!data->img.img)
	// 	return (free_render(data, 0));
	data->image->addr = mlx_get_data_addr(data->image->image, &data->image->bits_per_pixel, &data->image->line_length, &data->image->endian);

    
    rayAngle = data->angle - (FOV / 2);
    while (column < NUM_RAYS)
    {
        ray.rayAngle = rayAngle;
        oneRay(data, &ray);
        render_wall(data, &ray, column);
        column++;
        rayAngle += FOV / NUM_RAYS;
    }
    drawmap(data);
    drawplayer(data);
}

int create_window(char **map, t_texture *tex)
{
    t_data data;
    int len = 0;
    
    data.angle =  M_PI_2;
    while (map[len])
        len++;
    data.mlx = mlx_init();
    data.lenght = ft_strlen(map[0]);
    data.height = len;
    // data.win = mlx_new_window(data.mlx, data.lenght*10 , data.height*10 , "hello");
    data.win_test = mlx_new_window(data.mlx, Scren_W, Scren_H, "test");
 
//****************************************
     if (get_image_texture(&data, tex))
        return 1;
    if (get_addr_texture(&data))
        return 1;
    clear_texture(tex);
//*******************************************
    data.all_map = map;
    get_player_position(&data);
    // drawmap(&data);
    // drawplayer(&data);
    castAllRay(&data);
    // mlx_hook(data.win, 2, 0, key_press, &data);
    mlx_hook(data.win_test, 2, 0, key_press, &data);
    mlx_hook(data.win_test, 6, 0, mouse_rotate, &data);
    mlx_loop(data.mlx);
    return (0);
}
