/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:43:20 by aolde-mo          #+#    #+#             */
/*   Updated: 2023/11/21 14:05:54 by aolde-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_input(int argc, char **argv)
{
	if (argc != 2)
		print_error("Wrong amount of arguments. Only *.cub is needed\n");
	argv++;
	return (0);
}
