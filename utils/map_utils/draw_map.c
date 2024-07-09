/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 08:35:46 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/08 10:08:00 by aabouqas         ###   ########.fr       */
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
	t_data	*data;
	t_size	size;
	t_size	s;
	char	**grid;

	data = data_hook((void *)0);
	grid = data->maps;
	size.height = (data->player.position.y / TILE_SIZE) - 2;
	size.width = 0;
	s.height = 0;
	while (grid[size.height])
	{
		s.width = 0;
		size.width = (data->player.position.x / TILE_SIZE) - 2;
		while (grid[size.height][size.width])
		{
			if (grid[size.height][size.width] == '1')
				draw_square(s, RGB_RED);
			size.width++;
			s.width += TILE_SIZE;
		}
		s.height += TILE_SIZE;
		size.height++;
	}
}
