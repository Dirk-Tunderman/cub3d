/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:38:02 by aolde-mo          #+#    #+#             */
/*   Updated: 2024/01/31 10:57:08 by aolde-mo         ###   ########.fr       */
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
# include "../libft/libft.h"
# include "get_next_line.h"

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
	t_player		*player;
	t_ray			*ray;
	
	mlx_texture_t	**text_arr;
	uint8_t			***pixels;
	
	int				line_height;
	int				draw_start;
	int				draw_end;

	int				**map;
	char			*WE;
	char			*NO;
	char			*SO;
	char			*EA;
	uint32_t		*F;
	uint32_t		*C;
	int				x_player;
	int				y_player;
	t_direction		start_direction;
}					t_data;

typedef enum	e_movement
{
	LEFT,
	RIGHT,
	FORWARD,
	BACKWARD,
	ROTATE_LEFT,
	ROTATE_RIGHT,
}				t_movement;

typedef enum	e_direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
}				t_direction;

//main
int		main(int argc, char **argv);

//init
void	initialize(t_data *data);

//rayzzz
void	raycasting(t_data *data);
void	calculate_ray_direction(t_data *data, int x);
void	calculate_delta_distance(t_ray *ray);
void	calculate_side_distance(t_player *player, t_ray *ray);
void	dda(t_data *data, t_ray *ray);

//draw
void		draw_line(t_data *data, int x);
void		put_stripe(t_data *data, int x, int y);

//hooks
void	key_hook(void *param);
//exit
void	close_mlx(t_data *data);
void	cleanup(t_data *data);

//check
void	check_input(int argc, char **argv);

//error
void	*ft_malloc(size_t size);
void	print_error(char *s);

//utils
int		find_direction(t_data *data);
void	calculate_draw_vars(t_data *data);
void	free_textures(t_data *data, int texture);
void	texture_to_doubleptr(t_data *data);

# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

//open the file
bool is_map_line(char *line);

//error check
bool starts_with_map_char(const char *line);
int find_first_line_map(char **original_array);
char **extract_map(char **original_array, int original_height);
int calculate_original_height(char **array);
void 	error_check(char **old_map, int height);
int get_l_line(char **array);


//----------------------------- PARSING -----------------------------//

int check_position(char *line, char *dir);
int check_three_variables(char *line);
int check_top_map(char **cub, int f_l);
int find_first_line_mapp(char **original_array); // does not take into consideration map error
int    parsing(char **twod);
char *str_n_copy(const char *src, int start);
int check_position_c(char *line, char *dir);
int ft_isspace(int c);
int is_valid_format(const char *str);
int validate_numbers_in_range(const char *str);

//------------------------------FINAL PARSE---------------------------//
void    final_parse(t_data *data, char **cub);
void process_wall_textures(t_data *data, char **cub);
int parse_int(const char **str);
uint32_t rgb_to_uint32(const char *rgb_str);
void process_floor_ceiling_colors(t_data *data, char **cub);
char *ft_strdup(const char *s);
void parse_rgb_values(uint32_t *color_array, const char *rgb_str);
void process_map(t_data *data, char **cub);
int char_to_int(char c);
void print_map(int **map, int rows, int cols);
void print_player_coordinates(int x, int y);
void calculate_map_dimensions(char **cub, int *rows, int *cols);

static char **process_line(char **array, char *line, int *num_rows);
static char **resize_array(char **array, int *capacity, int num_rows);
static char **initialize_array(int *capacity);
char **read_cub_file_to_2d_array(const char *filename, int *num_rows);
int count_rows_in_file(const char *filename);

#endif