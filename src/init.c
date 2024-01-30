/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:09:47 by aolde-mo          #+#    #+#             */
/*   Updated: 2024/01/30 09:03:35 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <stdlib.h>

void	init_player(t_player *player)
{
	player->x_pos = 8;
	player->y_pos = 6;
	player->x_dir = 1;
	player->y_dir = 0;
	player->x_plane = 0;
	player->y_plane = 0.66;
}
#include <stdio.h>

void	load_textures(t_data *data)
{

	data->text_arr = malloc(sizeof(mlx_texture_t *) * 4);
	//protect
	data->text_arr[NORTH] = mlx_load_png("/Users/aolde-mo/Desktop/Documents/github/cub3d/textures/wall3.png");
	data->text_arr[EAST] = mlx_load_png("/Users/aolde-mo/Desktop/Documents/github/cub3d/textures/soze.png");
	data->text_arr[SOUTH] = mlx_load_png("/Users/aolde-mo/Desktop/Documents/github/cub3d/textures/test.png");
	data->text_arr[WEST] = mlx_load_png("/Users/aolde-mo/Desktop/Documents/github/cub3d/textures/wall1.png");
	//PROTECTE ELKE
	texture_to_doubleptr(data);
}

void	initialize(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	//MAL PROTECT PLAYER
	data->ray = malloc(sizeof(t_ray));
	//MAL PROTECT RAY
	init_player(data->player);
	data->mlx = mlx_init(screenWidth, screenHeight, "cub3d", false);
	//PROTECT
	data->img = mlx_new_image(data->mlx, screenWidth, screenHeight);
	//PROTECT
	data->pixels = malloc(sizeof(uint8_t *) * 4);
	load_textures(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	//PROTECT
}

void	close_mlx(t_data *data)
{
	mlx_close_window(data->mlx);
	mlx_delete_image(data->mlx, data->img);
}

void	cleanup(t_data *data)
{
	// for (size_t i = 0; i < data->texture->width * data->texture->height; i++)
	// 	free(data->pixels_arr[i]);
	// mlx_delete_texture(data->texture);
	// free(data->pixels_arr);
	free(data->player);
	free(data->ray);
	free(data);
}
