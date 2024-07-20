/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:47:26 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/20 13:55:30 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	make_map_square(void)
{
	t_size	size;
	t_data	*data;
	char	**map;
	size_t	line_size;
	char	**new_map;

	ft_bzero(&size, sizeof(t_size));
	data = data_hook(NULL);
	map = data->maps;
	new_map = ft_calloc(data->screen.height + 1, sizeof(char *));
	while (map[size.height])
	{
		line_size = safe_strlen(map[size.height]);
		new_map[size.height] = ft_calloc(data->screen.width + 1, 1);
		if (new_map[size.height] == NULL)
		{
			free_tab(new_map);
			safe_exit(1);
		}
		ft_memcpy(new_map[size.height], map[size.height], line_size);
		size.height++;
	}
	free (data->maps);
	data->maps = new_map;
}

void	print_data_collected(t_data	*data)
{
	print_2d(data->maps);
	printf("C: R %d\n", data->scene_info.ceiling_color.r);
	printf("C: G %d\n", data->scene_info.ceiling_color.g);
	printf("C: B %d\n", data->scene_info.ceiling_color.b);
	printf("F: R %d\n", data->scene_info.floor_color.r);
	printf("F: G %d\n", data->scene_info.floor_color.g);
	printf("F: B %d\n", data->scene_info.floor_color.b);
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
	// settings_init();
	data->mlx.mlx_ptr = mlx_init();
	if (data->mlx.mlx_ptr == NULL)
		eput_error("Cannot Init Mlx Connection", "[MLX_DYLIB]", 1);
	init_lines();
	check_maps();
	data->mlx.window_ptr = mlx_new_window(data->mlx.mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (data->mlx.window_ptr == NULL)
		eput_error("cannot open mlx window", "[MLX_DYLIB]", 1);
	set_screen_size();
	make_map_square();
}
