/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:17:28 by aolde-mo          #+#    #+#             */
/*   Updated: 2024/01/26 20:39:32 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	texture_to_doubleptr(t_data *data)
{
	size_t	pixel_count = data->texture->width * data->texture->height;
	uint8_t	**texture_arr = malloc(sizeof(uint8_t *) * pixel_count); // arr has 4 unsigned chars per pixel (rgba)
	
	for (size_t i = 0; i < pixel_count; i++)
	{
		texture_arr[i] = malloc(sizeof(uint8_t) * 4);
		for (size_t j = 0; j < 4; j++)
			texture_arr[i][j] = data->texture->pixels[i * 4 + j];
	}
	data->pixels_arr = texture_arr;
}
