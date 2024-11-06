/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:38:53 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/06 15:05:54 by hben-laz         ###   ########.fr       */
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
  
        
    // ************************************************************ 
    // if (angle > M_PI_2 && angle < 3 * M_PI_2)
    // {
    //     xintercept = floor(x / 50) * 50;
    //     xstep = -50;
    // }
    // else
    // {
    //     xintercept = floor(x / 50) * 50 + 50;
    //     xstep = 50;
    // }
    // yintercept = x + (xintercept - x) * tan(angle);
    // ystep = 50 * tan(angle);
    // ************************************************************
    // if (angle == M_PI_2 || angle == 3 * M_PI_2)
    // {
    //     return (INT_MAX);
    // }
    
    xintercept = floor(x / 50) * 50;
     ystep = 50 * tan(angle);
     
    if (angle >= M_PI_2 && angle <= 3 * M_PI_2)
    {
        xstep = 50;
    }
    else
    {
        xstep = -50;
    }
    yintercept = x + (xintercept - x) * tan(angle);
    if (angle > 0 && angle < M_PI)
    {
        ystep *= -1;
    }
   

    while (xintercept >= 0 && xintercept < data->lenght * 50 && yintercept >= 0 && yintercept < data->height * 50)
    {
        xtocheck = xintercept;
        ytocheck = yintercept;
        if (is_wall(data, ytocheck, xtocheck))
        {
            *v_hit_x = xtocheck;
            *v_hit_y = ytocheck;
            // printf("vertical\n");
            // printf("x : %f y : %f\n", xtocheck, ytocheck);
            v_distance = sqrt(pow(x - xtocheck, 2) + pow(y - ytocheck, 2));
               printf ("======== v ============\n\n\n");
                printf("rayAngle : %f\n", rayAngle);
                printf("x_p : %d y_p : %d\n", data->p_x, data->p_y);
                printf("vertical in function\n");
                printf("v_hit_x : %f v_hit_y : %f\n", *v_hit_x, *v_hit_y);
            
                printf ("=========f v===========\n");
            return (v_distance);
        }
        if (angle == M_PI_2 || angle == 3 * M_PI_2)
            xintercept = x;
        else
            xintercept += xstep;
        if (angle == 0 || angle == M_PI)
            yintercept = y;
        else    
            yintercept += ystep;
        
    }
    return (INT_MAX);
}


// int horz_incriment(t_data *data, double *xintercept, double *yintercept, double xstep, double ystep)
// {
//     if (xstep > 0)
//     {
//         *xintercept = floor(*xintercept / 50) * 50 + 50;
//     }
//     else
//     {
//         *xintercept = floor(*xintercept / 50) * 50 - 0.0001;
//     }
//     *yintercept = *yintercept + (*xintercept - *xintercept) * tan(0);
//     if (xstep > 0)
//         ystep *= -1;
//     if (is_wall(data, *yintercept, *xintercept))
//         return (1);
//     return (0);
// }

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
    // int k = 0;
 
 //************************************************************
    // if (angle > 0 && angle < M_PI)
    // {
    //     yintercept = floor(y / 50) * 50 - 0.0001;
    //     ystep = -50;
    // }
    // else
    // {
    //     yintercept = floor(y / 50) * 50 + 50;
    //     ystep = 50;
    // }
    // xintercept = y + (yintercept - y) / tan(angle);
    // xstep = 50 / tan(angle);
//****************************************************************

// -----------------------------------  2nd method  -----------------------------------



    // if (data->ray_looking_down)
	// 	yintercept += 50;
	// else
	// 	k = 1;
    //  ystep = 50;
    //  xintercept = y + (yintercept - y) / tan(angle);
    
    // if (!data->ray_looking_down)
	// 	ystep *= -1;

    //   xstep = 50 / tan(angle);
    
    
        

// -----------------------------------  end  method  -----------------------------------

    // if (angle == 0 || angle == M_PI)
    // {
    //     return (INT_MAX);
    // }
    
    
   yintercept = floor(y / 50) * 50;
  
   xstep = 50 / tan(angle);

   if (!(angle >= 0 && angle <= M_PI))
    {
        ystep = +50;
    }
    else
    {
        ystep = -50;
    }
    xintercept = y + (yintercept - y) / tan(angle);

    if (!(angle >= M_PI_2 && angle <= 3 * M_PI_2))
    {
       xstep *= -1;
    }
    
    while (xintercept >= 0 && xintercept <= data->lenght * 50 && yintercept >= 0 && yintercept <= data->height * 50)
    {
        xtocheck = xintercept;
        ytocheck = yintercept;
        if (is_wall(data, ytocheck, xtocheck))
        {
            *h_hit_x = xtocheck;
            *h_hit_y = ytocheck;
         printf ("======= h with wall =============\n\n\n");
                printf("rayAngle : %f\n", rayAngle);
                printf("x_p : %d y_p : %d\n", data->p_x, data->p_y);
                printf("horizontal in function\n");
                printf("h_hit_x : %f h_hit_y : %f\n", *h_hit_x, *h_hit_y);
            
                printf ("========= f h===========\n");
            h_distance = sqrt(pow(x - xtocheck, 2) + pow(y - ytocheck, 2));
            return (h_distance);
        }
         if (angle == M_2_PI || angle == 3 * M_PI_2)
             xintercept = x;
         else 
             xintercept += xstep;
        if (angle == 0 || angle == M_PI)
            yintercept = y;
        else
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
    // rayAngle = data->angle - (FOV / 2 );
    rayStep = ( 5 * M_PI / 180) / 50;
   
    rayAngle = normalize_angle(data->angle);
    printf("************* rayAngle in castAllRay ***************\n");
    printf("rayAngle : %f\n", rayAngle);
    printf("***************************************************\n");
    // rayAngle = normalize_angle(rayStep - ((FOV) / 2));
    // while (rayAngle < data->angle + (FOV / 2))
    // {

        ray(data, rayAngle);
    //     rayAngle += rayStep;
    // }

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
