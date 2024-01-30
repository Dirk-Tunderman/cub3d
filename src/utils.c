/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:57:28 by aolde-mo          #+#    #+#             */
/*   Updated: 2024/01/30 09:03:01 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_direction(t_data *data)
{
	t_ray *ray = data->ray;
	if (ray->vertical_wall_hit == true && ray->y_ray_dir < 0)
		return (NORTH);
	else if (ray->vertical_wall_hit == true)
		return (SOUTH);
	if (ray->x_ray_dir < 0)
		return (WEST);
	return (EAST);
}