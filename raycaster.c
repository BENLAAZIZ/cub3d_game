/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:38:53 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/14 11:03:05 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"


void get_player_position(t_data *data)
{
    if (data->all_map == NULL)
        return ;
    while (data->all_map[(int)data->p_y])
    {
        data->p_x = 0;
        while (data->all_map[(int)data->p_y][(int)data->p_x])
        {
            if (data->all_map[(int)data->p_y][(int)data->p_x] == 'N')
                break;
            data->p_x++;
        }
        if (data->all_map[(int)data->p_y][(int)data->p_x] == 'N')
            break;
        data->p_y++;
    }
    data->p_x = (data->p_x * 10) + 5;
    data->p_y = (data->p_y * 10) + 5;
}

void init_ray(t_ray *ray)
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
        ray->distance = ray->v_distance;
        ray->x_hit = ray->v_hit_x;
        ray->y_hit = ray->v_hit_y;
        ray->flag = 1;
        
        int x = -1;
        int y = -1;
        while (y < 1)
        {
            x = -1;
            while (x < 1)
            {
                mlx_pixel_put(data->mlx, data->win, ray->v_hit_x + x, ray->v_hit_y + y, 0xF61108);
                    x++;
            }
            y++;
        }
    }
    else
    {
        ray->distance = ray->h_distance;
        ray->x_hit = ray->h_hit_x;
        ray->y_hit = ray->h_hit_y;
        ray->flag = 0;
         int x = -1;
        int y = -1;
           while (y < 1)
        {
        x = -1;
        while (x < 1)
        {
        mlx_pixel_put(data->mlx, data->win, ray->h_hit_x + x, ray->h_hit_y + y, 0xF61108);
            x++;
        }
        y++;
        }
    }
}

void render_wall(t_data *data, t_ray *ray, double *column)
{
     ray->distance *= cos(ray->rayAngle - data->angle);
     ray->distance = ray->distance * 5;
        draw_wall(data, ray  , *column);
        draw_floor(data, ray->distance , *column);
        (*column)++;
}

void  castAllRay(t_data *data)
{
    double  rayAngle;
    double  rayStep;
    t_ray   *ray;
    double column;
        
    column = 0;
    rayAngle = data->angle - (FOV / 2 );
    rayStep = ( 5 * M_PI / 180) / 50;
    while (rayAngle <= data->angle + (FOV / 2))
    {
        ray = malloc(sizeof(t_ray));
        ray->rayAngle = rayAngle;
        oneRay(data, ray);
        printf("v_hit_y = %f\n", ray->v_hit_y);
        printf ("ray->h_hit_x = %f\n", ray->h_hit_x);
        render_wall(data, ray, &column);
        rayAngle += rayStep;
        free(ray);
    }
}


int get_image_texture(t_data *data)
{
    data->image[0].image = mlx_xpm_file_to_image(data->mlx, "monaliza_xpm.xpm", &data->image[0].whith, &data->image[0].height);
    data->image[1].image = mlx_xpm_file_to_image(data->mlx, "monaliza_xpm.xpm", &data->image[1].whith, &data->image[1].height);
    data->image[2].image = mlx_xpm_file_to_image(data->mlx, "monaliza_xpm.xpm", &data->image[2].whith, &data->image[2].height);
    data->image[3].image = mlx_xpm_file_to_image(data->mlx, "monaliza_xpm.xpm", &data->image[3].whith, &data->image[3].height);
    if (!data->image[0].image || !data->image[1].image || !data->image[2].image || !data->image[3].image)
    {
        printf("Failed to load texture\n");
        return (1);
    }
    return (0);
}

int get_addr_texture(t_data *data)
{
    int i = 0;
    while (i < 4)
    {
        data->image[i].addr = mlx_get_data_addr(data->image[i].image, 
                                    &data->image[i].bits_per_pixel,
                                     &data->image[i].line_length,
                                      &data->image[i].endian);
        i++;
    }
    return (0);
}

int create_window(char **map)
{
    t_data data;
    int len = 0;
    
    data.p_y = 0;
    data.p_x = 0;
    data.angle = 0.0;
    while (map[len])
        len++;
    data.mlx = mlx_init();
    data.lenght = ft_strlen(map[0]);
    data.height = len;
    data.win = mlx_new_window(data.mlx, data.lenght*10 , data.height*10 , "hello");
    data.win_test = mlx_new_window(data.mlx, 600, data.height * 50, "test");
//****************************************
     if (get_image_texture(&data))
        return 1;
    if (get_addr_texture(&data))
        return 1;
//*******************************************
    data.all_map = map;
    get_player_position(&data);
    drawmap(&data);
    drawplayer(&data);
    castAllRay(&data);
    mlx_hook(data.win, 2, 0, key_press, &data);
    mlx_hook(data.win_test, 2, 0, key_press, &data);
    mlx_loop(data.mlx);
    return (0);
}
