/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/30 12:55:52 by aabouqas         ###   ########.fr       */
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
void	normalize_sensibility()
{
	t_data	*data;

	data = data_hook(NULL);
	if (data->mouse.cam_sens > 0.0)
		data->mouse.cam_sens -= 0.5;
	if (data->mouse.cam_sens > 5.0)
		data->mouse.cam_sens -= 0.8;
	if (data->mouse.cam_sens <= 0.0)
		data->mouse.cam_sens = 0;

	if (data->mouse.cam_sens_v > 0.0)
		data->mouse.cam_sens_v -= 0.5;
	if (data->mouse.cam_sens_v > 5.0)
		data->mouse.cam_sens_v -= 5;
	if (data->mouse.cam_sens_v <= 0.0)
		data->mouse.cam_sens_v = 0;
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
		return (show_menu());
	put_bgd(&data->scene_layer, data->ceiling, data->floor);
	draw_mini_map();
	angle = data->player.angle - (FOV / 2);
	i = 0;
	data->looking_door = false;
	while (i < WIN_WIDTH)
	{
		ft_bzero(&ray, sizeof(t_ray));
		ray.angle = angle;
		send_ray(&ray);
		// printf("%f\n", ray.distance);
		put_wall(data, i, &ray);
		// send_ray(&ray, angle);
		angle += (float) FOV / WIN_WIDTH;
		i++;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr,
		data->scene_layer.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr,
		data->minimap_layer.img_ptr, (WIN_WIDTH * MPSIZE) / 2, (WIN_WIDTH * MPSIZE) / 2);
	normalize_sensibility();
	// if (data->Switch == false)
	// 	data->b += 2;
	// else
	// 	data->b -= 2;
	// if (data->b == 0 || data->b == 12)
	// 	data->Switch = data->Switch == false;
	if (data->jumping)
	{
		if (data->jump != 21)
			data->jump += 3;
		if (data->jump == 21)
			data->jumping = false;
	}
	if (data->jumping == false)
	{
		if (data->jump != 0)
			data->jump -= 3;
		if (data->jump == 0)
			data->one_jump = 0;
	}
	printf("[%d]\n", data->jump);
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
	t_data		*data;
	t_vector	mouse_pos;
	int			width_half;
	int			height_half;

	data = (t_data *)param;
	width_half = WIN_WIDTH / 2;
	height_half = WIN_HEIGHT / 2;
	if (y < height_half)
	{
		data->mouse.to_down = false;
		data->mouse.to_up = true;
	}
	if (y > height_half)
	{
		data->mouse.to_down = true;
		data->mouse.to_up = false;
	}
	if (x > width_half)
	{
		data->mouse.to_right = true;
		data->mouse.to_left = false;
	}
	if (x < width_half)
	{
		data->mouse.to_right = false;
		data->mouse.to_left = true;
	}
	data->mouse.cam_sens = fabs((width_half - x) * 0.02);
	data->mouse.cam_sens_v = fabs((height_half - y) * 0.03);
	if (data->mouse.center_mouse)
		mlx_mouse_move(data->mlx.window_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2); 
	return 0;
}


void	run_game(t_data *data)
{
	t_vector	map_size;

	map_size.x = data->scene_info.map_width * TILE_SIZE;
	map_size.y = data->scene_info.map_height * TILE_SIZE;
	data->scene_layer = t_image_create(WIN_WIDTH, WIN_HEIGHT, 0xffffffff);
	data->minimap_layer = t_image_create (
			WIN_WIDTH * MPSIZE,
			WIN_WIDTH * MPSIZE, 0xffffffff);
	init_player(data);
	data->texture_ea = t_image_loadfromxpm(data->scene_info.east_texture);
	data->texture_we = t_image_loadfromxpm(data->scene_info.west_texture);
	data->texture_so = t_image_loadfromxpm(data->scene_info.south_texture);
	data->texture_no = t_image_loadfromxpm(data->scene_info.north_texture);
	data->texture_door = t_image_loadfromxpm("textures/door.xpm");
	data->select_item.new_game_selected = true;
	data->select_item.cont_ignored = true;
	data->music = true;
	load_menu_images(&data->menu);
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYDOWN, 0, ev_key_down, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYUP, 0, ev_key_up, data);
	mlx_hook(data->mlx.window_ptr, ON_MOUSEMOVE, 0, mouse_event, data);
	mlx_loop(data->mlx.mlx_ptr);
}
