/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:09:47 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/11/23 14:21:04 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <stdlib.h>

void	init_data(t_data *data)
{
	if (!data)
		exit(EXIT_FAILURE);
	data->mlx = mlx_init(screenWidth, screenHeight, "cub3d", false);
	data->img = mlx_new_image(data->mlx, screenWidth, screenHeight);
}

void	init_img(t_data *data)
{
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_loop(data->mlx);
}

void	exit_cub3d(t_data *data)
{
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	free(data);
}
