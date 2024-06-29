/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:47:26 by mait-elk          #+#    #+#             */
/*   Updated: 2024/06/11 15:41:46 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	print_data_collected(t_data	*data)
{
	print_2d(data->maps);
	printf("C: R %d\n", data->scene_info.ceiling_color.r);
	printf("C: G %d\n", data->scene_info.ceiling_color.g);
	printf("C: B %d\n", data->scene_info.ceiling_color.b);
	printf("√ NORTH_texture : %s\n", data->scene_info.north_texture);
	printf("√ WEST_texture : %s\n", data->scene_info.west_texture);
	printf("√ EAST_texture : %s\n", data->scene_info.east_texture);
	printf("√ SOUTH_texture : %s\n", data->scene_info.south_texture);
}

void	data_init(t_data *data, int ac, char **av)
{
	data_hook(data);
	ft_bzero(data, sizeof(t_data));
	check_file(ac, av);
	data->mlx.mlx_ptr = mlx_init();
	if (data->mlx.mlx_ptr == NULL)
		eput_error("Cannot Init Mlx Connection", "[MLX_DYLIB]", 1);
	init_lines();
	check_maps();
	data->mlx.window_ptr = mlx_new_window(data->mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (data->mlx.window_ptr == NULL)
		eput_error("cannot open mlx window", "[MLX_DYLIB]", 1);
	t_vector v;
	data->logo = mlx_xpm_file_to_image(data->mlx.mlx_ptr, "textures/cube.xpm", &v.x, &v.y);
	print_data_collected(data);
}
