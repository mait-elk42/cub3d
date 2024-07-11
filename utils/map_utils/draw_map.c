/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 08:35:46 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/11 15:48:19 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_square(t_size i, int color)
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
			t_image_update_pixel(&image, data->player.position.x + i.width + size.width, data->player.position.y + i.height + size.height, color);
			size.width++;
		}
		size.height++;
	}
}

void	draw_mini_map()
{
	t_vector	player_pos;
	t_data	*data;
	t_size	grid;
	t_size	i;
	char	**map;

	data = data_hook((void *)0);
	player_pos.x = data->player.position.x / TILE_SIZE;
	player_pos.y = data->player.position.y / TILE_SIZE;
	map = data->maps;
	grid.height = player_pos.y - 2;
	i.height = player_pos.y + 2;
	while (map[grid.height])
	{
		i.width = player_pos.x;
		grid.width = player_pos.x - 2;
		while (map[grid.height][grid.width])
		{
			if (map[grid.height][grid.width] == '1')
				draw_square(i, RGB_RED);
			else if (map[grid.height][grid.width] == '0')
				draw_square(i, RGB_WHITE);
			grid.width++;
			i.width += TILE_SIZE;
		}
		i.height += TILE_SIZE;
		grid.height++;
	}
}
