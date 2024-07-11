/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 08:35:46 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/09 19:01:09 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_square(t_size s, int color)
{
	t_image	image;
	t_size	size;
	t_data	*data;

	size.height = 0;
	size.width = 0;
	data = data_hook(NULL);
	image = data->minimaps_layer;
	while (size.height < TILE_SIZE)
	{
		size.width = 0;
		while (size.width < TILE_SIZE)
		{
			t_image_update_pixel(&image, size.width + s.width, size.height + s.height, color);
			size.width++;
		}
		size.height++;
	}
}

void	draw_mini_map()
{
	t_vector	player_pos;
	t_data	*data;
	t_size	size;
	t_size	s;
	char	**grid;

	data = data_hook((void *)0);
	player_pos.x = data->player.position.x / TILE_SIZE;
	player_pos.y = data->player.position.y / TILE_SIZE;
	grid = data->maps;
	size.height = player_pos.y - 2;
	s.height = player_pos.y;
	while (grid[size.height] && size.height <= (size_t) player_pos.y + 2)
	{
		s.width = 0;
		size.width = player_pos.x - 2;
		while (grid[size.height][size.width] && size.width <= (size_t) player_pos.x + 2)
		{
			if (grid[size.height][size.width] == '1')
				draw_square(s, RGB_RED);
			else if (grid[size.height][size.width] == '0')
				draw_square(s, RGB_WHITE);
			size.width++;
			s.width += TILE_SIZE;
		}
		s.height += TILE_SIZE;
		size.height++;
	}
}
