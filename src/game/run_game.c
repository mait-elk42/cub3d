/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/08/02 08:52:14 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_line(t_image *image, int color, t_vector2 from, t_vector2 to)
{
	int			i;
	t_vector2	diff;
	t_vector2	inc;
	float		step;

	diff.x = round (to.x) - round (from.x);
	diff.y = round (to.y) - round (from.y);
	if (fabs(diff.x) >= fabs(diff.y))
		step = fabs(diff.x);
	else
		step = fabs(diff.y);
	inc.x = diff.x / step;
	inc.y = diff.y / step;
	i = 0;
	while (i <= step)
	{
		t_image_update_pixel(image, round (from.x), round (from.y), color);
		from.x += inc.x;
		from.y += inc.y;
		i++;
	}
}

void	get_cf_color(t_data *data)
{
	t_color	crgb;
	t_color	frgb;

	crgb = data->scene_info.ceiling_color;
	frgb = data->scene_info.floor_color;
	data->ceiling = (crgb.r << 16 | crgb.g << 8 | crgb.b);
	data->floor = (frgb.r << 16 | frgb.g << 8 | frgb.b);
}

int	game_loop(t_data *data)
{
	t_ray	ray;
	float	angle;
	int		i;

	handle_input(data, deg_to_rad(data->player.angle));
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	put_bgd(&data->scene_layer, data->ceiling, data->floor);
	angle = data->player.angle - (FOV / 2);
	angle -= 360 * (angle > 360);
	angle += 360 * (angle < 0);
	i = 0;
	while (i < WIN_WIDTH)
	{
		ray.angle = angle;
		send_ray(&ray);
		put_wall(data, i, &ray);
		angle += (float) FOV / WIN_WIDTH;
		i++;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr,
		data->scene_layer.img_ptr, 0, 0);
	return (0);
}

void	run_game(t_data *data)
{
	t_vector	map_size;

	map_size.x = data->scene_info.map_xsize * TILE_SIZE;
	map_size.y = data->scene_info.map_ysize * TILE_SIZE;
	data->scene_layer = t_image_create(WIN_WIDTH, WIN_HEIGHT, 0xffffffff);
	init_player(data);
	data->texture_ea = t_image_load_xpm(data->scene_info.east_texture);
	data->texture_we = t_image_load_xpm(data->scene_info.west_texture);
	data->texture_so = t_image_load_xpm(data->scene_info.south_texture);
	data->texture_no = t_image_load_xpm(data->scene_info.north_texture);
	get_cf_color(data);
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYDOWN, 0, ev_key_down, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYUP, 0, ev_key_up, data);
	mlx_hook(data->mlx.window_ptr, ON_DESTROY, 0, ev_destroy, data);
	mlx_loop(data->mlx.mlx_ptr);
}
