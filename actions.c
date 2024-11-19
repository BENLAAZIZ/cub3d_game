/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:47:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/19 23:31:57 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"


void	move_player_down(t_data *data)
{
	double x;
	double y;
	
	x = data->p_x - cos(data->angle) * 5.00;
	y = data->p_y - sin(data->angle) * 5.00;
	if (data->all_map[(int)(y / TILE_SIZE)][(int)x / (int)TILE_SIZE] == '1')
		return ;
	data->p_y = y;
	data->p_x = x;
	// mlx_clear_window(data->mlx, data->win);
	mlx_clear_window(data->mlx, data->win_test);
	// drawmap(data);
	// drawplayer(data);
	castAllRay(data);
}

void	move_player_up(t_data *data)
{
	double y = data->p_y + sin(data->angle) * 5.00;
	double x = data->p_x + cos(data->angle) * 5.00;
	if(data->all_map[(int)(y / TILE_SIZE)][(int)x / (int)TILE_SIZE] == '1')
		return ;
	data->p_y = y;
	data->p_x = x;
	// mlx_clear_window(data->mlx, data->win);
	mlx_clear_window(data->mlx, data->win_test);
	// drawmap(data);
	// drawplayer(data); 
	castAllRay(data);
}

void	move_player_left(t_data *data)
{ 
	double y = data->p_y + sin(data->angle - M_PI_2) * 10.00;
	double x = data->p_x + cos(data->angle - M_PI_2) * 10.00;
	if (data->all_map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
		return ;
	data->p_y = y;
	data->p_x = x;
	// mlx_clear_window(data->mlx, data->win);
	mlx_clear_window(data->mlx, data->win_test);
	// drawmap(data);
	// drawplayer(data);
	castAllRay(data);
}

void	move_player_right(t_data *data)
{
	double y = data->p_y + sin(data->angle + M_PI_2) * 10.00;
	double x = data->p_x + cos(data->angle + M_PI_2) * 10.00;
	if (data->all_map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
		return ;
	data->p_y = y;
	data->p_x = x;
	// mlx_clear_window(data->mlx, data->win);
	mlx_clear_window(data->mlx, data->win_test);
	// drawmap(data);
	// drawplayer(data);
	castAllRay(data);
}

void	player_rot(t_data *data, int keycode)
{
	if (keycode == 123)
	{
		data->angle -= 0.1 * (M_PI / 180) * 50.00;
  		if (data->angle < 0)
			data->angle += 2 * M_PI;

		// mlx_clear_window(data->mlx, data->win);
		mlx_clear_window(data->mlx, data->win_test);
		// drawmap(data);
		// drawplayer(data);
		castAllRay(data);
	}
	if (keycode == 124)
	{
		data->angle += 0.1 * (M_PI / 180) * 50.00;
		if (data->angle > 2 * M_PI)
			data->angle -= 2 * M_PI;
		// mlx_clear_window(data->mlx, data->win);
		mlx_clear_window(data->mlx, data->win_test);
		// drawmap(data);
		// drawplayer(data);
		castAllRay(data);
	}
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 13)
		move_player_up(data);
	else if (keycode == 1)
		move_player_down(data);
	else if (keycode == 0)
		move_player_left(data);
	else if (keycode == 2)
		move_player_right(data);
	else if (keycode == 123 || keycode == 124)
		player_rot(data, keycode);
	return (0);
}

int	mouse_rotate(int x, int y, t_data *data)
{
	int	safe_zone;

	if (x < 0 || x > Scren_W || y < 0 || y > Scren_H)
		return (0);
	safe_zone = abs(x - (Scren_W / 2));
	if (safe_zone < 100)
		return (0);
	if (x > Scren_W / 2)
		data->angle -= safe_zone / 100;
	else
		data->angle += safe_zone / 100;
        if (data->angle > 2 * M_PI)
            data->angle -= 2 * M_PI;
        if (data->angle < 0)
            data->angle += 2 * M_PI;
    castAllRay(data);

	return (0);
}
