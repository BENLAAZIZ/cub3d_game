/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-laz <hben-laz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 00:42:41 by hben-laz          #+#    #+#             */
/*   Updated: 2024/12/01 19:09:43 by hben-laz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_data *data, double y, double x)
{
	if (x <= 0 || x >= data->lenght * T_S || y <= 0 || y >= data->height * T_S)
		return (1);
	if (data->all_map[(int)y / (int)T_S][(int)x / (int)T_S] == '1')
		return (1);
	return (0);
}

int	player_direction(char c, t_data *data)
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

void	get_player_position(t_data *data)
{
	if (data->all_map == NULL)
		return ;
	while (data->all_map[(int)data->p_y])
	{
		data->p_x = 0;
		while (data->all_map[(int)data->p_y][(int)data->p_x])
		{
			if (player_direction(data->all_map[(int)data->p_y]
					[(int)data->p_x], data))
				break ;
			data->p_x++;
		}
		if (player_direction(data->all_map[(int)data->p_y]
				[(int)data->p_x], data))
			break ;
		data->p_y++;
	}
	data->p_x = (data->p_x * T_S) + (T_S / 2);
	data->p_y = (data->p_y * T_S) + (T_S / 2);
}
