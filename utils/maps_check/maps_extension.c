/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_extension.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:07:09 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/26 10:56:30 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_extension(char *file_name)
{
	char	*start_point;

	start_point = _strchr(file_name, '\0');
	if (start_point == NULL || _strlen(file_name) <= 4)
	{
		print(2, "cub3d: MapName: Invalid file name", 1);
		exit(1);
	}
	start_point -= 4;
	if (str_equal(start_point, ".cub") == 0)
	{
		print(2, "cub3d: MapName: Invalid file name", 1);
		exit(1);
	}
}
