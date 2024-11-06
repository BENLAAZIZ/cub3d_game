/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_m2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:38:53 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/07 00:03:43 by hben-laz         ###   ########.fr       */
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

double get_v_distance(t_data *data, double rayAngle, double *v_hit_x, double *v_hit_y)
{
    double xintercept;
    double yintercept;
    double xstep;
    double ystep;
    double xtocheck;
    double ytocheck;
    double v_distance;
    double x = data->p_x;
    double y = data->p_y;
    double angle = rayAngle;
    // ====================

    // int foundVertWallHit = 0;
    *v_hit_x = 0;
    *v_hit_y = 0;
    int vertWallContent = 0;
    
    // ====================
    xintercept = floor(x / 50) * 50;
    if (data->isRayFacingRight)
        xintercept += 50;
    yintercept = y + (xintercept - x) * tan(angle);

    xstep = 50;
    if (data->isRayFacingLeft)
        xstep *= -1;
    
    ystep = 50 * tan(angle);

    if (data->isRayFacingUp && ystep > 0)
        ystep *= -1;
    if (data->isRayFacingDown && ystep < 0)
        ystep *= -1;
    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;
    
    while (nextVertTouchX >= 0 && nextVertTouchX <= data->lenght * 50 && nextVertTouchY >= 0 && nextVertTouchY <= data->height * 50)
    {
        if (data->isRayFacingLeft)
            xtocheck = nextVertTouchX - 1;
        else
           xtocheck = nextVertTouchX;
        ytocheck = nextVertTouchY;
        if (is_wall(data, ytocheck, xtocheck))
        {
            *v_hit_x = nextVertTouchX;
            *v_hit_y = nextVertTouchY;
            vertWallContent = data->all_map[(int)floor(ytocheck / 50)][(int)floor(xtocheck / 50)];

            // foundVertWallHit = 1;
            v_distance = sqrt(pow(x - xtocheck, 2) + pow(y - ytocheck, 2));
            return (v_distance);
        }
        nextVertTouchX += xstep;
        nextVertTouchY += ystep;
        
    }
    return (INT_MAX);
}


double get_h_distance(t_data *data, double rayAngle, double *h_hit_x, double *h_hit_y)
{
    double xintercept;
    double yintercept;
    double xstep;
    double ystep;
    double xtocheck;
    double ytocheck;
    double h_distance;
    double x = data->p_x;
    double y = data->p_y;
    double angle = rayAngle;

    // ====================
    
//  int foundHorzWallHit = 0;
    xintercept = 0;
    yintercept = 0;
    *h_hit_x = 0;
    *h_hit_y = 0;
// int horzWallContent = 0;

    // ====================

    yintercept = floor(y / 50) * 50;
    if (data->isRayFacingDown)
        yintercept += 50;
 
    xintercept = x + (yintercept - y) / tan(angle);

    ystep = 50;
    if (data->isRayFacingUp)
        ystep *= -1;
   
    xstep = 50 / tan(angle);
    if (data->isRayFacingLeft && xstep > 0)
        xstep *= -1;
        
    if (data->isRayFacingRight && xstep < 0)
        xstep *= -1;
    
    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;
    
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= data->lenght * 50 && nextHorzTouchY >= 0 && nextHorzTouchY <= data->height * 50)
    {
        xtocheck = nextHorzTouchX;
        if (data->isRayFacingUp)
            ytocheck = nextHorzTouchY - 1;
        else
            ytocheck = nextHorzTouchY;
        if (is_wall(data, ytocheck, xtocheck))
        {
            *h_hit_x = nextHorzTouchX;
            *h_hit_y = nextHorzTouchY;
            // horzWallContent = data->all_map[(int)floor(ytocheck / 50)][(int)floor(xtocheck / 50)];
            // foundHorzWallHit = 1;
            h_distance = sqrt(pow(x - xtocheck, 2) + pow(y - ytocheck, 2));
            return (h_distance);
        }
        nextHorzTouchX += xstep;
        nextHorzTouchY += ystep;
    }
    return (INT_MAX);
}



void ray(t_data *data, double rayAngle)
{
    double v_distance;
    double h_distance;
    double h_hit_x;
    double h_hit_y;
    double v_hit_x;
    double v_hit_y;
    

    v_distance = 0;
    h_distance = 0;
    v_hit_x = 0;
    v_hit_y = 0;
    h_hit_x = 0;
    h_hit_y = 0;

    data->isRayFacingDown = 0;
    data->isRayFacingUp = 0;
    data->isRayFacingRight = 0;
    data->isRayFacingLeft = 0;
    
    if (rayAngle > 2 * M_PI)
        rayAngle -= 2 * M_PI;
    if (rayAngle < 0)
        rayAngle += 2 * M_PI;

    if (rayAngle > 0 && rayAngle < M_PI)
        data->isRayFacingDown = 1;
    data->isRayFacingUp = !data->isRayFacingDown;

    if (rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI)
        data->isRayFacingRight = 1;
    data->isRayFacingLeft = !data->isRayFacingRight;

    
    v_distance = get_v_distance(data, rayAngle, &v_hit_x, &v_hit_y);
    h_distance = get_h_distance(data, rayAngle, &h_hit_x, &h_hit_y);
    if (v_distance <= h_distance)
    {
        int x = -3;
        int y = -3;
           while (y < 3)
        {
        x = -3;
        while (x < 3)
        {
        mlx_pixel_put(data->mlx, data->win, v_hit_x + x, v_hit_y + y, 0xF62108);
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
        mlx_pixel_put(data->mlx, data->win, h_hit_x + x, h_hit_y + y, 0xF62108);
            x++;
        }
        y++;
        }
    }
     printf("\n");
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

void  castAllRay(t_data *data)
{
    double rayAngle;
    double rayStep;
  

    // double FOV = 60 * (M_PI / 180);

    // rayAngle = data->angle;
    rayAngle = data->angle - (FOV / 2 );
    rayStep = ( 5 * M_PI / 180) / 50;
   
    rayAngle = normalize_angle(rayAngle);
    printf("************* rayAngle in castAllRay ***************\n");
    printf("rayAngle : %f\n", rayAngle);
    printf("***************************************************\n");
    // rayAngle = normalize_angle(rayStep - ((FOV) / 2));
    while (rayAngle < data->angle + (FOV / 2))
    {
        ray(data, rayAngle);
        rayAngle += rayStep;
    }
}

int create_window(char **map)
{
    t_data data;
    data.p_y = 0;
    data.p_x = 0;
    data.angle = M_PI / 2;
    
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
