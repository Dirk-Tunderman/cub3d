/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:48:11 by aolde-mo          #+#    #+#             */
/*   Updated: 2024/01/27 16:38:40 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <stdio.h>

uint32_t	get_rgba(uint32_t g)
{
	int	r;
	int	b;

	r = 255;
	b = 255;
	return (r << 24 | g << 16 | b << 8 | 255);
}

uint32_t	get_pixel_rgba(uint8_t *arr)
{
	return (arr[0] << 24 | arr[1] << 16 | arr[2] << 8 | arr[3]);
}

void	calculate_x_wall(t_data *data)
{
	t_player *player = data->player;
	t_ray *ray = data->ray;
	ray->x_texture = (int)(ray->x_wall * (double)data->texture->width);
	
	if (ray->vertical_wall_hit == true)
		ray->x_wall = player->x_pos + ray->perpendicular_wall_dist * ray->x_ray_dir;
	else
		ray->x_wall = player->y_pos + ray->perpendicular_wall_dist * ray->y_ray_dir;
	ray->x_wall = ray->x_wall - (int)ray->x_wall;
	ray->x_texture = (int)(ray->x_wall * (double)data->texture->width);
	if (ray->vertical_wall_hit == true && ray->y_ray_dir < 0)
		ray->x_texture = data->texture->width - ray->x_texture - 1;
	if (ray->vertical_wall_hit == false && ray->x_ray_dir > 0)
		ray->x_texture = data->texture->width - ray->x_texture - 1;
	
}

void	put_stripe(t_data *data, int pixel_height, int x, int y)
{
	mlx_texture_t	*texture = data->texture;
	double	step_size = 1.0 * (double)texture->height / (double)pixel_height;
	uint32_t color;
	double texpos = (data->draw_start - screenHeight / 2 + pixel_height / 2) * step_size;

	for (int y = data->draw_start; y < data->draw_end; y++)
	{
		int texy = (int)texpos & (data->texture->height - 1);
		color = get_pixel_rgba(data->pixels_arr[(int)texpos * texture->width + data->ray->x_texture]);
		mlx_put_pixel(data->img, x, y, color);
		texpos += step_size;
	}
}

void	draw_line(t_data *data, double wall_dist, int x_pixel)
{
	int	pixel_height = (int)(screenHeight / data->ray->perpendicular_wall_dist);
	
	data->draw_start = -pixel_height / 2 + screenHeight / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = pixel_height / 2 + screenHeight / 2;
	if (data->draw_end > screenHeight)
		data->draw_end = screenHeight - 1;
	int y = 0;
	while (y < data->draw_start)
		mlx_put_pixel(data->img, x_pixel, y++, get_rgba(212));
	calculate_x_wall(data);
	put_stripe(data, pixel_height, x_pixel, y);
	y += data->draw_end - data->draw_start;
	while (y < screenHeight)
		mlx_put_pixel(data->img, x_pixel, y++, get_rgba(112));
}
