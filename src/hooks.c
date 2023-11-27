/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:49:09 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/11/27 17:35:34 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	key_hook(void *param)
{
	t_data	*data;

	data = param;
	// if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT));
		
	// if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT));
		
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		data->player->x_pos += 0.1;
		raycasting(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		data->player->x_pos -= 0.1;
		raycasting(data);
	}
}

void	key_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, &key_hook, data);
}