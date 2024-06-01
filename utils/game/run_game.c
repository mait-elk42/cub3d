/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/06/01 16:59:44 by aabouqas         ###   ########.fr       */
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
					if (maps[i.y][i.x] == '1')
						t_image_update_pixel(data_hook(NULL)->maps_image, j.x + x, j.y + y, 0x0000ff);
					else if (maps[i.y][i.x] == '0' || safe_strchr("NSEW", maps[i.y][i.x]))
						t_image_update_pixel(data_hook(NULL)->maps_image, j.x + x, j.y + y, 0xffffff);
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

void	put_line_in(t_vector from, t_vector to, int color)
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
		if (from.y % 26 == 0 || from.x % 26 == 0)
		{
			// printf("%c\n", data_hook(NULL)->maps[from.y / 26][from.x / 26]);
			if (data_hook(NULL)->maps[from.y / 26][from.x / 26] == '1')
				break;
			mlx_pixel_put(mlx.mlx_ptr, mlx.window_ptr, from.x, from.y, color);
		}else
			mlx_pixel_put(mlx.mlx_ptr, mlx.window_ptr, from.x, from.y, 0x00ff00);
		if (from.x == to.x && from.y == to.y)
			break;
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

int	game_loop(t_data *data)
{
	if (data->keys.w.pressed == true)
	{
		if (data->player.pos.y % 26 == 0 && data->maps[(data->player.pos.y / 26) - 1][data->player.pos.x / 26] == '1')
			return 0;
		data->player.pos.y--; 
	}
	if (data->keys.a.pressed == true)
	{
		if (data->player.pos.y % 26 == 0 && data->maps[(data->player.pos.y / 26)][(data->player.pos.x / 26) - 1] == '1')
			return 0;
		data->player.pos.x--;
	}
	if (data->keys.s.pressed == true)
	{
		if (data->player.pos.y % 26 == 0 && data->maps[(data->player.pos.y / 26) + 1][data->player.pos.x / 26] == '1')
			return 0;
		data->player.pos.y++;
	}
	if (data->keys.d.pressed == true)
	{
		if (data->player.pos.y % 26 == 0 && data->maps[(data->player.pos.y / 26)][(data->player.pos.x / 26) + 1] == '1')
			return 0;
		data->player.pos.x++;
	}
	
	if (data->keys.left.pressed == true)
	{
		data->angle -= 1;
	}
	if (data->keys.right.pressed == true)
	{
		data->angle += 1;
	}
	// printf("player in : x%d y%d\n", data->player.pos.x, data->player.pos.y);
	// print_2d(data->maps);
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	put_maps(data->maps, data->mlx);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->maps_image->img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->player.texture->img_ptr, data->player.pos.x, data->player.pos.y);
	// t_image	*img = t_image_create(200, 200, 0x000000);
	// while (j < 26)
	// {
	// x2 = x * cos(angle) - y * sin(angle)
	// y2 = x * sin(angle) + y * cos(angle)
	int j = 13;
	int length = -13;
	int k = data->player.pos.y + 13;
	while (1)
	{
		if (k % 26 == 0 && data->maps[k / 26][((data->player.pos.x + j) / 26)] != 'N')
		{
			// printf("found special place :) [%c]\n", data->maps[(k - 26) / 26][(data->player.pos.x + j) / 26]);
			if (data->maps[(k - 26) / 26][(data->player.pos.x + j) / 26] == '1')
				break ;
		}
		// mlx_pixel_put(data->mlx.mlx_ptr, data->mlx.window_ptr, data->player.pos.x + j, k, 0xff0000);
		k--;
		length++;
	}
	double radians = (data->angle * M_PI) / 180.0;
	// double radians = data->angle;
	int tox = data->player.pos.x + j;
	int toy = data->player.pos.y - length;
	int x2 = ((tox * cos(radians)) - (toy * sin(radians)));
	int y2 = ((tox * sin(radians)) + (toy * cos(radians)));
	put_line_in((t_vector){data->player.pos.x + j, data->player.pos.y + j}, (t_vector){x2, y2}, 0xff0000);
	// printf("angle : %f\n", data->angle);
	// put_line_in((t_vector){data->player.pos.x + j, data->player.pos.y + j}, (t_vector){data->player.pos.x + j, data->player.pos.y - length}, 0xff0000);
	// printf("length before is : %d\n", length);
	// 	j++;
	// }
	// mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, img, data->player.pos.x, data->player.pos.y);
	// int k = data->player.pos.y;
	// while (1)
	// {
	// 	if (k % 26 == 0 && data->maps[k /26][((data->player.pos.x + j) / 26)] != 'N')
	// 	{
	// 		printf("found special place :) [%c]\n", data->maps[(k - 26)/ 26][(data->player.pos.x + j) /26]);
	// 		if (data->maps[(k - 26)/ 26][(data->player.pos.x + j) /26] == '1')
	// 			break ;
	// 	}
	// 	else
	// 		// t_image_update_pixel(img, data->player.pos.x + j, k,  0xff0000);
	// 		mlx_pixel_put(data->mlx.mlx_ptr, data->mlx.window_ptr, data->player.pos.x + j, k, 0xff0000);
	// 	k--;
	// }
	return (0);
}

int key_up(int keycode, t_data *data)
{
	(void)data;
	// printf("released key : %d\n", keycode);
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

	pplr = get_player_pos(data);
	data->pp = pplr;
	data->maps_image = t_image_create(data->scene_info.maps_xsize * 26
								,data->scene_info.maps_ysize * 26
								, 0x111111);
	data->player.texture = t_image_create(26, 26, 
	 0x00ff00);
	data->player.pos = (t_vector){pplr.x * 26, pplr.y * 26};
	data->player.dir = (t_vector){0, 0};
	// data->angle = (90 * M_PI) / 180.0;
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYDOWN, 0, key_down, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYUP, 0, key_up, data);
	mlx_loop(data->mlx.mlx_ptr);
}
