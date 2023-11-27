/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:48:11 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/11/27 15:05:39 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <stdio.h>

int	get_rgba()
{
	int	r;
	int	g;
	int	b;

	r = 255;
	g = 255;
	b = 255;
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	draw_line(t_data *data, double wall_dist, int x_pixel)
{
	// if (wall_dist < 0)
	// 	wall_dist = 1;
	int	pixel_height = (int)(screenHeight / wall_dist);
	int	floor_ceiling_height = (screenHeight - pixel_height) / 2;
	int y = 0;
	while (y < floor_ceiling_height)
	{
		mlx_put_pixel(data->img, x_pixel, y, get_rgba());
		y++;
	}
	while (y < screenHeight - floor_ceiling_height)
		y++;
	while (y < screenHeight)
	{
		mlx_put_pixel(data->img, x_pixel, y, get_rgba());
		y++;
	}

	
	// if (x_pixel % 100 == 0)
	// 	printf("%lf\n", wall_dist);
}
