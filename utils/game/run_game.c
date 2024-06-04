/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/06/04 16:25:31 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_vector	get_player_pos(t_data *data)
{
	t_vector	v;

	v.y = 0;
	while (data->maps[v.y])
	{
		v.x = 0;
		while (data->maps[v.y][v.x])
		{
			if (safe_strchr("NEWS", data->maps[v.y][v.x]))
			{
				data->maps[v.y][v.x] = '0';
				return ((t_vector){.x = v.x, .y = v.y});
			}
			v.x++;
		}
		v.y++;
	}
	return ((t_vector){-1, -1});
}

void	put_maps(char **maps, t_mlx mlx)
{
	t_vector	i;
	t_vector	j;

	i.y = 0;
	j.y = 0;
	(void)mlx;
	while (maps[i.y])
	{
		i.x = 0;
		j.x = 0;
		while (maps[i.y][i.x])
		{
			int	y = 0;
			while (y < 26)
			{
				int	x = 0;
				while (x < 26)
				{
					if (maps[i.y][i.x] == '1')
						t_image_update_pixel(&data_hook(NULL)->minimaps_layer, j.x + x, j.y + y, 0x0000ff);
					else if (maps[i.y][i.x] == '0' || safe_strchr("NSEW", maps[i.y][i.x]))
						t_image_update_pixel(&data_hook(NULL)->minimaps_layer, j.x + x, j.y + y, 0xffffff);
					x++;
				}
				y++;
			}
			i.x++;
			j.x+= 26;
		}
		i.y++;
		j.y+= 26;
	}
}

int	put_line_in(t_vector from, t_vector to, int color)
{
	t_mlx	mlx;
	int dx = abs(to.x - from.x);
	int dy = abs(to.y - from.y);
	int sx = from.x < to.x ? 1 : -1;
	int sy = from.y < to.y ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	(void)color;
	int	line_length = 0;
	mlx = data_hook(NULL)->mlx;
	while (1)
	{
		if (from.y < data_hook(NULL)->minimaps_layer.sizey && from.x < data_hook(NULL)->minimaps_layer.sizex)
		{
			if (data_hook(NULL)->maps[from.y / 26][from.x / 26] == '1')
			{
				// printf("%c\n", data_hook(NULL)->maps[from.y / 26][from.x / 26]);
				t_image_update_pixel(&data_hook(NULL)->minimaps_layer, from.x, from.y, 0xff0000);
				return (line_length);
			}
			t_image_update_pixel(&data_hook(NULL)->minimaps_layer, from.x, from.y, color);
		}
		if (from.x == to.x && from.y == to.y)
			return (-1);
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			from.x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			from.y += sy;
		}
		line_length++;
	}
	return (0);
}

int	send_ray_from(t_vector from, double rad, int color)
{
	t_data		*data;
	t_vector	to;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;

	int	line_length = 0;
	data = data_hook(NULL);
	to.x = (double)(cos(rad) * 2) + data->player.cam_pos.x;
	to.y = (double)(sin(rad) * 2) + data->player.cam_pos.y;
	
	dx = abs(to.x - from.x);
	dy = abs(to.y - from.y);
	if (from.x < to.x)
		sx = 1;
	else
		sx = -1;
	if (from.y < to.y)
		sy = 1;
	else
		sy = -1;
	if (dx > dy)
		err = dx / 2;
	else
		err = -dy / 2;
	// err = (dx > dy ? dx : -dy) / 2;
	while (1)
	{
		// protect sug fault ray out of bounds
		if (from.y < 0 || from.x < 0 || from.y > data->minimaps_layer.sizey -1 || from.x > data->minimaps_layer.sizex -1)
			return (-1);
		if (data->maps[from.y / 26][from.x / 26] == '0')
			t_image_update_pixel(&data->minimaps_layer, from.x, from.y, 0x00ff00);
		// if (data->maps[from.y / 26][from.x / 26] == '1')
		// {
		// 	printf("       %c  \n", data->maps[from.y / 26][from.x / 26]);
		// 	return (line_length);
		// }
		t_image_update_pixel(&data->minimaps_layer, from.x, from.y, color);
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			from.x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			from.y += sy;
		}
		line_length++;
	}
	return (0);
}

void	put_line_in_cus(t_vector from, t_vector to, int color, t_image *img)
{
	t_mlx	mlx;
	int dx = abs(to.x - from.x);
	int dy = abs(to.y - from.y);
	int sx = from.x < to.x ? 1 : -1;
	int sy = from.y < to.y ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	mlx = data_hook(NULL)->mlx;
	while (1)
	{
		if (from.y < img->sizey && from.x < img->sizex)
			t_image_update_pixel(img, from.x, from.y, color);
		if (from.x == to.x && from.y == to.y)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			from.x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			from.y += sy;
		}
	}
}

void	put_player_shape(t_image *minimap_layer, int color, double size)
{
	t_vector	plr_pos;
	t_vector	ang1;
	t_vector	ang2;
	t_vector	ang3;
	double		plr_angle;


	plr_angle = data_hook(NULL)->angle;
	plr_pos = data_hook(NULL)->player.cam_pos;
	ang1.x = plr_pos.x + (cos(mth_degtorad(plr_angle)) * size);
	ang1.y = plr_pos.y + (sin(mth_degtorad(plr_angle)) * size);

	ang2.x = plr_pos.x + (cos(mth_degtorad(120 + plr_angle)) * size);
	ang2.y = plr_pos.y + (sin(mth_degtorad(120 + plr_angle)) * size);

	ang3.x = plr_pos.x + (cos(mth_degtorad(240 + plr_angle)) * size);
	ang3.y = plr_pos.y + (sin(mth_degtorad(240 + plr_angle)) * size);

	put_line_in_cus(ang1, ang2, color, minimap_layer);
	// put_line_in_cus(ang2, ang3, color, minimap_layer);
	put_line_in_cus(ang3, ang1, color, minimap_layer);
}

int	game_loop(t_data *data)
{
	double radi = mth_degtorad(data->angle);

	if (data->keys.w.pressed == true)
	{
		t_vector2	newpos;
		newpos.x = data->player.pos.x + cos(radi) * 2;
		newpos.y = data->player.pos.y + sin(radi) * 2;
		data->player.pos = newpos;
	}
	if (data->keys.s.pressed == true)
	{
		t_vector2	newpos;
		newpos.x = data->player.pos.x - cos(radi) * 2;
		newpos.y = data->player.pos.y - sin(radi) * 2;
		data->player.pos = newpos;
	}
	if (data->keys.d.pressed == true)
	{
		t_vector2	newpos;
		newpos.x = data->player.pos.x - sin(radi) * 2;
		newpos.y = data->player.pos.y + cos(radi) * 2;
		data->player.pos = newpos;
	}
	if (data->keys.a.pressed == true)
	{
		t_vector2	newpos;
		newpos.x = data->player.pos.x + sin(radi) * 2;
		newpos.y = data->player.pos.y - cos(radi) * 2;
		data->player.pos = newpos;
	}
	if (data->keys.left.pressed == true)
		data->angle -= 2;
	if (data->keys.right.pressed == true)
		data->angle += 2;
	if (data->angle > 360 || data->angle < 0)
		data->angle = 360 * (data->angle < 0);
// # error there two errors : 1:{Raycasting rendering - wall's edge crossing issue} , 2{the left wall is soo bad like a circle}
	// printf("player in : x%d y%d\n", data->player.pos.x, data->player.pos.y);
	// print_2d(data->maps);
	data->player.cam_pos = (t_vector){data->player.pos.x + (13)
								, data->player.pos.y + (13)};
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	t_image_clear_color(&data->scene_layer, 0x000000);
	t_image_clear_color(&data->minimaps_layer, 0x00ff00);
	put_maps(data->maps, data->mlx);
	// double o = -30;
	// while (o < 30)
	// {
		send_ray_from (data->player.cam_pos, mth_degtorad(data->angle), 0xff0000);
		// put_line_in((t_vector){data->player.cam_pos.x , data->player.cam_pos.y}, (t_vector){(cos(mth_degtorad(data->angle)) * 50) + data->player.cam_pos.x, (sin(mth_degtorad(data->angle)) * 50) + data->player.cam_pos.y},  0xff0000);
		// printf("pixel : %f\n", length);
		// printf("angle : %f\n", data->angle);
		// if (length > 0)
		// {
		// 	int max = WIN_SIZEY - (length * 2);
		// 	int color = 0x0000ff * (1.0 - length / (double)max);
		// 	int m = 0;
		// 	length = length * cos(radians);
		// 	while (m < 1)
		// 	{
		// 		int j = (length * 2);
		// 		while (max - length > j)
		// 		{
		// 			t_image_update_pixel(&data->scene_layer, m + (o * 26), j, color);
		// 			j++;
		// 		}
		// 		m++;
		// 	}
		// }
		// o += (double)60 / WIN_SIZEX;
		// o += 1;
	// }
	double n = 0;
	while (n <= 10)
	{
		put_player_shape(&data->minimaps_layer, RGB_DARK, n);
		n += 0.1;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->scene_layer.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->minimaps_layer.img_ptr, 0, 0);
	return (0);
}

int	mouse(int btn, int x, int y, void *param)
{
	t_data	*data;
	(void)x;
	(void)btn;

	data = (t_data *)param;
	if (y < 0)
	{
		data->keys.a.pressed = false;
		data->keys.s.pressed = false;
		data->keys.d.pressed = false;
		data->keys.w.pressed = false;
		data->keys.up.pressed = false;
		data->keys.down.pressed = false;
		data->keys.left.pressed = false;
		data->keys.right.pressed = false;
	}
	return (0);
}

int key_up(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys.w.pressed = false;
	if (keycode == KEY_A)
		data->keys.a.pressed = false;
	if (keycode == KEY_S)
		data->keys.s.pressed = false;
	if (keycode == KEY_D)
		data->keys.d.pressed = false;
	if (keycode == KEY_UP)
		data->keys.up.pressed = false;
	if (keycode == KEY_DOWN)
		data->keys.down.pressed = false;
	if (keycode == KEY_LEFT)
		data->keys.left.pressed = false;
	if (keycode == KEY_RIGHT)
		data->keys.right.pressed = false;
	return (0);
}


int key_down(int keycode, t_data *data)
{
	(void)data;
	if (keycode == KEY_ESC)
		safe_exit(0);
	// printf("pressed key : %d\n", keycode);
	if (keycode == KEY_W)
		data->keys.w.pressed = true;
	if (keycode == KEY_A)
		data->keys.a.pressed = true;
	if (keycode == KEY_S)
		data->keys.s.pressed = true;
	if (keycode == KEY_D)
		data->keys.d.pressed = true;
	if (keycode == KEY_UP)
		data->keys.up.pressed = true;
	if (keycode == KEY_DOWN)
		data->keys.down.pressed = true;
	if (keycode == KEY_LEFT)
		data->keys.left.pressed = true;
	if (keycode == KEY_RIGHT)
		data->keys.right.pressed = true;
	return (0);
}

void	run_game(t_data *data)
{
	t_vector	pplr;
	t_vector	map_size;

// # error make one image only and update it layer 1 : the scene, layer 2 : the maps, layer 3 : the player , layer 4 : the player raycasts :) 
	pplr = get_player_pos(data);
	data->pp = pplr;
	map_size.x = data->scene_info.maps_xsize * 26;
	map_size.y = data->scene_info.maps_ysize * 26;
	data->scene_layer =  t_image_create(WIN_WIDTH, WIN_HEIGHT, 0xffffffff);
	data->minimaps_layer =  t_image_create(data->scene_info.maps_xsize * 26, data->scene_info.maps_ysize * 26, 0xffffffff);
	data->player.pos = (t_vector2){pplr.x * 26, pplr.y * 26};
	data->angle = 0;
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYDOWN, 0, key_down, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYUP, 0, key_up, data);
	mlx_mouse_hook(data->mlx.window_ptr, mouse, data);
	mlx_loop(data->mlx.mlx_ptr);
}
