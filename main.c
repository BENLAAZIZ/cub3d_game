#include "cub3d.h"

int get_image_texture(t_data *data, t_texture *tex)
{
	int i;
	
	i  =  0;
    while (tex)
    {
		printf("tex->identifier = %d\n", tex->identifier);
		if (i == 4)
			return (0);
        if (tex->identifier == i)
		{
			data->image[i].texture = mlx_load_png(tex->Path);
			data->image[i].image = mlx_texture_to_image(data->mlx, data->image[i].texture);
		}
		i++;
        tex = tex->next;
    }
	i = 0;
	while (i < 4)
	{
		if (data->image[i].image == NULL || data->image[i].texture == NULL)
			return (1);
		i++;
	}

    return (0); 
}

// int get_image_texture(t_data *data, t_texture *tex)
// {
//     while (tex)
//     {
//         if (tex->identifier == 0)
// 		{
// 			data->image[0].texture = mlx_load_png(tex->Path);
// 			data->image[0].image = mlx_texture_to_image(data->mlx, data->image[0].texture);
// 		}
//         if (tex->identifier == 1)
// 	    {
// 			data->image[1].texture = mlx_load_png(tex->Path);
// 			data->image[1].image = mlx_texture_to_image(data->mlx, data->image[1].texture);
// 		}
//         if (tex->identifier == 2)
//         {
// 			data->image[2].texture = mlx_load_png(tex->Path);
// 			data->image[2].image = mlx_texture_to_image(data->mlx, data->image[2].texture);
// 		}
//         if (tex->identifier == 3)
//         {
// 			data->image[3].texture = mlx_load_png(tex->Path);
// 			data->image[3].image = mlx_texture_to_image(data->mlx, data->image[3].texture);
// 		}
//         tex = tex->next;
//     }
//     if (data->image[0].image == NULL || data->image[1].image == NULL || data->image[2].image == NULL || data->image[3].image == NULL)
//     {
//             return (1);
//     }

//     return (0); 
// }

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int player_direction(char c, t_data *data)
{
	if (c == 'N')
	{
		data->angle = 3 * M_PI_2;
		return (1);
	}
	if (c == 'S')
	{
		data->angle = M_PI_2;
		return (1);
	}
	if (c == 'E')
	{
		data->angle = 0;
		return (1);
	}
	if (c == 'W')
	{
		data->angle = M_PI;
		return (1);
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
            // if (data->all_map[(int)data->p_y][(int)data->p_x] == 'N' 
			// 	|| data->all_map[(int)data->p_y][(int)data->p_x] == 'S' 
			// 	|| data->all_map[(int)data->p_y][(int)data->p_x] == 'E' 
			// 	|| data->all_map[(int)data->p_y][(int)data->p_x] == 'W')
            //     break;
			if (player_direction(data->all_map[(int)data->p_y][(int)data->p_x], data))
				break;
            data->p_x++;
        }
        // if (data->all_map[(int)data->p_y][(int)data->p_x] == 'N' 
		// 	|| data->all_map[(int)data->p_y][(int)data->p_x] == 'S' 
		// 	|| data->all_map[(int)data->p_y][(int)data->p_x] == 'E' 
		// 	|| data->all_map[(int)data->p_y][(int)data->p_x] == 'W')
        //     break;
		if (player_direction(data->all_map[(int)data->p_y][(int)data->p_x], data))
				break;
        data->p_y++;
    }
    data->p_x = (data->p_x * TILE_SIZE) + (TILE_SIZE / 2);
    data->p_y = (data->p_y * TILE_SIZE) + (TILE_SIZE / 2);
}

int is_wall(t_data *data, double y, double x)
{
    if (x <= 0 || x >= data->lenght * TILE_SIZE || y <= 0 || y >= data->height * TILE_SIZE)
        return (1);
    if (data->all_map[(int)y / (int)TILE_SIZE][(int)x / (int)TILE_SIZE] == '1')
        return (1);
      
    return (0);
}

// int point_image_texture(t_data *data, t_ray *ray, t_image **img)
// {

//     if (!ray->flag && !(ray->rayAngle > 0 && ray->rayAngle < M_PI))
//     {
//         *img = &data->image[0];
//     }
//     else if (!ray->flag && ray->rayAngle >= 0 && ray->rayAngle <= M_PI)
//     {
//         *img = &data->image[1];
//     }
//     else if (ray->flag && ray->rayAngle >= M_PI_2 && ray->rayAngle <= 3 * M_PI_2)
//     {
//         *img = &data->image[2];
//     }
//     else
//     {
//         *img = &data->image[3];
//     }
//    if (*img == NULL)
//             return (1);
//     // exit(0);
//     return (0);
// }



void render_wall(t_data *data, t_ray *ray, double column)
{
     ray->distance *= cos(ray->rayAngle - data->angle);
     ray->distance = ray->distance * 5;
     draw_wall(data, ray  , column);
     draw_floor(data, ray->distance , column);
}

void ft_hook(void* param)
{
	t_data *data = (t_data*)param;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player_up(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player_down(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player_left(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player_right(data);
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT) || mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
        player_rot(data);

}

void clear_texture(t_texture *tex)
{
	t_texture *tmp;
	while (tex)
	{
		tmp = tex;
		tex = tex->next;
		free(tmp->Path);
		free(tmp);
	}
}


int ft_init(t_data *data, t_texture *textures, char **map)
{
	int height;	
	if (map == NULL)
		return 1;
	height = 0;
	while(map[height])
		height++;
	data->height = height;
	data->all_map = map;
	data->tex = textures;
	data->lenght = ft_strlen(map[0]);
	data->mlx = mlx_init(Screen_W, Screen_H, "Cub3D", 1);
	data->img = mlx_new_image(data->mlx, Screen_W, Screen_H);
    if (get_image_texture(data, textures))
		return (ft_putstr_fd("Error in get_image_texture", 2), 1);
	clear_texture(data->tex);
    get_player_position(data);
    castAllRay(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	return (0);
}



int main (int argc, char **argv)
{
	t_texture	*textures;
	char 		**map;
	t_data		data;

	map = NULL;
	textures = NULL;
	if (argc != 2)
		return (ft_putstr_fd("Invalid number of arguments", 2), 1);
	if (ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub") != 0)
		return (ft_putstr_fd("Invalid file extension", 2), 1);
	map = pars_map(argv[1], &textures, map);

	// **************************	
	if (TILE_SIZE < 1)
		return (ft_putstr_fd("Invalid TILE_SIZE", 2), 1);
	if (TILE_SIZE * ft_strlen(map[0]) > Screen_W)
		return (ft_putstr_fd("Invalid Screen size", 2), 1);
	if (Screen_W < 1 || Screen_H < 1 || Screen_W > 2560 || Screen_H > 1440)
		return (ft_putstr_fd("Invalid Screen size", 2), 1);
	// **************************

	ft_init(&data, textures, map);
}
