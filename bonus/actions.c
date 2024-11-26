
#include "cub3d_bonus.h"


void	move_player_down(t_data *data)
{
    double	new_x;
    double	new_y;
    double	buffer = 5.0;

    new_x = data->p_x - cos(data->angle) * data->speed;
    new_y = data->p_y - sin(data->angle) * data->speed;
    // Check for collisions in a buffer area
    // Top-left corner
    if (data->all_map[(int)((new_y - buffer) / T_S)][(int)((new_x - buffer) / T_S)] == '1' ||
        // Top-right corner
        data->all_map[(int)((new_y - buffer) / T_S)][(int)((new_x + buffer) / T_S)] == '1' ||
        // Bottom-left corner
        data->all_map[(int)((new_y + buffer) / T_S)][(int)((new_x - buffer) / T_S)] == '1' ||
        // Bottom-right corner
        data->all_map[(int)((new_y + buffer) / T_S)][(int)((new_x + buffer) / T_S)] == '1')
    {
        return;
    }
    data->p_x = new_x;
    data->p_y = new_y;
    castAllRay(data);
}


void	move_player_up(t_data *data)
{
    double	new_x;
    double	new_y;
    double	buffer = 5.0;

    new_x = data->p_x + cos(data->angle) * data->speed;
    new_y = data->p_y + sin(data->angle) * data->speed;
    if (data->all_map[(int)((new_y - buffer) / T_S)][(int)((new_x - buffer) / T_S)] == '1' ||
        data->all_map[(int)((new_y - buffer) / T_S)][(int)((new_x + buffer) / T_S)] == '1' ||
        data->all_map[(int)((new_y + buffer) / T_S)][(int)((new_x - buffer) / T_S)] == '1' ||
        data->all_map[(int)((new_y + buffer) / T_S)][(int)((new_x + buffer) / T_S)] == '1')
    {
        return;
    }
    data->p_x = new_x;
    data->p_y = new_y;
    castAllRay(data);
}

// void	move_player_up(t_data *data)
// {
// 	double	y;
// 	double	x;

// 	y = data->p_y + sin(data->angle) * data->speed;
// 	x = data->p_x + cos(data->angle) * data->speed;
// 	if (data->all_map[(int)(y / T_S)][(int)(x / T_S)] == '1')
// 		return ;
// 	data->p_y = y;
// 	data->p_x = x;
// 	castAllRay(data);
// }

void	move_player_left(t_data *data)
{
    double	new_x;
    double	new_y;
    double	buffer = 5.0;

    new_x = data->p_x + cos(data->angle - M_PI_2) * data->speed;
    new_y = data->p_y + sin(data->angle - M_PI_2) * data->speed;
    if (data->all_map[(int)((new_y - buffer) / T_S)][(int)((new_x - buffer) / T_S)] == '1' ||
        data->all_map[(int)((new_y - buffer) / T_S)][(int)((new_x + buffer) / T_S)] == '1' ||
        data->all_map[(int)((new_y + buffer) / T_S)][(int)((new_x - buffer) / T_S)] == '1' ||
        data->all_map[(int)((new_y + buffer) / T_S)][(int)((new_x + buffer) / T_S)] == '1')
    {
        return;
    }
    data->p_x = new_x;
    data->p_y = new_y;
    castAllRay(data);
}

// void	move_player_left(t_data *data)
// {
// 	double	y;
// 	double	x;

// 	y = data->p_y + sin(data->angle - M_PI_2) * data->speed;
// 	x = data->p_x + cos(data->angle - M_PI_2) * data->speed;
// 	if (data->all_map[(int)(y / T_S)][(int)(x / T_S)] == '1')
// 		return ;
// 	data->p_y = y;
// 	data->p_x = x;
// 	castAllRay(data);
// }

void	move_player_right(t_data *data)
{
    double	new_x;
    double	new_y;
    double	buffer = 5.0;

    new_x = data->p_x + cos(data->angle + M_PI_2) * data->speed;
    new_y = data->p_y + sin(data->angle + M_PI_2) * data->speed;
    if (data->all_map[(int)((new_y - buffer) / T_S)][(int)((new_x - buffer) / T_S)] == '1' ||
        data->all_map[(int)((new_y - buffer) / T_S)][(int)((new_x + buffer) / T_S)] == '1' ||
        data->all_map[(int)((new_y + buffer) / T_S)][(int)((new_x - buffer) / T_S)] == '1' ||
        data->all_map[(int)((new_y + buffer) / T_S)][(int)((new_x + buffer) / T_S)] == '1')
    {
        return;
    }
    data->p_x = new_x;
    data->p_y = new_y;
    castAllRay(data);
}

// void	move_player_right(t_data *data)
// {
// 	double	y;
// 	double	x;

// 	y = data->p_y + sin(data->angle + M_PI_2) * data->speed;
// 	x = data->p_x + cos(data->angle + M_PI_2) * data->speed;
// 	if (data->all_map[(int)(y / T_S)][(int)(x / T_S)] == '1')
// 		return ;
// 	data->p_y = y;
// 	data->p_x = x;
// 	castAllRay(data);
// }

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
