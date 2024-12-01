/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:39:19 by hben-laz          #+#    #+#             */
/*   Updated: 2024/11/29 23:49:06 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player_down(t_data *data)
{
	double	new_x;
	double	new_y;
	double	buffer;

	buffer = 5.0;
	new_x = data->p_x - cos(data->angle) * data->speed;
	new_y = data->p_y - sin(data->angle) * data->speed;
	if (data->all_map[(int)((new_y - buffer) / T_S)]
			[(int)((new_x - buffer) / T_S)] == '1' ||
		data->all_map[(int)((new_y - buffer) / T_S)]
				[(int)((new_x + buffer) / T_S)] == '1' ||
		data->all_map[(int)((new_y + buffer) / T_S)]
				[(int)((new_x - buffer) / T_S)] == '1' ||
		data->all_map[(int)((new_y + buffer) / T_S)]
				[(int)((new_x + buffer) / T_S)] == '1')
	{
		return ;
	}
	data->p_x = new_x;
	data->p_y = new_y;
	cast_rays(data);
}

void	move_player_up(t_data *data)
{
	double	new_x;
	double	new_y;
	double	buffer;

	buffer = 5.0;
	new_x = data->p_x + cos(data->angle) * data->speed;
	new_y = data->p_y + sin(data->angle) * data->speed;
	if (data->all_map[(int)((new_y - buffer) / T_S)]
			[(int)((new_x - buffer) / T_S)] == '1' ||
		data->all_map[(int)((new_y - buffer) / T_S)]
				[(int)((new_x + buffer) / T_S)] == '1' ||
		data->all_map[(int)((new_y + buffer) / T_S)]
				[(int)((new_x - buffer) / T_S)] == '1' ||
		data->all_map[(int)((new_y + buffer) / T_S)]
				[(int)((new_x + buffer) / T_S)] == '1')
	{
		return ;
	}
	data->p_x = new_x;
	data->p_y = new_y;
	cast_rays(data);
}

void	move_player_left(t_data *data)
{
	double	new_x;
	double	new_y;
	double	buffer;

	buffer = 5.0;
	new_x = data->p_x + cos(data->angle - M_PI_2) * data->speed;
	new_y = data->p_y + sin(data->angle - M_PI_2) * data->speed;
	if (data->all_map[(int)((new_y - buffer) / T_S)]
			[(int)((new_x - buffer) / T_S)] == '1' ||
		data->all_map[(int)((new_y - buffer) / T_S)]
			[(int)((new_x + buffer) / T_S)] == '1' ||
		data->all_map[(int)((new_y + buffer) / T_S)]
			[(int)((new_x - buffer) / T_S)] == '1' ||
		data->all_map[(int)((new_y + buffer) / T_S)]
			[(int)((new_x + buffer) / T_S)] == '1')
	{
		return ;
	}
	data->p_x = new_x;
	data->p_y = new_y;
	cast_rays(data);
}

void	move_player_right(t_data *data)
{
	double	new_x;
	double	new_y;
	double	buffer;

	buffer = 5.0;
	new_x = data->p_x + cos(data->angle + M_PI_2) * data->speed;
	new_y = data->p_y + sin(data->angle + M_PI_2) * data->speed;
	if (data->all_map[(int)((new_y - buffer) / T_S)]
			[(int)((new_x - buffer) / T_S)] == '1' ||
		data->all_map[(int)((new_y - buffer) / T_S)]
			[(int)((new_x + buffer) / T_S)] == '1' ||
		data->all_map[(int)((new_y + buffer) / T_S)]
			[(int)((new_x - buffer) / T_S)] == '1' ||
		data->all_map[(int)((new_y + buffer) / T_S)]
			[(int)((new_x + buffer) / T_S)] == '1')
	{
		return ;
	}
	data->p_x = new_x;
	data->p_y = new_y;
	cast_rays(data);
}

void	player_rot(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->angle -= 0.1 * (M_PI / 180) * 50;
		if (data->angle < 0)
			data->angle += 2 * M_PI;
		cast_rays(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->angle += 0.1 * (M_PI / 180) * 50;
		if (data->angle > 2 * M_PI)
			data->angle -= 2 * M_PI;
		cast_rays(data);
	}
}
