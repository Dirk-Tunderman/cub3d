/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:38:02 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/11/24 10:35:30 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define NOWALL 0
# define WALL 1

# define mapWidth 24
# define mapHeight 24
# define screenWidth 1920
# define screenHeight 1080

# include "../MLX42/include/MLX42/MLX42.h"

typedef struct	s_data{
	mlx_t		*mlx;
	mlx_image_t	*img;
}				t_data;

//main
int		main(int argc, char **argv);

//init
void	initialize(t_data *data);

//rayz
void	raycasting(t_data *data);

//exit
void	cleanup(t_data *data);

//check
void	check_input(int argc, char **argv);

//error
void	print_error(char *s);

#endif