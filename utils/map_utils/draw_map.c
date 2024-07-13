/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 08:35:46 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/12 10:01:43 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// void	draw_square(t_size i, int color)
// {
// 	t_image	image;
// 	t_size	size;
// 	t_data	*data;

// 	size.height = 0;
// 	size.width = 0;
// 	data = data_hook(NULL);
// 	image = data->minimaps_layer;
// 	while (size.height < TILE_SIZE)
// 	{
// 		size.width = 0;
// 		while (size.width < TILE_SIZE)
// 		{
// 			t_image_update_pixel(&image, data->player.position.x + i.width + size.width, data->player.position.y + i.height + size.height, color);
// 			size.width++;
// 		}
// 		size.height++;
// 	}
// }

void	custom_draw_line(t_image *image, char **map, t_vector2 from, t_vector2 to)
{
	t_vector2	diff;
	t_vector2	inc;
	float		step;

	diff.x = to.x - from.x;
	diff.y = to.y - from.y;
	if (fabs(diff.x) > fabs(diff.y))
		step = fabs(diff.x);
	else
		step = fabs(diff.y);
	inc.x = diff.x / step;
	inc.y = diff.y / step;
	int i = 0;
	while (i <= step)
	{
		if ((from.y / TILE_SIZE) < data_hook(NULL)->screen.height && map[(int) (from.y / TILE_SIZE)][(int) (from.x / TILE_SIZE)] == '1')
			t_image_update_pixel(image, from.x, from.y, RGB_DARK_GREEN);
		if ((from.y / TILE_SIZE) < data_hook(NULL)->screen.height && map[(int) (from.y / TILE_SIZE)][(int) (from.x / TILE_SIZE)] == '0')
			t_image_update_pixel(image, from.x, from.y, RGB_WHITE);
		else
			t_image_update_pixel(image, from.x, from.y, RGB_BLUE);
		from.x += inc.x;
		from.y += inc.y;
		i++;
	}
}

void	draw_mini_map()
{
	t_data		*data;
	t_size		size;
	t_vector2	end_point;

	data = data_hook(NULL);
	size = (t_size) {0, 0};

	// if (data->player.angle > 360)
	// 	data->player.angle = 0;
	// if (data->player.angle < 0)
	// 	data->player.angle = 360;
	printf("%f\n", data->player.angle);
	double i = 0;
	while (i <= 360) {
		end_point.x = data->player.position.x + cos (deg_to_rad(i)) * 100;
		end_point.y = data->player.position.y + sin (deg_to_rad(i)) * 100;
		custom_draw_line(&data->scene_layer, data->maps, (t_vector2){(data->screen.width / 2) * 32, (data->screen.height / 2) * 32}, end_point);
		i += 0.2;
	}
}
