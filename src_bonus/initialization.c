/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:47:26 by mait-elk          #+#    #+#             */
/*   Updated: 2024/08/01 14:38:04 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	make_map_square(void)
{
	t_size	size;
	t_data	*data;
	char	**map;
	size_t	line_size;
	char	**new_map;

	ft_bzero(&size, sizeof(t_size));
	data = data_hook(NULL);
	map = data->map;
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
	free_tab(data->map);
	data->map = new_map;
}

void	print_data_collected(t_data	*data)
{
	print_2d(data->map);
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

int	_mlx_init(t_data *data)
{
	void	*m_win;
	void	*m_ptr;

	m_ptr = mlx_init();
	if (m_ptr == NULL)
	{
		print(2, "Cannot Init Mlx Connection" "[MLX_DYLIB]", 1);
		exit (1);
	}
	m_win = mlx_new_window (m_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (m_ptr == NULL)
	{
		print (2, "cannot open mlx window" "[MLX_DYLIB]", 1);
		exit (1);
	}
	data->mlx.mlx_ptr = m_ptr;
	data->mlx.window_ptr = m_win;
	return (0);
}
void	check_textures(void)
{
	t_data	*data;
	int		i;

	i = 0;
	data = data_hook(NULL);
	while (data->lines && data->lines[i] && i < 4)
	{
		check_texture(str_skip_wsp (data->lines[i]), str_skip_wsp(data->lines[i] + 3));
		i++;
	}
}


void	data_init(t_data *data, int ac, char **av)
{
	data_hook(data);
	ft_bzero(data, sizeof(t_data));
	check_file(ac, av);
	_mlx_init (data);
	init_lines();
	check_map();
	check_textures();
	set_screen_size();
	make_map_square();
	print_data_collected(data);
}
