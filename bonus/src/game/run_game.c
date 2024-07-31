/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/31 17:57:14 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

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

void	normalize_sensibility(void)
{
	t_data	*data;

	data = data_hook(NULL);
	if (data->mouse.cam_sens_h > 15.0)
		data->mouse.cam_sens_h -= 10.0;
	else if (data->mouse.cam_sens_h > 10.0)
		data->mouse.cam_sens_h -= 2.0;
	else if (data->mouse.cam_sens_h > 0.0)
		data->mouse.cam_sens_h -= 0.4;
	else if (data->mouse.cam_sens_h <= 0.0)
		data->mouse.cam_sens_h = 0;
	if (data->mouse.cam_sens_v > 0.0)
		data->mouse.cam_sens_v -= 0.5;
	else if (data->mouse.cam_sens_v > 5.0)
		data->mouse.cam_sens_v -= 5;
	else if (data->mouse.cam_sens_v <= 0.0)
		data->mouse.cam_sens_v = 0;
}

int	game_loop(t_data *data)
{
	t_ray	ray;
	float	angle;
	int		i;

	handle_input(data, deg_to_rad(data->player.angle));
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	if (data->game_started == false)
		return (show_menu(), 1);
	draw_mini_map();
	angle = data->player.angle - (FOV / 2);
	i = 0;
	while (i < WIN_WIDTH)
	{
		ft_bzero(&ray, sizeof(t_ray));
		ray.angle = angle;
		send_ray(&ray);
		put_wall(data, i++, &ray);
		angle += (float) FOV / WIN_WIDTH;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr,
		data->scene_layer.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr,
		data->minimap_layer.img_ptr,
		(WIN_WIDTH * MPSIZE) / 2, (WIN_WIDTH * MPSIZE) / 2);
	return (normalize_sensibility(), put_weapon(), player_effects(), 0);
}

void	run_game(t_data *data)
{
	t_vector	map_size;
	int			def;

	def = 0xffffffff;
	get_cf_color(data);
	map_size.x = data->scene_info.map_width * TILE_SIZE;
	map_size.y = data->scene_info.map_height * TILE_SIZE;
	data->scene_layer = t_image_create(WIN_WIDTH, WIN_HEIGHT, def);
	data->minimap_layer = t_image_create (WIN_WIDTH * MPSIZE,
			WIN_WIDTH * MPSIZE, def);
	init_player(data);
	data->texture_ea = t_image_loadfromxpm(data->scene_info.east_texture);
	data->texture_we = t_image_loadfromxpm(data->scene_info.west_texture);
	data->texture_so = t_image_loadfromxpm(data->scene_info.south_texture);
	data->texture_no = t_image_loadfromxpm(data->scene_info.north_texture);
	data->texture_door = t_image_loadfromxpm("textures/door.xpm");
	data->select_item.new_game_selected = true;
	data->select_item.cont_ignored = true;
	data->music = false;
	load_menu_images(&data->menu);
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYDOWN, 0, ev_key_down, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYUP, 0, ev_key_up, data);
	mlx_hook(data->mlx.window_ptr, ON_MOUSEMOVE, 0, ev_mouse_moved, data);
	mlx_loop(data->mlx.mlx_ptr);
}
