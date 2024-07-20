/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 08:35:46 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/20 17:22:34 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_player(double player_size)
{
	double	i;

	i = 0;
	while (i < player_size)
	{
		put_player_shape(i);
		i += 0.1;
	}
}

void	put_pixel(t_vector2 player_pos, t_vector2 targ, int i)
{
	t_data		*data;
	char		**map;
	t_size		sc_size;
	t_vector	grid;

	data = data_hook(NULL);
	map = data->maps;
	sc_size.width = data->screen.width * TILE_SIZE;
	sc_size.height = data->screen.height * TILE_SIZE;
	grid.x = player_pos.x / TILE_SIZE;
	grid.y = player_pos.y / TILE_SIZE;
	if (i < 90)
	{
		if (player_pos.x > 0 && player_pos.x < sc_size.width
			&& player_pos.y > 0 && player_pos.y < sc_size.height
			&& map[grid.y][grid.x] == '1'
		)
			t_image_update_pixel(&data->minimaps_layer, targ.x, targ.y, 0x66000000);
		else
			t_image_update_pixel(
				&data->minimaps_layer, targ.x, targ.y, 0x66ffffff);
		return ;
	}
	t_image_update_pixel(&data->minimaps_layer, targ.x, targ.y, 0x000000);
}

void	draw_mini_map()
{
	t_data		*data;
	t_size		size;
	t_vector2	targ;
	t_vector2	plyrpos;

	data = data_hook(NULL);
	size = (t_size) {0, 0};
	double i = 0;
	while (i <= 360) {
		plyrpos = data->player.position;
		int j = 0;
		while (j < 100)
		{
			targ.x = 100 + cos (deg_to_rad(i)) * j;
			targ.y = 100 + sin (deg_to_rad(i)) * j;
			put_pixel(plyrpos, targ, j);
			j++;
			plyrpos.x += cos (deg_to_rad(data->player.angle + i + 90));
			plyrpos.y += sin (deg_to_rad(data->player.angle + i + 90));
		}
		i += 0.25;
	}
	draw_player(5);
}
