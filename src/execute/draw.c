/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:48:11 by aolde-mo          #+#    #+#             */
/*   Updated: 2024/01/30 18:11:59 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

#include <stdio.h>

uint32_t	get_floor_ceiling_rgba(uint32_t g)
{
	int	r;
	int	b;

	r = 255;
	b = 255;
	return (r << 24 | g << 16 | b << 8 | 255);
}

// uint32_t	get_floor_ceiling_rgba(uint32_t *flor_clng)
// {
// 	return (flor_clng[0] << 24 | flor_clng[1] << 16 | flor_clng[2] << 8 | 255);
// }

uint32_t	get_pixel_rgba(uint8_t *arr)
{
	return (arr[0] << 24 | arr[1] << 16 | arr[2] << 8 | arr[3]);
}

void	calculate_x_wall(t_data *data, t_direction direction)
{
	mlx_texture_t	*texture = data->text_arr[direction];
	t_player *player = data->player;
	t_ray *ray = data->ray;
	ray->x_texture = (int)(ray->x_wall * (double)texture->width);
	
	if (ray->vertical_wall_hit == true)
		ray->x_wall = player->x_pos + ray->perpendicular_wall_dist * ray->x_ray_dir;
	else
		ray->x_wall = player->y_pos + ray->perpendicular_wall_dist * ray->y_ray_dir;
	ray->x_wall = ray->x_wall - (int)ray->x_wall;
	ray->x_texture = (int)(ray->x_wall * (double)texture->width);
	
	// preventing flipped images
	if (ray->vertical_wall_hit == true && ray->y_ray_dir > 0)
		ray->x_texture = data->text_arr[direction]->width - ray->x_texture - 1;
	if (ray->vertical_wall_hit == false && ray->x_ray_dir < 0)
		ray->x_texture = data->text_arr[direction]->width - ray->x_texture - 1;
	
}

void	put_stripe(t_data *data, int x, int y)
{
	mlx_texture_t	*texture;
	int				direction;
	double			step;
	uint32_t		color;

	direction = find_direction(data);
	texture = data->text_arr[direction];
	step = (double)texture->height / (double)data->line_height;
	double texpos = (data->draw_start - screenHeight / 2 + data->line_height / 2) * step;

	calculate_x_wall(data, direction);
	while (y < data->draw_end)
	{
		color = get_pixel_rgba(data->pixels[direction][(int)texpos * texture->width + data->ray->x_texture]);
		mlx_put_pixel(data->img, x, y, color);
		texpos += step;
		y++;
	}
}

void	draw_line(t_data *data, int x)
{
	int	y;

	y = 0;
	calculate_draw_vars(data);
	while (y < data->draw_start)
		mlx_put_pixel(data->img, x, y++, get_floor_ceiling_rgba(212));
	put_stripe(data, x, y);
	y += data->draw_end - data->draw_start;
	while (y < screenHeight)
		mlx_put_pixel(data->img, x, y++, get_floor_ceiling_rgba(112));
}
