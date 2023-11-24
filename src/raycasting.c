/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:23:37 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/11/24 13:49:32 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <math.h>
#include <stdbool.h>

//positions we know before calculating
double x_pos = 22, y_pos = 12;
double x_dir = -1, y_dir = 0;
double x_plane = 0, y_plane = 0.66;

//side_dist is the distance TO the first wall hit from x or y from the starting position
double x_side_dist, y_side_dist;
//delta_dist is the distance FROM the first wall hit to the next wall in the x or y axes
double x_delta_dist, y_delta_dist;

//camera plane
double x_camera;
double x_ray_dir, y_ray_dir;

double x_perpendicular_wall_dist;


bool	wall_is_hit = false;
bool	north_south;

void	raycasting(t_data *data)
{
	for (int x = 0; x < screenWidth; x++)
	{
		x_camera = 2 * x / screenWidth - 1;
		x_ray_dir = x_dir + x_plane * x_camera;
		y_ray_dir = y_dir + y_plane * x_camera;
	}
	calculate_delta_distance();

}

// calculates the nearest x or y wall from the first side distance.
// if the ray goes straight along the x or y axes (the ray direction is zero) it will never reach an wall
// so we put the difference to an large number (1e10 - 1 x 10^10).
// also make the distance absolute. Since we care about the distance and a distance can not be negative.

void	calculate_delta_distance()
{
	if (x_ray_dir == 0)
		x_delta_dist = 1e10;
	else
		x_delta_dist = fabs(1 / x_ray_dir);
	if (y_ray_dir == 0)
		y_delta_dist = 1e10;
	else
		y_delta_dist = fabs(1 / y_ray_dir);
}