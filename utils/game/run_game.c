/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/06/03 18:45:43 by aabouqas         ###   ########.fr       */
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
				return ((t_vector){.x = v.x, .y = v.y});
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
					// if (maps[i.y][i.x] == '1')
					// 	t_image_update_pixel(data_hook(NULL)->maps_image, j.x + x, j.y + y, 0x0000ff);
					// else if (maps[i.y][i.x] == '0' || safe_strchr("NSEW", maps[i.y][i.x]))
					// 	t_image_update_pixel(data_hook(NULL)->maps_image, j.x + x, j.y + y, 0xffffff);
					// x++;
					if (maps[i.y][i.x] == '1')
						t_image_update_pixel(data_hook(NULL)->scene, j.x + x, j.y + y, 0x0000ff);
					else if (maps[i.y][i.x] == '0' || safe_strchr("NSEW", maps[i.y][i.x]))
						t_image_update_pixel(data_hook(NULL)->scene, j.x + x, j.y + y, 0xffffff);
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
		if (from.y < data_hook(NULL)->scene->sizey && from.x < data_hook(NULL)->scene->sizex)
		{
			if (data_hook(NULL)->maps[from.y / 26][from.x / 26] == '1')
			{
				// printf("%c\n", data_hook(NULL)->maps[from.y / 26][from.x / 26]);
				t_image_update_pixel(data_hook(NULL)->scene, from.x, from.y, 0xff0000);
				return (line_length);
			}
			t_image_update_pixel(data_hook(NULL)->scene, from.x + 1, from.y, color);
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

int	game_loop(t_data *data)
{
	double radi = (((data->angle) * M_PI) / 180.0);
	if (data->keys.w.pressed == true)
	{
		data->player.pos.x += cos(radi) * 2;
		data->player.pos.y += sin(radi) * 2;
	}
	if (data->keys.s.pressed == true)
	{
		data->player.pos.x -= cos(radi) * 2;
		data->player.pos.y -= sin(radi) * 2;
	}
	if (data->keys.d.pressed == true)
	{
		data->player.pos.x -= sin(radi) * 2;
		data->player.pos.y += cos(radi) * 2;
	}
	if (data->keys.a.pressed == true)
	{
		data->player.pos.x += sin(radi) * 2;
		data->player.pos.y -= cos(radi) * 2;
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
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	t_image_clear_color(data->scene, RGB_BLACK);
	put_maps(data->maps, data->mlx);
	data->player.cam_pos = (t_vector){data->player.pos.x + (13), data->player.pos.y + (13)};
	double o = -30;
	while (o < 30)
	{
		int viewposx = 300;
		int viewposy = 300;
		double radians = ((data->angle + o) * (M_PI / 180.0));
		int x2 = (cos(radians) * 10000) + data->player.cam_pos.x;
		int y2 = (sin(radians) * 10000) + data->player.cam_pos.y;
		int length = 0;
		length = put_line_in((t_vector){data->player.cam_pos.x , data->player.cam_pos.y}, (t_vector){x2, y2}, RGB_DARK);
		printf("pixel : %d\n", length);
		// printf("angle : %f\n", data->angle);
		int max = 500;
		if (length != -1)
		{
			viewposy += length / 2;
			length = max - length;
			int i = 0;
			while (i < length)
			{
				t_image_update_pixel(data->scene, viewposx + (o * 10), viewposy + i, RGB_DARKRED);
				i++;
			}
		}
		o += 0.1;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->scene->img_ptr, 0, 0);
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
	data->scene =  t_image_create(WIN_SIZEX, WIN_SIZEY, RGB_CYAN);
	data->player.pos = (t_vector2){pplr.x * 26, pplr.y * 26};
	data->angle = 0;
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYDOWN, 0, key_down, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYUP, 0, key_up, data);
	mlx_mouse_hook(data->mlx.window_ptr, mouse, data);
	mlx_loop(data->mlx.mlx_ptr);
}
