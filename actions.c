/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:47:52 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/13 22:01:51 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"


void	move_player_down(t_data *data)
{
	double x;
	double y;
	
	x = data->p_x - cos(data->angle) * 10.00;
	y = data->p_y - sin(data->angle) * 10.00;
	if (data->all_map[(int)y / 10][(int)x / 10] == '1')
		return ;
	data->p_y = y;
	data->p_x = x;
	mlx_clear_window(data->mlx, data->win);
	mlx_clear_window(data->mlx, data->win_test);
	drawmap(data);
	drawplayer(data);
	castAllRay(data);
}

void	move_player_up(t_data *data)
{
	double y = data->p_y + sin(data->angle) * 10.00;
	double x = data->p_x + cos(data->angle) * 10.00;
	if (data->all_map[(int)y / 10][(int)x / 10] == '1')
		return ;
	data->p_y = y;
	data->p_x = x;
	mlx_clear_window(data->mlx, data->win);
	mlx_clear_window(data->mlx, data->win_test);
	drawmap(data);
	drawplayer(data); 
	castAllRay(data);
}

void	move_player_left(t_data *data)
{ 
	double y = data->p_y + sin(data->angle - M_PI_2) * 10.00;
	double x = data->p_x + cos(data->angle - M_PI_2) * 10.00;
	if (data->all_map[(int)y / 10][(int)x / 10] == '1')
		return ;
	data->p_y = y;
	data->p_x = x;
	mlx_clear_window(data->mlx, data->win);
	mlx_clear_window(data->mlx, data->win_test);
	drawmap(data);
	drawplayer(data);
	castAllRay(data);
}

void	move_player_right(t_data *data)
{
	double y = data->p_y + sin(data->angle + M_PI_2) * 10.00;
	double x = data->p_x + cos(data->angle + M_PI_2) * 10.00;
	if (data->all_map[(int)y / 10][(int)x / 10] == '1')
		return ;
	data->p_y = y;
	data->p_x = x;
	mlx_clear_window(data->mlx, data->win);
	mlx_clear_window(data->mlx, data->win_test);
	drawmap(data);
	drawplayer(data);
	castAllRay(data);
}

void	player_rot(t_data *data, int keycode)
{
	if (keycode == 123)
	{
		data->angle -= 0.1 * (M_PI / 180) * 50;
  		if (data->angle < 0)
			data->angle += 2 * M_PI;

		mlx_clear_window(data->mlx, data->win);
		mlx_clear_window(data->mlx, data->win_test);
		drawmap(data);
		drawplayer(data);
		castAllRay(data);
	}
	if (keycode == 124)
	{
		data->angle += 0.1 * (M_PI / 180) * 50;
		if (data->angle > 2 * M_PI)
			data->angle -= 2 * M_PI;
		mlx_clear_window(data->mlx, data->win);
		mlx_clear_window(data->mlx, data->win_test);
		drawmap(data);
		drawplayer(data);
		castAllRay(data);
	}
}

int	key_press(int keycode, t_data *data)
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
	if (keycode == 123 || keycode == 124)
		player_rot(data, keycode);
	return (0);
}
