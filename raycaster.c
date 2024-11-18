/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:38:53 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/18 18:19:23 by hben-laz         ###   ########.fr       */
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
        ray->distance = ray->v_distance / 10;
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
        ray->distance = ray->h_distance / 10;
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

void render_wall(t_data *data, t_ray *ray, double column)
{
     ray->distance *= cos(ray->rayAngle - data->angle);
     ray->distance = ray->distance * 5;
     draw_wall(data, ray  , column);
     draw_floor(data, ray->distance , column);
        // (*column)++;
}


// void lstadd_back_ray(t_ray **lst, t_ray *new)
// {
//     t_ray *tmp;
//     if (!*lst)
//     {
//         *lst = new;
//         return ;
//     }
//     tmp = *lst;
//     while (tmp->next)
//         tmp = tmp->next;
//     tmp->next = new;
// }

// void  castAllRay(t_data *data)
// {
//     double  rayAngle;
//     t_ray   *ray = NULL;
//     t_ray  *tmp;
//     double column;
        
//     column = 0;
//     rayAngle = data->angle - (FOV / 2);
 
//     int i = 0;
//     rayAngle = data->angle - (FOV / 2);
//     while (i < NUM_RAYS)
//     {
//         tmp = malloc(sizeof(t_ray));
//         tmp->next = NULL;
//         tmp->rayAngle = rayAngle;
//         oneRay(data, tmp);
//         lstadd_back_ray(&ray, tmp);
//         i++;
//         rayAngle += FOV / NUM_RAYS;
//     }
//     while(ray)
//     {
//         // printf("ray->distance = %f %f %f\n", ray->distance, ray->x_hit, ray->y_hit);
//         render_wall(data, ray, &column);
//         ray = ray->next;
//     }
//     // exit(0);
// }


void  castAllRay(t_data *data)
{
    double  rayAngle;
    t_ray   *ray = NULL;
    double column;
        
    column = 0;
    rayAngle = data->angle - (FOV / 2);
    while (column < NUM_RAYS)
    {
        ray = malloc(sizeof(t_ray));
        ray->rayAngle = rayAngle;
        oneRay(data, ray);
        render_wall(data, ray, column);
        column++;
        rayAngle += FOV / NUM_RAYS;
        free(ray);
    }
}


int get_image_texture(t_data *data, t_texture *tex)
{
    while (tex)
    {
        if (tex->identifier == 0)
            data->image[0].image = mlx_xpm_file_to_image(data->mlx, tex->Path, 
                                &data->image[0].whith, &data->image[0].height);
        if (tex->identifier == 1)
            data->image[1].image = mlx_xpm_file_to_image(data->mlx, tex->Path, 
                                &data->image[1].whith, &data->image[1].height);
        if (tex->identifier == 2)
            data->image[2].image = mlx_xpm_file_to_image(data->mlx, tex->Path, 
                        &data->image[2].whith, &data->image[2].height);
        if (tex->identifier == 3)
            data->image[3].image = mlx_xpm_file_to_image(data->mlx, tex->Path, &data->image[3].whith, &data->image[3].height);
        tex = tex->next;
    }
    if (data->image[0].image == NULL || data->image[1].image == NULL || data->image[2].image == NULL || data->image[3].image == NULL)
    {
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

int create_window(char **map, t_texture *tex)
{
    t_data data;
    int len = 0;
    
    data.p_y = 0;
    data.p_x = 0;
    data.angle = M_PI_2;
    while (map[len])
        len++;
    data.mlx = mlx_init();
    data.lenght = ft_strlen(map[0]);
    data.height = len;
    data.win = mlx_new_window(data.mlx, data.lenght*10 , data.height*10 , "hello");
    data.win_test = mlx_new_window(data.mlx, Scren_W, Scren_H, "test");
 
//****************************************
   data.tex = tex;
     if (get_image_texture(&data, tex))
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
    
    mlx_loop_hook(data.mlx, key_press, &data);
    mlx_loop(data.mlx);
    return (0);
}
