/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:09:47 by aolde-mo          #+#    #+#             */
/*   Updated: 2024/01/31 10:51:50 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

#include <stdlib.h>

//adding 0.5 offset to spawn in the middle of block
void	init_player(t_data *data)
{
	t_player	*player = data->player;

	player->x_pos = data->x_player + 0.5;
	player->y_pos = data->y_player + 0.5;
	player->x_dir = 1;
	player->y_dir = 0;
	player->x_plane = 0;
	player->y_plane = 0.66;
}
void	load_textures(t_data *data)
{

	data->text_arr = ft_malloc(sizeof(mlx_texture_t *) * 4);
	// data->text_arr[NORTH] = mlx_load_png("/Users/aolde-mo/Desktop/Documents/github/cub3d/textures/wall1.png");
	// data->text_arr[EAST] = mlx_load_png("/Users/aolde-mo/Desktop/Documents/github/cub3d/textures/wall3.png");
	// data->text_arr[SOUTH] = mlx_load_png("/Users/aolde-mo/Desktop/Documents/github/cub3d/textures/swastika.png");
	// data->text_arr[WEST] = mlx_load_png("/Users/aolde-mo/Desktop/Documents/github/cub3d/textures/lake.png");

	data->text_arr[NORTH] = mlx_load_png(data->NO);
	data->text_arr[EAST] = mlx_load_png(data->EA);
	data->text_arr[SOUTH] = mlx_load_png(data->SO);
	data->text_arr[WEST] = mlx_load_png(data->WE);
	texture_to_doubleptr(data);
}

void	close_mlx(t_data *data)
{
	mlx_close_window(data->mlx);
	mlx_delete_image(data->mlx, data->img);
}

void	cleanup(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < 4)
		free_textures(data, i++);
	mlx_terminate(data->mlx);
	free(data->text_arr);
	free(data->pixels);
	free(data->player);
	free(data->ray);
	free(data);
}

void	initialize(t_data *data)
{
	data->player = ft_malloc(sizeof(t_player));
	init_player(data);
	data->ray = ft_malloc(sizeof(t_ray));
	data->mlx = mlx_init(screenWidth, screenHeight, "cub3d", false);
	data->img = mlx_new_image(data->mlx, screenWidth, screenHeight);
	data->pixels = ft_malloc(sizeof(uint8_t *) * 4);
	load_textures(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}
