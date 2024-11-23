#include "cub3d.h"

void	move_player_down(t_data *data)
{
	double x;
	double y;
	
	x = data->p_x - cos(data->angle) * 10.00;
	y = data->p_y - sin(data->angle) * 10.00;
	if (data->all_map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
		return ;
	data->p_y = y;
	data->p_x = x;
	castAllRay(data);

}
void	move_player_up(t_data *data)
{
	double y = data->p_y + sin(data->angle) * 10.00;
	double x = data->p_x + cos(data->angle) * 10.00;
	if (data->all_map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
		return ;
	data->p_y = y;
	data->p_x = x;
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
	castAllRay(data);
}

void	player_rot(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->angle -= 0.1 * (M_PI / 180) * 50;
  		if (data->angle < 0)
			data->angle += 2 * M_PI;
		castAllRay(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->angle += 0.1 * (M_PI / 180) * 50;
		if (data->angle > 2 * M_PI)
			data->angle -= 2 * M_PI;
		castAllRay(data);
	}
}