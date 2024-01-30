/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:57:28 by aolde-mo          #+#    #+#             */
/*   Updated: 2024/01/30 18:11:55 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	find_direction(t_data *data)
{
	t_ray	*ray;

	ray = data->ray;
	if (ray->vertical_wall_hit == true && ray->y_ray_dir < 0)
		return (NORTH);
	else if (ray->vertical_wall_hit == true)
		return (SOUTH);
	if (ray->x_ray_dir < 0)
		return (WEST);
	return (EAST);
}

void	calculate_draw_vars(t_data *data)
{
	data->line_height = screenHeight / data->ray->perpendicular_wall_dist;
	data->draw_start = -data->line_height / 2 + screenHeight / 2;
	data->draw_end = data->line_height / 2 + screenHeight / 2;
	if (data->draw_start < 0 || data->draw_start > data->draw_end
		|| data->draw_start > screenHeight)
	{
		data->draw_start = 0;
		data->draw_end = screenHeight;
	}
}

void	free_textures(t_data *data, int texture)
{
	int	i;

	i = 0;
	while (i < data->text_arr[texture]->width * data->text_arr[texture]->height)
		free(data->pixels[texture][i++]);
	free(data->pixels[texture]);
	mlx_delete_texture(data->text_arr[texture]);
}

// filling our pixel array with the data from the texture->pixels array.
// i * 4 + j, so we take steps of 4 because we want every rgba value for each i.
static void	fill_pixel_arr(t_data *data, int pixel_count, int direction)
{
	uint8_t	pixel;
	int		i;
	int		j;

	i = 0;
	while (i < pixel_count)
	{
		data->pixels[direction][i] = ft_malloc(sizeof(uint8_t) * 4);
		j = 0;
		while (j < 4)
		{
			pixel = data->text_arr[direction]->pixels[i * 4 + j];
			data->pixels[direction][i][j] = pixel;
			j++;
		}
		i++;
	}
}

// pixel array has 4 unsigned chars per pixel (rgba)
// pixels looks as follows:
// ***pixel = which texture (north, east, south, west)
// **pixel = which pixel we're at. we go from left to right then top to bottom.
// *pixel = rgba value of pixel (only 4 chars), 0 = r, 1 = g, 2 = b, 3 = a.
void	texture_to_doubleptr(t_data *data)
{
	int	pixel_count;
	int	i;

	i = 0;
	while (i < 4)
	{
		pixel_count = data->text_arr[i]->width * data->text_arr[i]->height;
		data->pixels[i] = ft_malloc(sizeof(uint8_t *) * pixel_count);
		fill_pixel_arr(data, pixel_count, i++);
	}
}
