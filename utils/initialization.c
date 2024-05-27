/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:47:26 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/27 17:13:36 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	data_init(t_data *data_ptr, int ac, char **av)
{
	int	fd;

	data_hook(data_ptr);
	ft_bzero(data_ptr, sizeof(t_data));
	fd = check_file(ac, av);
	init_lines(fd);
	check_lines();
	printf("C: R %d\n", data_ptr->scene_info.CEILING_color.r);
	printf("C: G %d\n", data_ptr->scene_info.CEILING_color.g);
	printf("C: B %d\n", data_ptr->scene_info.CEILING_color.b);
	printf("√ NORTH_texture : %s\n", data_hook(NULL)->scene_info.NORTH_texture);
	printf("√ WEST_texture : %s\n", data_hook(NULL)->scene_info.WEST_texture);
	printf("√ EAST_texture : %s\n", data_hook(NULL)->scene_info.EAST_texture);
	printf("√ SOUTH_texture : %s\n", data_hook(NULL)->scene_info.SOUTH_texture);
}
