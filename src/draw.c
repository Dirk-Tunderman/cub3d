/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:48:11 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/11/28 18:50:56 by aolde-mo         ###   ########.fr       */
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
	int	pixel_height = (int)((double)screenHeight / wall_dist);
	int	floor_ceiling_height = (screenHeight - pixel_height) / 2;
	if (floor_ceiling_height < 0)
		floor_ceiling_height = 0;
	int y = 0;
	while (y < floor_ceiling_height)
		mlx_put_pixel(data->img, x_pixel, y++, get_rgba(220));
	while (y < screenHeight - floor_ceiling_height)
		mlx_put_pixel(data->img, x_pixel, y++, get_rgba(0));
	while (y < screenHeight)
		mlx_put_pixel(data->img, x_pixel, y++, get_rgba(255));
}
