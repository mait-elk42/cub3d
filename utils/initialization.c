/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:47:26 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/29 10:47:32 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	data_init(t_data *data_ptr, int ac, char **av)
{
	data_hook(data_ptr);
	ft_bzero(data_ptr, sizeof(t_data));
	check_file(ac, av);
	init_lines();
	check_maps();
	print_2d(data_ptr->maps);
	printf("C: R %d\n", data_ptr->scene_info.ceiling_color.r);
	printf("C: G %d\n", data_ptr->scene_info.ceiling_color.g);
	printf("C: B %d\n", data_ptr->scene_info.ceiling_color.b);
	printf("√ NORTH_texture : %s\n", data_hook(NULL)->scene_info.north_texture);
	printf("√ WEST_texture : %s\n", data_hook(NULL)->scene_info.west_texture);
	printf("√ EAST_texture : %s\n", data_hook(NULL)->scene_info.east_texture);
	printf("√ SOUTH_texture : %s\n", data_hook(NULL)->scene_info.south_texture);
}
