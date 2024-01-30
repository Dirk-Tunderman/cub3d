/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:17:28 by aolde-mo          #+#    #+#             */
/*   Updated: 2024/01/28 15:37:26 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	fill_pixel_arr(t_data *data, int pixel_count, int direction)
{
	int	i;
	int	j;

	i = 0;
	while (i < pixel_count)
	{
		data->pixels[direction][i] = malloc(sizeof(uint8_t) * 4);
		//protect
		j = 0;
		while (j < 4)
		{
			data->pixels[direction][i][j] = data->text_arr[direction]->pixels[i * 4 + j];
			j++;
		}
		i++;
	}
}

void	texture_to_doubleptr(t_data *data)
{
	int		pixel_count;
	int		i = 0;
	while (i < 4) // 0 = NORTH | 1 = EAST | 2 = SOUTH | 3 = WEST
	{
		pixel_count = data->text_arr[i]->width * data->text_arr[i]->height;
		data->pixels[i] = malloc(sizeof(uint8_t *) * pixel_count); // arr has 4 unsigned chars per pixel (rgba)
		//protect
		fill_pixel_arr(data, pixel_count, i++);
	}
}
