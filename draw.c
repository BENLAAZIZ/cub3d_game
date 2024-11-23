#include "cub3d.h"

int get_texture_pixel_color(t_data *data, int texture_x, int texture_y, t_image *img)
{
    int color;
    (void)data;
    if (texture_x < 0 || texture_x > img->width || texture_y < 0 || texture_y > img->height)
    {
        printf("Invalid texture coordinates: x=%d, y=%d\n", texture_x, texture_y);
        return 0;
    }

    color = img->addr[((int)(texture_y * img->height + texture_x))];
    return (color);
}

int point_image_texture(t_data *data, t_ray *ray)
{

    if (!ray->flag && !(ray->rayAngle > 0 && ray->rayAngle < M_PI))
        data->imgx = &data->image[0];
    else if (!ray->flag && ray->rayAngle >= 0 && ray->rayAngle <= M_PI)
        data->imgx = &data->image[1];
    else if (ray->flag && ray->rayAngle >= M_PI_2 && ray->rayAngle <= 3 * M_PI_2)
        data->imgx = &data->image[2];
    else
        data->imgx = &data->image[3];
    if (data->imgx == NULL)
            return (1);
    return (0);
}


void draw_wall(t_data *data, t_ray *ray, int column)
{
    double line_height;
    double top_y, bottom_y;
    int color;
    int ofsset_x;
    int offset_y;
    double y;

    line_height = (Screen_H / ray->distance) * 5;
    top_y = Screen_H / 2 - line_height / 2;
    bottom_y = Screen_H / 2 + line_height / 2;


    if (point_image_texture(data, ray))
    {
        printf("Failed to load texture\n");
        return;
    }

     if (ray->flag == 1)
    {
        ofsset_x = (int)((ray->v_hit_y / TILE_SIZE) * data->imgx->texture->width) % data->imgx->texture->width;
        // ofsset_x = 
    }
    else
    {
        ofsset_x = (int)((ray->h_hit_x / TILE_SIZE) * data->imgx->texture->width) % data->imgx->texture->width;
    }


    // if (ray->flag == 1)
    // {
    //     ofsset_x = (int)((ray->v_hit_y / TILE_SIZE) * data->image[0].texture->width) % data->image[0].texture->width;
    //     // ofsset_x = 
    // }
    // else
    // {
    //     ofsset_x = (int)((ray->h_hit_x / TILE_SIZE) * data->image[0].texture->width) % data->image[0].texture->width;
    // }



    y = top_y;
    while (y < bottom_y)
    {
        if (y < 0)
            y = 0;
        if (y >= Screen_H)
            break;
        int distance = (y + line_height / 2) - (Screen_H / 2);
        // offset_y = distance * (data->image[0].texture->height / line_height);
        offset_y = distance * (data->imgx->texture->height / line_height);




        // unsigned int* pixel=  (unsigned int *)data->image[0].texture->pixels;
        unsigned int* pixel=  (unsigned int *)data->imgx->texture->pixels;

        color = pixel[(offset_y * data->imgx->texture->width) + ofsset_x];
        // color = pixel[(offset_y * data->image[0].texture->width) + ofsset_x];
        color = ft_pixel(color >> 16, color >> 8, color, 255);
        mlx_put_pixel(data->img, column, y, color);
        y++;
    }  
}
void draw_floor(t_data *data, double distance, double column)
{
	double line_height;
   	double top_y;
   	double bottom_y;
	double window_height = Screen_H;
    line_height = (window_height / distance) * 5;
    top_y = window_height / 2 - line_height / 2;
    bottom_y = top_y + line_height;

	int i = bottom_y;
	while(i < window_height)
	{
        mlx_put_pixel(data->img, column, i, ft_pixel(98, 149, 132, 255));
		i++;
	}
	i = 0;
	while (i < top_y)
	{
        mlx_put_pixel(data->img, column, i, ft_pixel(36, 54, 66, 255));
		i++;
	}
}

void    drawplayer(t_data *data)
{
    t_player    player;
    double      x;
    double      y;

    x = -2;
    y = -2;
    player.ray_y = data->p_y / TILE_SIZE;
    player.ray_x = data->p_x / TILE_SIZE;
    player.step_x = cos(data->angle - (FOV / 2)) * player.ray_step;
    player.step_y = sin(data->angle - (FOV / 2)) * player.ray_step;
    player.ray_step = 0.5;
    player.z = 100;
    draw_rays_minimap(data, &player); 
    while (y < 2)
    {
        x = -2;
        while (x < 2)
        {
			mlx_put_pixel(data->img, data->p_x + x, data->p_y + y, ft_pixel(0, 0, 255, 255));
            x++;
        }
        y++;
    }
}

void    draw_rays_minimap(t_data *data, t_player *player)
{
     double rayAngle;

    rayAngle = data->angle - (FOV / 2);
    while (rayAngle < data->angle + (FOV / 2))
    {
        while (player->z)
        {
            if (is_wall(data, player->ray_y, player->ray_x))
                    break;
			mlx_put_pixel(data->img, player->ray_x, player->ray_y, ft_pixel(0, 255, 0, 255));
            player->ray_x += player->step_x;
            player->ray_y += player->step_y;
            player->z--;
        }
        player->ray_y = data->p_y;
        player->ray_x = data->p_x;
        rayAngle += 0.01;
        player->step_x = cos(rayAngle) * player->ray_step;
        player->step_y = sin(rayAngle) * player->ray_step;
        player->z = 100;
    }
    
}
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
                while (y < TILE_SIZE)
                {
                    x = 1;
                    while (x < TILE_SIZE)
                    {
						mlx_put_pixel(data->img, (j * TILE_SIZE) + y, (i * TILE_SIZE) + x, ft_pixel(255, 255, 255, 255));
                        x++;
                    }
                    y++;
                }
            }
            else if (data->all_map[i][j] == '0' || data->all_map[i][j] == 'N' || data->all_map[i][j] == 'S' || data->all_map[i][j] == 'E' || data->all_map[i][j] == 'W')
            {
                int y = 0;
                int x = 0;
                while (y < TILE_SIZE)
                {
                    x = 0;
                    while (x < TILE_SIZE)
                    {
						mlx_put_pixel(data->img, (j * TILE_SIZE) + y, (i * TILE_SIZE) + x, ft_pixel(0, 0, 0, 255));
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