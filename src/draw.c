/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:48:11 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/11/27 17:22:55 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <stdio.h>

int	get_rgba(int g)
{
	int	r;
	int	asd;
	int	b;

	r = 255;
	asd = g;
	b = 255;
	return (r << 24 | g << 16 | b << 8 | 255);
}

#include <stdio.h>
void	draw_line(t_data *data, double wall_dist, int x_pixel)
{
	// if (wall_dist < 0)
	// 	wall_dist = 1;
	int	pixel_height = (int)((double)screenHeight / wall_dist);
	if (pixel_height > screenHeight / 10 * 8)
		pixel_height = screenHeight / 10 * 9;
	int	floor_ceiling_height = (screenHeight - pixel_height) / 2;
	int y = 0;
	while (y < floor_ceiling_height)
		mlx_put_pixel(data->img, x_pixel, y++, get_rgba(220));
	while (y < screenHeight - floor_ceiling_height)
		mlx_put_pixel(data->img, x_pixel, y++, get_rgba(0));
	while (y < screenHeight)
		mlx_put_pixel(data->img, x_pixel, y++, get_rgba(255));
}
