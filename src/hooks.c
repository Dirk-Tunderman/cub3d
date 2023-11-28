/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:49:09 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/11/28 19:09:33 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <math.h>

#define MOVE_SPEED 0.125
#define ROTATE_SPEED 0.0625


void	rotate(t_data *data, t_player *player)
{
	double	tmp_x_dir;
	double	tmp_x_plane;

	tmp_x_dir = player->x_dir;
	tmp_x_plane = player->x_plane;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		player->x_dir = player->x_dir * cos(-ROTATE_SPEED) - player->y_dir * sin(-ROTATE_SPEED);
		player->y_dir = tmp_x_dir * sin(-ROTATE_SPEED) + player->y_dir * cos(-ROTATE_SPEED);
		player->x_plane = player->x_plane * cos(-ROTATE_SPEED) - player->y_plane * sin(-ROTATE_SPEED);
		player->y_plane = tmp_x_plane * sin(-ROTATE_SPEED) + player->y_plane * cos(-ROTATE_SPEED);
	}
	else
	{
		player->x_dir = player->x_dir * cos(ROTATE_SPEED) - player->y_dir * sin(ROTATE_SPEED);
		player->y_dir = tmp_x_dir * sin(ROTATE_SPEED) + player->y_dir * cos(ROTATE_SPEED);
		player->x_plane = player->x_plane * cos(ROTATE_SPEED) - player->y_plane * sin(ROTATE_SPEED);
		player->y_plane = tmp_x_plane * sin(ROTATE_SPEED) + player->y_plane * cos(ROTATE_SPEED);
	}
	raycasting(data);
}

void	execute_key(t_data *data)
{
	t_player	*player;
	int			sign;

	player = data->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		sign = 1;
	else
		sign = -1;
	player->y_pos = player->y_pos + player->y_dir * MOVE_SPEED * 1 * sign;
	player->x_pos = player->x_pos + player->x_dir * MOVE_SPEED * 1 * sign;
	raycasting(data);
	
}

void	key_hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		execute_key(data);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate(data, data->player);
}

void	key_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, &key_hook, data);
}