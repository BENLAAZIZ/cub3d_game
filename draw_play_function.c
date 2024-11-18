void    drawplayer(t_data *data)
{
    double x = -2;
    double y = -2;
    // printf("p_x = %f, p_y = %f\n", data->p_x, data->p_y);
    // exit(0);

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


    double ray_y = data->p_y;
    double ray_x = data->p_x;
    // double angle = data->angle;
    double ray_step = 0.5;
    // double step_x = cos(angle - FOV / 2) * ray_step;
    // double step_y = sin(angle - FOV / 2) * ray_step;
    double z = 100;
    double rayAngle = data->angle - (FOV / 2);
    // if (rayAngle < 0)
    //     rayAngle += 2 * M_PI;
    // if (rayAngle > 2 * M_PI)
    //     rayAngle -= 2 * M_PI; 
    printf("angle = %f\n", data->angle);
    printf("data->angle - (FOV / 2) = %f\n", data->angle - (FOV / 2));
    printf("data->angle + (FOV / 2) = %f\n", data->angle + (FOV / 2));
    // exit(0);
    
    while (rayAngle < data->angle + (FOV / 2))
    {
        while (z)
        {
            if (is_wall(data, ray_y, ray_x))
                    break;
            mlx_pixel_put(data->mlx, data->win_test, ray_x, ray_y, 0x40ff00);
            ray_x += cos(rayAngle) * ray_step;;
            ray_y += sin(rayAngle) * ray_step;;
            z--;
        }
        printf(" ======== rayAngle = %f ========\n", rayAngle);
        z = 100;
        // ray_x += step_x;
        // ray_y += step_y;
        rayAngle += 0.005;
    }
    
    // ray_y = data->p_y;
    // ray_x = data->p_x;
    // step_x = cos(angle - (FOV / 2)) * ray_step;
    // step_y = sin(angle - (FOV / 2)) * ray_step;
    // z = 800;
    // while (z)
    // {
    //     if (is_wall(data, ray_y, ray_x))
    //             break;
    //     mlx_pixel_put(data->mlx, data->win_test, ray_x, ray_y, 0x40ff00);
    //     ray_x += step_x;
    //     ray_y += step_y;
    //     z--;
    // }
    //************************************************************************************************
    // ray_y = data->p_y;
    // ray_x = data->p_x;
    // step_x = cos(angle - (FOV / 2)) * ray_step;
    // step_y = sin(angle - (FOV / 2)) * ray_step;
    //************************************************************************************************

    // z = 800;
    // while (z)
    // {
    //     if (is_wall(data, ray_y, ray_x))
    //             break;
    //     mlx_pixel_put(data->mlx, data->win_test, ray_x, ray_y, 0x40ff00);
    //     ray_x += step_x;
    //     ray_y += step_y;
    //     z--;
    // }
    //************************************************************************************************
    // double rayAngle = angle - (FOV / 2);

    //   while (rayAngle < angle + (FOV / 2))
    // {
    //     while (z)
    //     {
    //         if (is_wall(data, ray_y, ray_x))
    //                 break;
    //         mlx_pixel_put(data->mlx, data->win_test, ray_x, ray_y, 0x40ff00);
    //         ray_x += cos(rayAngle) * ray_step;
    //         ray_y += sin(rayAngle) * ray_step;
    //         z--;
    //     }
        
    //         z = 800;
    //         ray_x += step_x;
    //         ray_y += step_y;
    //         rayAngle += 0.5;
        
        
    //     rayAngle += 0.5;
    // }
    
}