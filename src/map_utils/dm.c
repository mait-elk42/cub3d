/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 08:35:46 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/18 18:19:33 by mait-elk         ###   ########.fr       */
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
	t_vector2	end_point;
	t_vector2	ppos;

	data = data_hook(NULL);
	size = (t_size) {0, 0};

	// if (data->player.angle > 360)
	// 	data->player.angle = 0;
	// if (data->player.angle < 0)
	// 	data->player.angle = 360;
	// printf("%f\n", data->player.angle);
	ppos = data->player.position;
	double i = 0;
	while (i <= 360) {
		end_point.x = 100 + cos (deg_to_rad(i)) * 100;
		end_point.y = 100 + sin (deg_to_rad(i)) * 100;
		custom_draw_line(&data->minimaps_layer, data->maps,  (t_vector2){100, 100}, end_point);
		i += 0.1;
	}
	put_player_shape(10);
}
