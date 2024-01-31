/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:43:17 by aolde-mo          #+#    #+#             */
/*   Updated: 2024/01/31 10:45:24 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <stdlib.h>
#include <stdio.h>

void	leakss()
{
	system("leaks cub3d");
}

static void	game(t_data *data)
{
	raycasting(data);
	mlx_loop_hook(data->mlx, &key_hook, data);
	mlx_loop(data->mlx);
}

// int	main(int argc, char **argv)
// {
// 	t_data	*data;

// 	data = ft_malloc(sizeof(t_data));
// 	// check_input(argc, argv);
// 	// atexit(leakss);
// 	initialize(data);
// 	game(data);
// 	cleanup(data);
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_data	*data;

    int error = 0;
	int num_rows = count_rows_in_file(argv[1]);
	data = malloc(sizeof(t_data));
	check_input(argc, argv);

	char **cub_data = read_cub_file_to_2d_array(argv[1], &num_rows);
	// int i = 0;
	// while (cub_data[i])
	// {
	// 	printf("%s\n", cub_data[i]);
	// 	i++;
	// }

	error = parsing(cub_data);
    if (error == -1)
    {
        printf("Error: Invalid map.\n");
        return (-1);
    }
    final_parse(data, cub_data);
	initialize(data);
	game(data);
	cleanup(data);

	for (int i = 0; i < num_rows; i++) {
    printf("%s\n", cub_data[i]);
    }

    // Free the allocated memory
    for (int i = 0; i < num_rows; i++) {
        free(cub_data[i]);
    }
    free(cub_data);

	return (0);
}
