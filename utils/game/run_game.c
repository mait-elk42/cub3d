/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/06/05 11:23:19 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

double	send_ray(double angle, int color)
{
	t_data		*data;
	double		step_x;
	double		step_y;
	t_vector2	ray_dir;

	data = data_hook(NULL);
	ray_dir = (t_vector2){data->player.cam_pos.x, data->player.cam_pos.y};
	step_x = cos(mth_degtorad(angle));
	step_y = sin(mth_degtorad(angle));
	while (1)
	{
		if (data->maps[(int)ray_dir.y / 26][(int)ray_dir.x / 26] == '1')
			break;
		t_image_update_pixel(&data->minimaps_layer, ray_dir.x, ray_dir.y, color);
		if ((int)ray_dir.y % 26 == 0 || (int)ray_dir.x % 26 == 0)
			t_image_update_pixel(&data->minimaps_layer, ray_dir.x, ray_dir.y, RGB_BRONZE);
		ray_dir.x += step_x;
		ray_dir.y += step_y;
	}
	return (sqrt(pow(data->player.cam_pos.x - ray_dir.x, 2) + pow(data->player.cam_pos.y - ray_dir.y, 2)));
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


	if (size == 0)
		return ;
	plr_angle = data_hook(NULL)->player.angle;
	plr_pos = data_hook(NULL)->player.cam_pos;
	ang1.x = plr_pos.x + (cos(mth_degtorad(plr_angle)) * size);
	ang1.y = plr_pos.y + (sin(mth_degtorad(plr_angle)) * size);

	ang2.x = plr_pos.x + (cos(mth_degtorad(120 + plr_angle)) * size);
	ang2.y = plr_pos.y + (sin(mth_degtorad(120 + plr_angle)) * size);

	ang3.x = plr_pos.x + (cos(mth_degtorad(240 + plr_angle)) * size);
	ang3.y = plr_pos.y + (sin(mth_degtorad(240 + plr_angle)) * size);

	put_line_in_cus(ang1, ang2, color, minimap_layer);
	put_line_in_cus(ang3, ang1, color, minimap_layer);
	put_player_shape(minimap_layer, color, size -1);
}

void	handle_input(t_data *data, double radi)
{
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
	data->player.angle -= (data->keys.left.pressed == true) * 2;
	data->player.angle += (data->keys.right.pressed == true) * 2;
	if (data->player.angle > 360 || data->player.angle < 0)
		data->player.angle = 360 * (data->player.angle < 0);
}
// # error there two errors : 1:{Raycasting rendering - wall's edge crossing issue} , 2{the left wall is soo bad like a circle}

int	game_loop(t_data *data)
{
	handle_input(data, mth_degtorad(data->player.angle));
	data->player.cam_pos = (t_vector){data->player.pos.x + (13)
								, data->player.pos.y + (13)};
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	t_image_clear_color(&data->scene_layer, 0xffffffff);
	t_image_clear_color(&data->minimaps_layer, 0xffffffff);
	put_maps(data->maps, data->mlx);
	// int rayscount = 0;
	double angle = data->player.angle - 30;
	double i = 0;
	while (i < WIN_WIDTH)
	{
#error in the ray of direction and player is different, fix it
		double distance = send_ray(data->player.angle + angle, 0xff0000);
		double wallHeight = floor((WIN_HEIGHT / 2) / distance);
		// printf("pixel %d : %f\n", (int)o, length);
		// printf("angle : %f\n", data->angle);
		// int max = WIN_HEIGHT - length;
		// int color = 0x0000ff;
		// length = length * cos(mth_degtorad(data->angle + o));
		int y = 0;
		while (y < (WIN_HEIGHT / 2) - wallHeight)
		{
			t_image_update_pixel(&data->scene_layer, i, y, RGB_DARK_GREEN);
			y++;
		}
		// while (j < wallHeight)
		// {
		// 	// reset 32 to 26 to make everything clear :)
		// 	t_image_update_pixel(&data->scene_layer, (o * 32) , j, color);
		// 	j++;
		// }
		// while (max + length > j)
		// {
		// 	// reset 32 to 26 to make everything clear :)
		// 	t_image_update_pixel(&data->scene_layer, (o * 32) , j, RGB_BRONZE);
		// 	j++;
		// }
		// rayscount++;
		angle += (double)60 / WIN_WIDTH;
		i++;
	}
	// printf("rays count : %d\n", rayscount);
	put_player_shape(&data->minimaps_layer, RGB_DARK, 10);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->scene_layer.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->minimaps_layer.img_ptr, 0, 0);
	return (0);
}

void	run_game(t_data *data)
{
	t_vector	map_size;

// # error make one image only and update it layer 1 : the scene, layer 2 : the maps, layer 3 : the player , layer 4 : the player raycasts :) 
	map_size.x = data->scene_info.maps_xsize * 26;
	map_size.y = data->scene_info.maps_ysize * 26;
	data->scene_layer =  t_image_create(WIN_WIDTH, WIN_HEIGHT, 0xffffffff);
	data->minimaps_layer =  t_image_create(data->scene_info.maps_xsize * 26, data->scene_info.maps_ysize * 26, 0xffffffff);
	init_player(data);
	init_keys(data);
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYDOWN, 0, ev_key_down, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYUP, 0, ev_key_up, data);
	mlx_loop(data->mlx.mlx_ptr);
}
