/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:43:17 by aolde-mo          #+#    #+#             */
/*   Updated: 2024/01/26 18:22:22 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <stdlib.h>
#include <stdio.h>

void	leakss()
{
	system("leaks cub3d");
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	// check_input(argc, argv);
	// atexit(leakss);
	initialize(data);
	// raycasting(data);
	mlx_loop_hook(data->mlx, &key_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	cleanup(data);
	return (0);
}
