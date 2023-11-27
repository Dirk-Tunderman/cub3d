/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:23:37 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/11/27 14:42:04 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <math.h>
#include <stdbool.h>

int world_map[mapWidth][mapHeight] =
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
		{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1}, // 11 
		{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1}, // 12
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 13
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 14
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 15
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 16
		{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 17
		{1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 18
		{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 19
		{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 20
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 21
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, // 22
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} //y 23
};


#include <stdio.h>

void	calculate_ray_direction(t_data *data, int x)
{
	t_ray		*ray;
	t_player	*player;

	ray = data->ray;
	player = data->player;
	ray->x_camera = 2 * x / (double)screenWidth - 1;
	ray->x_ray_dir = player->x_dir + player->x_plane * ray->x_camera;
	ray->y_ray_dir = player->y_dir + player->y_plane * ray->x_camera;
}

// calculates the nearest x or y wall from the first side distance.
// if the ray goes straight along the x or y axes (the ray direction is zero) it will never reach an wall
// so we put the difference to an large number (1e10 == 1 x 10^10).
// also make the distance absolute. Since a distance can not be negative.
void	calculate_delta_distance(t_ray *ray)
{
	if (ray->x_ray_dir == 0)
		ray->x_delta_dist = 1e10;
	else
		ray->x_delta_dist = fabs(1 / ray->x_ray_dir);
	if (ray->y_ray_dir == 0)
		ray->y_delta_dist = 1e10;
	else
		ray->y_delta_dist = fabs(1 / ray->y_ray_dir);
}

// calculates the distance between the starting position and
// the first wall in the x- and y-axis
void	calculate_side_distance(t_player *player, t_ray *ray)
{
	ray->x_map = (int)player->x_pos;
	ray->y_map = (int)player->y_pos;
	if (ray->x_ray_dir < 0)
	{
		ray->x_step = -1;
		ray->x_side_dist = (player->x_pos - ray->x_map) * ray->x_delta_dist;
	}
	else
	{
		ray->x_step = 1;
		ray->x_side_dist = (ray->x_map + 1 - player->x_pos) * ray->x_delta_dist;
	}
	if (ray->y_ray_dir < 0)
	{
		ray->y_step = -1;
		ray->y_side_dist = (player->y_pos - ray->y_map) * ray->y_delta_dist;
	}
	else
	{
		ray->y_step = 1;
		ray->y_side_dist = (ray->y_map + 1 - player->y_pos) * ray->y_delta_dist;
	}
}



void	dda(t_ray *ray)
{
	bool	wall_is_hit;

	wall_is_hit = false;
	while (!wall_is_hit)
	{
		if (ray->x_side_dist < ray->y_side_dist)
		{
			ray->x_side_dist += ray->x_delta_dist;
			ray->x_map += ray->x_step;
			ray->vertical_wall_hit = false;
		}
		else
		{
			ray->y_side_dist += ray->y_delta_dist;
			ray->y_map += ray->y_step;
			ray->vertical_wall_hit = true;
		}
		if (world_map[ray->y_map][ray->x_map] == 1)
			wall_is_hit = true;
	}
}

void	calculate_perpendicular_wall_dist(t_ray *ray)
{
	if (ray->vertical_wall_hit == true)
		ray->perpendicular_wall_dist = ray->y_side_dist - ray->y_delta_dist;
	else
		ray->perpendicular_wall_dist = ray->x_side_dist - ray->x_delta_dist;
}

void	raycasting(t_data *data)
{
	t_player	*player;
	t_ray		*ray;
	int			x;

	player = data->player;
	ray = data->ray;
	x = 0;
	while (x < screenWidth)
	{
		calculate_ray_direction(data, x);
		calculate_delta_distance(ray);
		calculate_side_distance(player, ray);
		dda(ray);
		calculate_perpendicular_wall_dist(ray);
		draw_line(data, ray->perpendicular_wall_dist, x);
		x++;
	}
}
