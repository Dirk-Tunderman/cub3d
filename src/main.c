/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:43:17 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/11/27 15:48:51 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	check_input(argc, argv);
	initialize(data);
	raycasting(data);
	key_hooks(data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	cleanup(data);
	return (0);
}
