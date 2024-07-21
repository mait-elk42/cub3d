/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/21 13:45:41 by aabouqas         ###   ########.fr       */
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

void	menu()
{
	t_data		*data;
	t_image		new_game;
	t_image		exit;
	t_image		logo;
	t_image		cont;
	t_select	select;

	data = data_hook(NULL);
	select = data->select_item;
	logo = t_image_loadfromxpm("textures/cub_logo.xpm");
	if (select.new_game_selected)
		new_game = t_image_loadfromxpm("textures/new_game_selected.xpm");
	else
		new_game = t_image_loadfromxpm("textures/new_game_unselected.xpm");
	if (select.cont_selected)
		cont = t_image_loadfromxpm("textures/continue_selected.xpm");
	else
		cont = t_image_loadfromxpm("textures/continue_unselected.xpm");
	if (select.exit_selected)
		exit = t_image_loadfromxpm("textures/exit_selected.xpm");
	else
		exit = t_image_loadfromxpm("textures/exit_unselected.xpm");
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, logo.img_ptr, (WIN_WIDTH / 2) - 240, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, new_game.img_ptr, (WIN_WIDTH / 2) - 140, (WIN_HEIGHT / 2) - 50);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, cont.img_ptr, (WIN_WIDTH / 2) - 140, (WIN_HEIGHT / 2) + 50);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, exit.img_ptr, (WIN_WIDTH / 2) - 140, (WIN_HEIGHT / 2) + 150);
}

int	game_loop(t_data *data)
{
	t_ray	ray;
	float	angle;
	int		i;

	get_cf_color(data);
	handle_input(data, deg_to_rad(data->player.angle));
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	if (data->game_started == false)
	{
		menu();
		return 0;
	}
	t_image_clear_color(&data->minimaps_layer, 0xffffffff);
	// t_image_clear_color(&data->minimaps_layer, 0xffff00);
	put_bgd(&data->scene_layer, data->ceiling, data->floor);
	draw_mini_map();
	angle = data->player.angle - (FOV / 2);
	i = 0;
	while (i < WIN_WIDTH)
	{
		send_ray(&ray, angle);
		put_wall(data, i, &ray);
		angle += (float) FOV / WIN_WIDTH;
		i++;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr,
		data->scene_layer.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr,
		data->minimaps_layer.img_ptr, (WIN_WIDTH * MPSIZE) / 2, (WIN_WIDTH * MPSIZE) / 2);
	return (0);
}

void	norm_angle()
{
	if (data_hook(NULL)->player.angle > 360)
		data_hook(NULL)->player.angle -= 360;
	if (data_hook(NULL)->player.angle < 0)
		data_hook(NULL)->player.angle += 360;
}

int	mouse_event(int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->mouse.used_mouse = true;
	(void)y;
	if ((x > ((WIN_WIDTH / 2) - 100) && x < ((WIN_WIDTH / 2) + 100) )|| data->player.angle == 90)
	{
		data->mouse.used_mouse = false;
		data->mouse.cam_sens = 1;
		return 0;
	}
	if (x > (int) (WIN_WIDTH / 2))
	{
		data->mouse.to_right = true;
		data->mouse.to_left = false;
		// data->key_pressed.right = true;
		// data->key_pressed.left = false;
	}
	if (x < (int) (WIN_WIDTH / 2))
	{
		data->mouse.to_right = false;
		data->mouse.to_left = true;
		// data->key_pressed.left = true;
		// data->key_pressed.right = false;
	}
	data->mouse.cam_sens += 0.1;
	if (data->mouse.cam_sens > 3.0)
		data->mouse.cam_sens = 1;
	return 0;
}


void	run_game(t_data *data)
{
	t_vector	map_size;

	map_size.x = data->scene_info.maps_xsize * TILE_SIZE;
	map_size.y = data->scene_info.maps_ysize * TILE_SIZE;
	data->scene_layer = t_image_create(WIN_WIDTH,
			WIN_HEIGHT, 0xffffffff);
	// data->minimaps_layer = t_image_create(
	// 		data->screen.width * TILE_SIZE,
	// 		data->screen.height * TILE_SIZE, 0xffffffff);
	data->minimaps_layer = t_image_create(
			WIN_WIDTH * MPSIZE,
			WIN_WIDTH * MPSIZE, 0xffffffff);
	init_player(data);
	data->texture_ea = t_image_loadfromxpm(data->scene_info.east_texture);
	data->texture_we = t_image_loadfromxpm(data->scene_info.west_texture);
	data->texture_so = t_image_loadfromxpm(data->scene_info.south_texture);
	data->texture_no = t_image_loadfromxpm(data->scene_info.north_texture);
	data->select_item.new_game_selected = true;
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYDOWN, 0, ev_key_down, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYUP, 0, ev_key_up, data);
	mlx_hook(data->mlx.window_ptr, ON_MOUSEMOVE, 0, mouse_event, data);
	// mlx_mouse_hook(data->mlx.window_ptr, , data);
	mlx_loop(data->mlx.mlx_ptr);
}
