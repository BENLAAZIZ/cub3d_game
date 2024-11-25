#include "cub3d_bonus.h"


int ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}


// int is_wall(t_data *data, double y, double x)
// {
//     if (x <= 0 || x >= data->lenght * TILE_SIZE || y <= 0 || y >= data->height * TILE_SIZE)
//         return (1);
//     if (data->all_map[(int)y / (int)TILE_SIZE][(int)x / (int)TILE_SIZE] == '1')
//         return (1);
      
//     return (0);
// }


void ft_hook(void* param)
{
	t_data *data = (t_data*)param;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		delete_texture(data);
		free_double(data->all_map);
		lst_clear(&data->tex);
		mlx_close_window(data->mlx);
	}
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

int ft_init(t_data *data, t_texture *textures, char **map)
{
	int height;	

	height = 0;
	while(map[height])
		height++;
	data->height = height;
	data->all_map = map;
	data->lenght = ft_strlen(map[0]);
	data->mlx = mlx_init(Screen_W, Screen_H, "Cub3D", 1);
	if (data->mlx == NULL)
		return (ft_putstr_fd("Error in mlx_init", 2), 1);
	data->tex = textures;
	data->img = mlx_new_image(data->mlx, Screen_W, Screen_H);
	if (data->img == NULL)
	{
		mlx_terminate(data->mlx);
		return (ft_putstr_fd("Error in mlx_new_image", 2), 1);
	}

	return (0);
}

int ft_game(t_data *data, t_texture *textures, char **map)
{
	if (map == NULL)
		return 1;
	if (ft_init(data, textures, map))
		return (1);
    if (get_image_texture(data, textures, 0))
	{
		mlx_terminate(data->mlx);
		return (ft_putstr_fd("Error in get_image_texture", 2), 1);
	}
    get_player_position(data);
    if (castAllRay(data))
		return (1);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	return (0);
}

void f()
{
	system("leaks cub3d");
}

int main (int argc, char **argv)
{
	t_texture	*textures;
	char 		**map;
	t_data		data;

// atexit(f);
	map = NULL;
	textures = NULL;
	if (argc != 2)
		return (ft_putstr_fd("Invalid number of arguments", 2), 1);
	if (ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub") != 0)
		return (ft_putstr_fd("Invalid file extension", 2), 1);
	map = pars_map(argv[1], &textures, map);
	if (map == NULL)
		return (1);
	if (Screen_W < 1 || Screen_H < 1 || Screen_W > 2560 || Screen_H > 1440 || TILE_SIZE < 1 || TILE_SIZE > 100)
	{
		free_double(map);
		lst_clear(&textures);
		return (ft_putstr_fd("Invalid Screen size", 2), 1);
	}
	if (ft_game(&data, textures, map) == 1)
	{
		free_double(map);
		lst_clear(&textures);
		return (1);
	}
}

