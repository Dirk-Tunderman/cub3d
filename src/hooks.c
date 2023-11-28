/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:49:09 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/11/28 19:42:25 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <math.h>

#define MOVE_SPEED 0.125
#define ROTATE_SPEED 0.0625

int wworld_map[mapWidth][mapHeight] =
{
// x ==  0,1,2,3,4,5,6,7,8,9						22,23
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, //y == 0
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 1
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 2
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 3
		{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1}, // 4
		{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 5
		{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 6
		{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1}, // 7
		{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1}, // 8
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 9
		{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 10
		{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 11 
		{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 12
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1}, // 13
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 14
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1}, // 15
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1}, // 16
		{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1}, // 17
		{1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,1}, // 18
		{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 19
		{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 20
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 21
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 22
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} //y 23
};

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

#include <stdio.h>
void	execute_key(t_data *data)
{
	t_player	*player;
	double		tmp_x;
	double		tmp_y;
	int			sign;

	player = data->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		sign = 1;
	else
		sign = -1;
	tmp_x = player->x_pos + player->x_dir * MOVE_SPEED * 1 * sign;
	tmp_y = player->y_pos + player->y_dir * MOVE_SPEED * 1 * sign;
	printf("x %lf\t y %lf\txi %d\t yi %d\n", tmp_x, tmp_y, (int)tmp_x, (int)tmp_y);
	if (wworld_map[(int)tmp_y][(int)tmp_x] == 1)
		return;
	player->x_pos = tmp_x;
	player->y_pos = tmp_y;
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