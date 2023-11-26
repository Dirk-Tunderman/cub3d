/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:09:47 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/11/26 16:18:22 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <stdlib.h>

void	init_player(t_player *player)
{
	player->x_pos = 18;
	player->y_pos = 12;
	player->x_dir = -1;
	player->y_dir = 0;
	player->x_plane = 0;
	player->y_plane = 0.66;
}

void	initialize(t_data *data)
{
	//MAL PROTECT DATA
	data->player = malloc(sizeof(t_player));
	//MAL PROTECT PLAYER
	data->ray = malloc(sizeof(t_ray));
	//MAL PROTECT RAY
	init_player(data->player);
	data->mlx = mlx_init(screenWidth, screenHeight, "cub3d", false);
	data->img = mlx_new_image(data->mlx, screenWidth, screenHeight);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

void	cleanup(t_data *data)
{
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	free(data);
}
