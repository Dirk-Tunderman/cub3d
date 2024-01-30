/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:49:09 by aolde-mo          #+#    #+#             */
/*   Updated: 2024/01/30 08:46:00 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <math.h>

#define MOVE_SPEED 0.15
#define ROTATE_SPEED 0.0625

#define POV_MIN 0.2
#define POV_MAX 1.0

#define MIN_DIST 0.125

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

void	rotate(t_data *data, t_player *player, t_movement movement)
{
	double	tmp_x_dir;
	double	tmp_x_plane;

	tmp_x_dir = player->x_dir;
	tmp_x_plane = player->x_plane;
	if (movement == ROTATE_LEFT)
	{
		player->x_dir = player->x_dir * cos(-ROTATE_SPEED) - player->y_dir * sin(-ROTATE_SPEED);
		player->y_dir = tmp_x_dir * sin(-ROTATE_SPEED) + player->y_dir * cos(-ROTATE_SPEED);
		player->x_plane = player->x_plane * cos(-ROTATE_SPEED) - player->y_plane * sin(-ROTATE_SPEED);
		player->y_plane = tmp_x_plane * sin(-ROTATE_SPEED) + player->y_plane * cos(-ROTATE_SPEED);
	}
	if (movement == ROTATE_RIGHT)
	{
		player->x_dir = player->x_dir * cos(ROTATE_SPEED) - player->y_dir * sin(ROTATE_SPEED);
		player->y_dir = tmp_x_dir * sin(ROTATE_SPEED) + player->y_dir * cos(ROTATE_SPEED);
		player->x_plane = player->x_plane * cos(ROTATE_SPEED) - player->y_plane * sin(ROTATE_SPEED);
		player->y_plane = tmp_x_plane * sin(ROTATE_SPEED) + player->y_plane * cos(ROTATE_SPEED);
	}
	raycasting(data);
}

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static void	move_forward_backward(t_data *data, t_movement movement)
{
	t_player	*player;
	double		tmp_x;
	double		tmp_y;
	int			sign;

	player = data->player;
	if (movement == FORWARD)
		sign = 1;
	if (movement == BACKWARD)
		sign = -1;
	//making temporaly x and y position to check for wall collisions
	tmp_x = player->x_pos + player->x_dir * MOVE_SPEED * sign;
	tmp_y = player->y_pos + player->y_dir * MOVE_SPEED * sign;
	if (wworld_map[(int)tmp_y][(int)tmp_x] == WALL)
		return;
	player->x_pos = tmp_x;
	player->y_pos = tmp_y;
	raycasting(data);
}

static void	move_left_right(t_data *data, t_movement movement)
{
	t_player	*player;
	double		tmp_x;
	double		tmp_y;

	player = data->player;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		tmp_x = player->x_pos + player->y_dir * MOVE_SPEED;
		tmp_y = player->y_pos - player->x_dir * MOVE_SPEED;
	}
	else
	{
		tmp_x = player->x_pos - player->y_dir * MOVE_SPEED;
		tmp_y = player->y_pos + player->x_dir * MOVE_SPEED;
	}
	if (wworld_map[(int)tmp_y][(int)tmp_x] == WALL)
		return;
	player->x_pos = tmp_x;
	player->y_pos = tmp_y;
	raycasting(data);
}

void	key_hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate(data, data->player, ROTATE_LEFT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate(data, data->player, ROTATE_RIGHT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		close_mlx(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_forward_backward(data, FORWARD);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_forward_backward(data, BACKWARD);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_left_right(data, LEFT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_left_right(data, RIGHT);
}
