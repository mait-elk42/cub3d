/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/31 18:54:12 by aabouqas         ###   ########.fr       */
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
			while (y < 25)
			{
				int	x = 0;
				while (x < 25)
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
			j.x+= 25;
		}
		i.y++;
		j.y+= 25;
	}
}

int	game_loop(t_data *data)
{
	printf("[%c x : %d | y : %d]\n", data->maps[data->pp.y][data->pp.x], data->pp.x, data->pp.y);
	if (data->keys.w.pressed == true)
	{
		if (data->player.pos.y % 25 == 0 && data->maps[data->pp.y - 1][data->pp.x] == '0')
			data->pp.y--;
		if (data->maps[data->pp.y - 1][data->pp.x] == '0')
			data->player.pos.y--; 
	}
	if (data->keys.a.pressed == true)
	{
		if (data->player.pos.x % 25 == 0 && data->maps[data->pp.y][data->pp.x - 1] == '0')
			data->pp.x--;
		if (data->maps[data->pp.y][data->pp.x - 1] == '0')
			data->player.pos.x--;
	}
	if (data->keys.s.pressed == true)
	{
		if (data->player.pos.y % 25 == 0 && data->maps[data->pp.y + 1][data->pp.x] == '0')
			data->pp.y++;
		if (data->maps[data->pp.y + 1][data->pp.x] == '0')
			data->player.pos.y++;
	}
	if (data->keys.d.pressed == true)
	{
		if (data->player.pos.x % 25 == 0 && data->maps[data->pp.y][data->pp.x + 1] == '0')
			data->pp.x++;
		if (data->maps[data->pp.y][data->pp.x + 1] == '0')
			data->player.pos.x++;
	}
	printf("player in : x%d y%d\n", data->player.pos.x, data->player.pos.y);
	print_2d(data->maps);
	put_maps(data->maps, data->mlx);
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->maps_image->img_ptr, 0, 0);
	t_image_update_pixel(data->player.texture, 13 , 13, 0xffffff);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->player.texture->img_ptr, data->player.pos.x, data->player.pos.y);
	int k = 0;
	while (k < 50)
	{
		if (k % 25 == 0)
		{
			// printf("found special place :) [%c]\n", data->maps[data->player.pos.y /25][data->player.pos.x /25]);
			mlx_pixel_put(data->mlx.mlx_ptr, data->mlx.window_ptr, data->player.pos.x + (data->player.texture->sizex / 2), data->player.pos.y -k + (data->player.texture->sizey / 2), 0xffff00);
		}
		else
		{
			mlx_pixel_put(data->mlx.mlx_ptr, data->mlx.window_ptr, data->player.pos.x + (data->player.texture->sizex / 2), data->player.pos.y -k + (data->player.texture->sizey / 2), 0xff0000);
		}
		k++;
	}
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
	return (0);
}

void	run_game(t_data *data)
{
	t_vector	pplr;

	pplr = get_player_pos(data);
	data->pp = get_player_pos(data);
	data->maps[pplr.y][pplr.x] = '0';
	data->maps_image = t_image_create(data->scene_info.maps_xsize * 25
								,data->scene_info.maps_ysize * 25
								, 0x111111);
	data->player.texture = t_image_create(25, 25, 0x00ff00);
	data->player.pos = (t_vector){pplr.x * 25, pplr.y * 25};
	data->player.dir = (t_vector){0, 0};
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYDOWN, 0, key_down, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYUP, 0, key_up, data);
	mlx_loop(data->mlx.mlx_ptr);
}
