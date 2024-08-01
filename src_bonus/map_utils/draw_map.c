/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 08:35:46 by mait-elk          #+#    #+#             */
<<<<<<< HEAD:bonus/src/map_utils/draw_map.c
/*   Updated: 2024/08/01 16:32:50 by aabouqas         ###   ########.fr       */
=======
/*   Updated: 2024/08/01 17:13:59 by mait-elk         ###   ########.fr       */
>>>>>>> b99abdca85ed5e0178530524ee7e32ec6f8122e3:src_bonus/map_utils/draw_map.c
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

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
	map = data->map;
	sc_size.width = data->screen.width * TILE_SIZE;
	sc_size.height = data->screen.height * TILE_SIZE;
	grid.x = player_pos.x / TILE_SIZE;
	grid.y = player_pos.y / TILE_SIZE;
	if (i < ((WIN_WIDTH * MPSIZE) / 2) - 10)
	{
		if (player_pos.x > 0 && player_pos.x < sc_size.width
			&& player_pos.y > 0 && player_pos.y < sc_size.height
			&& map[grid.y][grid.x] == '1'
		)
			t_image_update_pixel(&data->minimap_layer,
				targ.x, targ.y, 0x66000000);
		else if (!is_door_minimap(player_pos, sc_size, targ))
			t_image_update_pixel(
				&data->minimap_layer, targ.x, targ.y, 0x66ffffff);
		return ;
	}
	t_image_update_pixel(&data->minimap_layer, targ.x, targ.y, 0x000000);
}

void	draw_mini_map(void)
{
	t_data		*data;
	t_vector2	targ;
	t_vector2	plyrpos;
	double		i;
	int			j;

	data = data_hook(NULL);
	i = 0;
	while (i <= 360)
	{
		plyrpos = data->player.position;
		j = 0;
		while (j < (WIN_WIDTH * MPSIZE) / 2)
		{
			targ.x = ((WIN_WIDTH * MPSIZE) / 2) + cos (deg_to_rad(i)) * j;
			targ.y = ((WIN_WIDTH * MPSIZE) / 2) + sin (deg_to_rad(i)) * j;
			put_pixel(plyrpos, targ, j);
			plyrpos.x += cos (deg_to_rad(data->player.angle + i + 90));
			plyrpos.y += sin (deg_to_rad(data->player.angle + i + 90));
			j++;
		}
		if (i == 0)
			data->north_icon_pos = (t_vector){((WIN_WIDTH * MPSIZE / 2) - 16) + (-cos (deg_to_rad(data->player.angle)) * (WIN_WIDTH * MPSIZE) / 2), ((WIN_WIDTH * MPSIZE / 2) - 16) + (sin (deg_to_rad(data->player.angle)) * (WIN_WIDTH * MPSIZE) / 2)};
		i += 0.30;
	}
<<<<<<< HEAD:bonus/src/map_utils/draw_map.c
	draw_player(WIN_WIDTH * 0.006);
=======
	draw_player(WIN_WIDTH * 0.005);
>>>>>>> b99abdca85ed5e0178530524ee7e32ec6f8122e3:src_bonus/map_utils/draw_map.c
}