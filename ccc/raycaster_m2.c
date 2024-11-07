/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_m2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:38:53 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/07 15:34:15 by hben-laz         ###   ########.fr       */
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

double get_v_distance(t_data *data, t_ray *ray, double xstep, double ystep)
{
    double xintercept;
    double yintercept;
    double xtocheck;
    double ytocheck;
    double v_distance;
  
    // ====================
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
            // foundVertWallHit = 1;
            v_distance = sqrt(pow(data->p_x - xtocheck, 2) + pow(data->p_y - ytocheck, 2));
            return (v_distance);
        }
        xintercept += xstep;
        yintercept += ystep;
    }
    return (INT_MAX);
}


double get_h_distance(t_data *data, t_ray *ray, double xstep, double ystep)
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

void ray_function(t_data *data, double rayAngle)
{   
    t_ray *ray;

    ray = malloc(sizeof(t_ray));
    ray->rayAngle = rayAngle;
    init_ray(ray);
    if (ray->rayAngle > 2 * M_PI)
        ray->rayAngle -= 2 * M_PI;
    if (ray->rayAngle < 0)
        ray->rayAngle += 2 * M_PI;
        
    if (ray->rayAngle > 0 && ray->rayAngle < M_PI)
        ray->lookingDown = 1;
    ray->lookingUp = !ray->lookingDown;
    if (ray->rayAngle < 0.5 * M_PI || ray->rayAngle > 1.5 * M_PI)
        ray->lookingRight = 1;
    ray->lookingLeft = !ray->lookingRight;

    
    ray->v_distance = get_v_distance(data, ray, 0, 0);
    ray->h_distance = get_h_distance(data, ray, 0, 0);
    if (ray->v_distance <= ray->h_distance)
    {
        int x = -3;
        int y = -3;
           while (y < 3)
        {
        x = -3;
        while (x < 3)
        {
        mlx_pixel_put(data->mlx, data->win, ray->v_hit_x + x, ray->v_hit_y + y, 0xF62108);
            x++;
        }
        y++;
        }
    }
    else
    {
         int x = -3;
        int y = -3;
           while (y < 3)
        {
        x = -3;
        while (x < 3)
        {
        mlx_pixel_put(data->mlx, data->win, ray->h_hit_x + x, ray->h_hit_y + y, 0xF62108);
            x++;
        }
        y++;
        }
    }
     printf("\n");
    free(ray);
}

float	normalize_angle(float angle)
{
	float degree_angle;

	degree_angle = (angle * 360) / (2 * M_PI);
	degree_angle = (int)degree_angle % (360);
	if (degree_angle < 0)
		degree_angle = degree_angle + (360);
	return (RAD(degree_angle));
}

// float ft_remainder(float x, float y) {
//     // Calculate the quotient and round it towards zero
//     int quotient = (int)(x / y);

//     // Calculate the remainder
//     float rem = x - (quotient * y);

//     // Adjust remainder to be within the correct range
//     if (rem > y / 2) rem -= y;
//     else if (rem < -y / 2) rem += y;

//     return rem;
// }

// float normalize_angle(float angle)
// {
//     angle = ft_remainder(angle, 2 * M_PI);
//     if (angle < 0)
//         angle = (2 * M_PI) + angle;
//     return (angle);
// }

void  castAllRay(t_data *data)
{
    double rayAngle;
    double rayStep;
    

    // double FOV = 60 * (M_PI / 180);
    // ray->rayAngle = data->angle;
    // ray = malloc(sizeof(t_ray));
    rayAngle = data->angle - (FOV / 2 );
    rayStep = ( 5 * M_PI / 180) / 50;
   
    printf("ray->rayAngle : %f\n", rayAngle);
    rayAngle = normalize_angle(rayAngle);
    printf("************* rayAngle in castAllRay ***************\n");
    printf("rayAngle : %f\n", rayAngle);
    printf("data->angle : %f\n", data->angle);
    printf("data->angle + (FOV / 2) : %f\n", data->angle + (FOV / 2));
    printf("***************************************************\n");
    // rayAngle = normalize_angle(rayStep - ((FOV) / 2));
    while (rayAngle <= data->angle + (FOV / 2))
    {
        printf ("in while\n");
        ray_function(data, rayAngle);
        rayAngle += rayStep;
    }
}

int create_window(char **map)
{
    t_data data;
    data.p_y = 0;
    data.p_x = 0;
    // data.angle = M_PI;
    data.angle = 0.00;
    
    int len = 0;
    while (map[len])
        len++;
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, (ft_strlen(map[0]) * 50), len * 50, "hello");
    data.all_map = map;
    data.height = len;
    get_player_position(&data);
    printf("p_x : %d p_y : %d\n", data.p_x, data.p_y);
    data.lenght = ft_strlen(map[0]);
    drawmap(&data);
    drawplayer(&data);
    castAllRay(&data);
    mlx_hook(data.win, 2, 0, key_press, &data);
    mlx_loop(data.mlx);
    return (0);
}
