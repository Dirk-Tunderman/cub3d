/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:43:17 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/11/26 15:14:27 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <stdlib.h>
#include <stdio.h>

void asd()
{
	system("leaks cub3d");
}

int	main(int argc, char **argv)
{
	// atexit(asd);
	t_data	*data;

	data = malloc(sizeof(t_data));
	// check_input(argc, argv);
	initialize(data);
	raycasting(data);
	// mlx_loop(data->mlx);
	// cleanup(data);
	return (0);
}
