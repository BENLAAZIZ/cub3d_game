/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:55:54 by aaaraba           #+#    #+#             */
/*   Updated: 2024/12/01 12:40:46 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_mouse(t_data *data)
{
	mlx_get_mouse_pos(data->mlx, &data->mouse_x, &data->mouse_y);
	if (data->mouse_x < SCREEN_W / 2 && data->mouse_x > 0)
	{
		(data->angle -= 0.07)
			&& (cast_rays(data));
	}
	if (data->mouse_x > SCREEN_W / 2 && data->mouse_x < SCREEN_W)
	{
		(data->angle += 0.07)
			&& (cast_rays(data));
	}
	if (data->angle > 2 * M_PI)
		data->angle -= 2 * M_PI;
	if (data->angle < 0)
		data->angle += 2 * M_PI;
}

void	ft_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_mouse(data);
	mlx_set_mouse_pos(data->mlx, SCREEN_W / 2, SCREEN_H / 2);
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
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		player_rot(data);
}

int	ft_init(t_data *data, t_texture *textures, char **map, int i)
{
	if (T_S > 50)
		data->speed = 40;
	data->lenght = ft_strlen(map[0]);
	if (check_image_texture(data, textures, 0))
		return (ft_putstr_fd("Error in check_image_texture", 2), 1);
	data->mlx = mlx_init(SCREEN_W, SCREEN_H, "Cub3D", 1);
	if (data->mlx == NULL)
		return (ft_putstr_fd("Error in mlx_init", 2), 1);
	data->tex = textures;
	if (get_image_texture(data, textures, 0))
	{
		i = -1;
		while (data->image[++i].texture)
			mlx_delete_texture(data->image[i].texture);
		mlx_terminate(data->mlx);
		return (ft_putstr_fd("Error in get_image_texture", 2), 1);
	}
	data->img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
	if (data->img == NULL)
	{
		mlx_terminate(data->mlx);
		return (ft_putstr_fd("Error in mlx_new_image", 2), 1);
	}
	return (0);
}

int	ft_game(t_data *data, t_texture *textures, char **map, int i)
{
	int	height;	

	height = 0;
	while (map[height])
		height++;
	data->height = height;
	data->all_map = map;
	data->speed = 10;
	if (map == NULL || ft_init(data, textures, map, i))
		return (1);
	get_player_position(data);
	if (cast_rays(data))
		return (1);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_set_mouse_pos(data->mlx, SCREEN_W / 2, SCREEN_H / 2);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	(lst_clear(&textures), free_double(map));
	i = -1;
	while (++i < 4)
		mlx_delete_texture(data->image[i].texture);
	mlx_terminate(data->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_texture	*textures;
	t_data		data;
	char		**map;

	map = NULL;
	textures = NULL;
	if (argc != 2)
		return (ft_putstr_fd("Invalid number of arguments", 2), 1);
	if (ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub") != 0)
		return (ft_putstr_fd("Invalid file extension", 2), 1);
	map = pars_map(argv[1], &textures, map);
	if (map == NULL)
		return (1);
	if ((SCREEN_W < 600 || SCREEN_W > 2560)
		|| (SCREEN_H < 600 || SCREEN_H > 1440)
		|| T_S < 1 || T_S > 100)
	{
		(free_double(map), lst_clear(&textures));
		return (ft_putstr_fd("Invalid Screen size", 2), 1);
	}
	if (ft_game(&data, textures, map, 0) == 1)
		return (free_double(map), lst_clear(&textures), 1);
}
