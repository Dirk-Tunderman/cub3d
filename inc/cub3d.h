/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:38:02 by aolde-mo          #+#    #+#             */
/*   Updated: 2024/01/27 15:12:50 by aolde-mo         ###   ########.fr       */
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

#include <stdio.h>
#include <stdlib.h>

extern int world_map[mapWidth][mapHeight];


// positions we know before calculating
typedef struct	s_player{
// position of player
	double		x_pos;
	double		y_pos;
// direction of ray
	double		x_dir;
	double		y_dir;
// the bigger the plane the bigger the POV
	double		x_plane;
	double		y_plane;
}				t_player;

typedef struct	s_ray{
// camera plane
	double		x_camera;
// the map position of the player
	int			x_map;
	int			y_map;
// side_dist is the distance TO the first wall hit from x or y from the starting position
	double		x_side_dist;
	double		y_side_dist;
// delta_dist is the distance FROM the first wall hit to the next wall in the x or y axes
	double		x_delta_dist;
	double		y_delta_dist;
// dir the ray is going
	double		x_ray_dir;
	double		y_ray_dir;
// to calculate perpendicular distance to wall from camera pov (not the player position)
// we calculate from camera pov to avoid fisheye effect
	double		perpendicular_wall_dist;
// negative or positive step direction
	int			x_step;
	int			y_step;
// on which x the ray hits the wall
	double		x_wall;
// x of the texture we should use
	int			x_texture;
// whether vertical wall is hit
	bool		vertical_wall_hit;
}				t_ray;

typedef struct	s_data{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*texture;
	t_player		*player;
	t_ray			*ray;
	uint8_t			**pixels_arr;
	int				draw_start;
	int				draw_end;
}					t_data;

typedef enum	e_directions
{
	LEFT,
	RIGHT,
	FORWARD,
	BACKWARD,
	ROTATE_LEFT,
	ROTATE_RIGHT,
}				t_directions;
//main
int		main(int argc, char **argv);

//init
void	initialize(t_data *data);

//rayzzz
void	raycasting(t_data *data);
void	calculate_ray_direction(t_data *data, int x);
void	calculate_delta_distance(t_ray *ray);
void	calculate_side_distance(t_player *player, t_ray *ray);
void	dda(t_ray *ray);
void	calculate_perpendicular_wall_dist(t_ray *ray);

//draw
void		draw_line(t_data *data, double wall_dist, int x_pixel);
void		put_stripe(t_data *data, int pixel_height, int x, int y);
uint32_t	get_rgba(uint32_t g);
uint32_t	get_pixel_rgba(uint8_t *arr);

//hooks
void	key_hook(void *param);
//exit
void	close_mlx(t_data *data);
void	cleanup(t_data *data);

//check
void	check_input(int argc, char **argv);

//error
void	print_error(char *s);

//texture parsing

void	texture_to_doubleptr(t_data *data);

#endif