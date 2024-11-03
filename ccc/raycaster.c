/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:38:53 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/03 01:11:24 by hben-laz         ###   ########.fr       */
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



int is_wall(t_data *data, double y, double x)
{
    if (x < 0 || x > data->lenght * 50 || y < 0 || y > data->height * 50)
        return (1);
    if (data->all_map[(int)y / 50][(int)x / 50] == '1')
        return (1);
    return (0);
}

// int is_wall( t_data *data, double x, double y) // check the wall hit
// {
// 	int  x_m;
// 	int  y_m;

// 	if (x < 0 || y < 0)
// 		return (0);
// 	x_m = floor (x / 50); // get the x position in the map
// 	y_m = floor (y / 50); // get the y position in the map
// 	if ((y_m >= data->height || x_m >= data->lenght) || (y_m < 0 || x_m < 0))
// 		return (1);
// 	if (data->all_map[y_m] && x_m <= (int)strlen(data->all_map[y_m]))
// 		if (data->all_map[y_m][x_m] == '1')
// 			return (1);
// 	return (0);
// }

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
    double z = 400;
    while (z)
    {
        if (is_wall(data, ray_y, ray_x))
                break;
        mlx_pixel_put(data->mlx, data->win, ray_x, ray_y, 0x40ff00);
        ray_x -= step_x;
        ray_y -= step_y;
        z--;
    }
    ray_y = data->p_y;
    ray_x = data->p_x;
    step_x = cos(angle - (FOV / 2)) * ray_step;
    step_y = sin(angle - (FOV / 2)) * ray_step;
    z = 400;
    while (z)
    {
        if (is_wall(data, ray_y, ray_x))
                break;
        mlx_pixel_put(data->mlx, data->win, ray_x, ray_y, 0x40ff00);
        ray_x -= step_x;
        ray_y -= step_y;
        z--;
    }
    ray_y = data->p_y;
    ray_x = data->p_x;
    step_x = cos(angle + (FOV / 2)) * ray_step;
    step_y = sin(angle + (FOV / 2)) * ray_step;
    z = 400;
    while (z)
    {
        if (is_wall(data, ray_y, ray_x))
                break;
        mlx_pixel_put(data->mlx, data->win, ray_x, ray_y, 0x40ff00);
        ray_x -= step_x;
        ray_y -= step_y;
        z--;
    }
    
}

void    move_player_up(t_data *data)
{
    double x;
    double y;
    
    x = data->p_x + cos(data->angle) * 10.00;
    y = data->p_y - sin(data->angle) * 10.00;
    if (data->all_map[(int)y / 50][(int)x / 50] == '1')
        return ;
    data->p_y = y;
    data->p_x = x;
    mlx_clear_window(data->mlx, data->win);
    drawmap(data);
    drawplayer(data);
    castAllRay(data);
}

void    move_player_down(t_data *data)
{
    printf("cos : %f sin : %f\n", cos(data->angle) ,sin(data->angle));
    double y = data->p_y + sin(data->angle) * 10.00;
    double x = data->p_x + cos(data->angle) * 10.00;
    if (data->all_map[(int)y / 50][(int)x / 50] == '1')
        return ;
    data->p_y = y;
    data->p_x = x;
    mlx_clear_window(data->mlx, data->win);
    drawmap(data);
    drawplayer(data);
    castAllRay(data);
}

void    move_player_right(t_data *data)
{
    printf("cos : %f sin : %f\n", cos(data->angle + M_PI_2) ,sin(data->angle + M_PI_2));
    double y = data->p_y + sin(data->angle - M_PI_2) * 10.00;
    double x = data->p_x + cos(data->angle - M_PI_2) * 10.00;
    if (data->all_map[(int)y / 50][(int)x / 50] == '1')
        return ;
    data->p_y = y;
    data->p_x = x;
    mlx_clear_window(data->mlx, data->win);
    drawmap(data);
    drawplayer(data);
    castAllRay(data);
}
void    move_player_left(t_data *data)
{
    printf("cos : %f sin : %f\n", cos(data->angle - M_PI_2) ,sin(data->angle - M_PI_2));
    double y = data->p_y + sin(data->angle + M_PI_2) * 10.00;
    double x = data->p_x + cos(data->angle + M_PI_2) * 10.00;
    if (data->all_map[(int)y / 50][(int)x / 50] == '1')
        return ;
    data->p_y = y;
    data->p_x = x;
    mlx_clear_window(data->mlx, data->win);
    drawmap(data);
    drawplayer(data);
    castAllRay(data);
}

int    key_press(int keycode, t_data *data)
{
    if (keycode == 53)
        exit(0);
    if (keycode == 13)
        move_player_up(data);
    if (keycode == 1)
        move_player_down(data);
    if (keycode == 0)
        move_player_left(data);
    if (keycode == 2)
        move_player_right(data);
    if (keycode == 123)
    {
        puts("right");
        data->angle -= 0.1 * (M_PI / 180) * 50;
        printf("%f\n", data->angle);
        mlx_clear_window(data->mlx, data->win);
        drawmap(data);
        drawplayer(data);
        castAllRay(data);
    }
    if (keycode == 124)
    {
        puts("left");
        data->angle += 0.1 * (M_PI / 180) * 50;
        printf("%f\n", data->angle);
        mlx_clear_window(data->mlx, data->win);
    drawmap(data);
    drawplayer(data);
    castAllRay(data);
    }
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
    // data->p_x *= 50;
    // data->p_y *= 50;
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
  

    if (angle >= M_PI_2 && angle <= 3 * M_PI_2)
    {
        xintercept = floor(x / 50) * 50;
        xstep = -50;
    }
    else
    {
        xintercept = floor(x / 50) * 50 + 50;
        xstep = 50;
    }
    yintercept = x + (xintercept - x) * tan(angle);
    ystep = 50 * tan(angle);
    while (xintercept >= 0 && xintercept < data->lenght * 50 && yintercept >= 0 && yintercept < data->height * 50)
    {
        xtocheck = xintercept;
        ytocheck = yintercept;
        if (is_wall(data, ytocheck, xtocheck))
        {
            *v_hit_x = xtocheck;
            *v_hit_y = ytocheck;
            printf("vertical\n");
            printf("x : %f y : %f\n", xtocheck, ytocheck);
            v_distance = sqrt(pow(x - xtocheck, 2) + pow(y - ytocheck, 2));
            return (v_distance);
        }
        xintercept += xstep;
        yintercept += ystep;
        
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
 
    if (angle >= 0 && angle <= M_PI)
    {
        yintercept = floor(y / 50) * 50 - 0.0001;
        ystep = -50;
    }
    else
    {
        yintercept = floor(y / 50) * 50 + 50;
        ystep = 50;
    }
    xintercept = y + (yintercept - y) / tan(angle);
    xstep = 50 / tan(angle);
    while (xintercept >= 0 && xintercept < data->lenght * 50 && yintercept >= 0 && yintercept < data->height * 50)
    {
        xtocheck = xintercept;
        ytocheck = yintercept;
        if (is_wall(data, ytocheck, xtocheck))
        {
            *h_hit_x = xtocheck;
            *h_hit_y = ytocheck;
            printf("horizontal\n");
            printf("x : %f y : %f\n", xtocheck, ytocheck);
            h_distance = sqrt(pow(x - xtocheck, 2) + pow(y - ytocheck, 2));
            return (h_distance);
        }
        xintercept += xstep;
        yintercept += ystep;
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
    

   if (rayAngle > 2 * M_PI)
        rayAngle -= 2 * M_PI;
    if (rayAngle < 0)
        rayAngle += 2 * M_PI;
    
        
    v_distance = get_v_distance(data, rayAngle, &v_hit_x, &v_hit_y);
    h_distance = get_h_distance(data, rayAngle, &h_hit_x, &h_hit_y);
    printf("--------------------\n");
    printf("v_distance : %f\n", v_distance);
    printf("h_distance : %f\n", h_distance);
    if (v_distance <= h_distance)
    {
        mlx_pixel_put(data->mlx, data->win, v_hit_y, v_hit_x, 0xF62108);
    }
    else
    {
        mlx_pixel_put(data->mlx, data->win, h_hit_y, h_hit_x, 0xF62108);
    }
     printf("--------------------\n");
}

void  castAllRay(t_data *data)
{
    double rayAngle;
    double rayStep;
  

    // double FOV = 60 * (M_PI / 180);

    rayAngle = data->angle - (FOV / 2 );
    rayStep = ( 5 * M_PI / 180) / 50;
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
    // data.size_p = 30;
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
