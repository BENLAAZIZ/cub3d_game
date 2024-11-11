/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:38:53 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/11 16:51:25 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"




int is_wall(t_data *data, double y, double x)
{
    if (x <= 0 || x >= data->lenght * 50 || y <= 0 || y >= data->height * 50)
        return (1);
    if (data->all_map[(int)y / 50][(int)x / 50] == '1')
        return (1);
      
    return (0);
}

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
    data->p_x = (data->p_x * 50) + 25;
    data->p_y = (data->p_y * 50) + 25;
}

double get_v_intercept(t_data *data, t_ray *ray, double xstep, double ystep)
{
    double xintercept;
    double yintercept;
    double xtocheck;
    double ytocheck;
    double v_distance;
  
    xintercept = floor(data->p_x / 50) * 50;
    if (ray->lookingRight)
        xintercept += 50;
        
    yintercept = data->p_y + (xintercept - data->p_x) * tan(ray->rayAngle);
    xstep = 50;
    ystep = 50 * tan(ray->rayAngle);
    
    if (ray->lookingLeft)
        xstep *= -1;
    if (ray->lookingUp && ystep > 0)
        ystep *= -1;
    if (ray->lookingDown && ystep < 0)
        ystep *= -1;
    
    while (xintercept >= 0 && xintercept <= data->lenght * 50 && yintercept >= 0 && yintercept <= data->height * 50)
    {
        if (ray->lookingLeft)
            xtocheck = xintercept - 1;
        else
           xtocheck = xintercept;
        ytocheck = yintercept;
        if (is_wall(data, ytocheck, xtocheck))
        {
            ray->v_hit_x = xintercept;
            ray->v_hit_y = yintercept;
            v_distance = sqrt(pow(data->p_x - xtocheck, 2) + pow(data->p_y - ytocheck, 2));
            return (v_distance);
        }
        xintercept += xstep;
        yintercept += ystep;
    }
    return (INT_MAX);
}


double get_h_intercept(t_data *data, t_ray *ray, double xstep, double ystep)
{
    double xintercept;
    double yintercept;
    double xtocheck;
    double ytocheck;
    double h_distance;

    yintercept = floor(data->p_y / 50) * 50;
    if (ray->lookingDown)
        yintercept += 50;
    xintercept = data->p_x + (yintercept - data->p_y) / tan(ray->rayAngle);
    ystep = 50;
    xstep = 50 / tan(ray->rayAngle); 
    if (ray->lookingUp)
        ystep *= -1;
    if (ray->lookingLeft && xstep > 0)
        xstep *= -1;
    if (ray->lookingRight && xstep < 0)
        xstep *= -1;
    while (xintercept >= 0 && xintercept <= data->lenght * 50 && yintercept >= 0 && yintercept <= data->height * 50)
    {
        xtocheck = xintercept;
        if (ray->lookingUp)
            ytocheck = yintercept - 1;
        else
            ytocheck = yintercept;
        if (is_wall(data, ytocheck, xtocheck))
        {
            ray->h_hit_x = xintercept;
            ray->h_hit_y = yintercept;
            h_distance = sqrt(pow(data->p_x - xtocheck, 2) + pow(data->p_y - ytocheck, 2));
            return (h_distance);
        }
        xintercept += xstep;
        yintercept += ystep;
    }
    return (INT_MAX);
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
        
        int x = -2;
        int y = -2;
        while (y < 2)
        {
            x = -2;
            while (x < 2)
            {
                mlx_pixel_put(data->mlx, data->win, ray->v_hit_x + x, ray->v_hit_y + y, 0xF62108);
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
         int x = -2;
        int y = -2;
           while (y < 2)
        {
        x = -2;
        while (x < 2)
        {
        mlx_pixel_put(data->mlx, data->win, ray->h_hit_x + x, ray->h_hit_y + y, 0xF62108);
            x++;
        }
        y++;
        }
    }
}

void render_wall(t_data *data, t_ray *ray, double *column)
{
     ray->distance *= cos(ray->rayAngle - data->angle);
        draw_wall(data, ray->distance  , *column);
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
        render_wall(data, ray, &column);
        rayAngle += rayStep;
        free(ray);
    }
}

int create_window(char **map)
{
    t_data data;
    int len = 0;
    
    data.p_y = 0;
    data.p_x = 0;
    data.angle = M_PI_2;
    while (map[len])
        len++;
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, (ft_strlen(map[0]) * 50), len * 50, "hello");
    data.win_test = mlx_new_window(data.mlx, ((ft_strlen(map[0]) - 1) * 100), len * 50, "test");

//****************************************

    data.image = mlx_xpm_file_to_image(data.mlx, "monaliza_xpm.xpm", &data.lenght, &data.height);
    if (!data.image)
    {
        printf("Failed to load texture\n");
        return (1);
    }

    // Get the address of the pixel array within the image
    // data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

//*******************************************
    
    data.all_map = map;
    data.height = len;
    get_player_position(&data);
    data.lenght = ft_strlen(map[0]);
    drawmap(&data);
    drawplayer(&data);
    castAllRay(&data);
    mlx_hook(data.win, 2, 0, key_press, &data);
    mlx_loop(data.mlx);
    return (0);
}
