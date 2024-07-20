/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 08:35:46 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/20 08:55:56 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	custom_draw_line(t_image *image, char **map, t_vector2 from, t_vector2 to)
{
	t_data		*data;
	t_size		sc_size;
	t_vector2	plyrpos;
	t_vector2	diff;
	t_vector2	inc;
	float		step;

	data = data_hook(NULL);
	sc_size = data->screen;
	plyrpos = data->player.position;
	diff.x = to.x - from.x;
	diff.y = to.y - from.y;
	if (fabs(diff.x) > fabs(diff.y))
		step = fabs(diff.x);
	else
		step = fabs(diff.y);
	inc.x = diff.x / step;
	inc.y = diff.y / step;
	int i = 0;
	(void)map;
	// double angle = 0.0;
	while (i <= step)
	{
		// if ((from.y / TILE_SIZE) < data_hook(NULL)->screen.height && map[(int) (from.y / TILE_SIZE)][(int) (from.x / TILE_SIZE)] == '1')
		// 	t_image_update_pixel(image, from.x, from.y, 0xff0000);
		// if ((from.y / TILE_SIZE) < data_hook(NULL)->screen.height && map[(int) (from.y / TILE_SIZE)][(int) (from.x / TILE_SIZE)] == '0')
		// 	t_image_update_pixel(image, from.x, from.y, 0xffffff);
		// else
		// 
		// printf("%d %d\n", );
		// #error rotating the map
		if (plyrpos.x > 0 && plyrpos.x < sc_size.width * TILE_SIZE && plyrpos.y > 0 && plyrpos.y < sc_size.height * TILE_SIZE && map[(int) ((plyrpos.y) / TILE_SIZE)][(int) ((plyrpos.x) / TILE_SIZE)] == '1')
			t_image_update_pixel(image, from.x, from.y, 0x0000ff);
		else
			t_image_update_pixel(image, from.x, from.y, 0xffffff);
		from.x += inc.x;
		from.y += inc.y;
		plyrpos.x += inc.x;
		plyrpos.y += inc.y;
		i++;
	}
}

void	draw_mini_map()
{
	t_data		*data;
	t_size		size;
	t_vector2	targ;
	// t_vector2	end_point;
	t_vector2	ppos;

	data = data_hook(NULL);
	size = (t_size) {0, 0};

	// if (data->player.angle > 360)
	// 	data->player.angle = 0;
	// if (data->player.angle < 0)
	// 	data->player.angle = 360;
	// printf("%f\n", data->player.angle);
	double i = 0;
	while (i <= 360) {
		// end_point.x = 100 + cos (deg_to_rad(i)) * 100;
		// end_point.y = 100 + sin (deg_to_rad(i)) * 100;
		// custom_draw_line(&data->minimaps_layer, data->maps,  (t_vector2){100, 100}, end_point);
		ppos = data->player.position;
		int j = 0;
		while (j < 100)
		{
			targ.x = 100 + cos (deg_to_rad(i)) * j;
			targ.y = 100 + sin (deg_to_rad(i)) * j;
			if (ppos.x > 0 && ppos.x < data->screen.width * TILE_SIZE && ppos.y > 0 && ppos.y < data->screen.height * TILE_SIZE && data->maps[(int) ((ppos.y) / TILE_SIZE)][(int) ((ppos.x) / TILE_SIZE)] == '1')
				t_image_update_pixel(&data->minimaps_layer, targ.x, targ.y, 0x0000ff);
			else
				t_image_update_pixel(&data->minimaps_layer, targ.x, targ.y, 0xffffff);
			j+= 4;
			// printf("%f\n", data->player.angle);
			ppos.x += cos (deg_to_rad(i + data->player.angle + 90));
			ppos.y += sin (deg_to_rad(i + data->player.angle + 90));
		}
		i += 0.25;
	}
	// t_image_update_pixel(&data->minimaps_layer, 100, 100, 0xff0000);
	double pp = 0;
	while (pp < 7)
	{
		put_player_shape(pp);
		pp += 0.1;
	}
}
