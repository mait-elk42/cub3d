/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/06/07 21:06:25 by aabouqas         ###   ########.fr       */
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
			while (y < MAP_SIZE)
			{
				int	x = 0;
				while (x < MAP_SIZE)
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
			j.x+= MAP_SIZE;
		}
		i.y++;
		j.y+= MAP_SIZE;
	}
}

double	send_ray(double ray_angle, int color)
{
	t_data		*data;
	double		step_x;
	double		step_y;
	t_vector2	ray_dir;
	bool		wall;

	data = data_hook(NULL);
	ray_dir.x = data->player.cam_pos.x;
	ray_dir.y = data->player.cam_pos.y;
	step_x = cos(mth_degtorad(ray_angle)) * 0.1;
	step_y = sin(mth_degtorad(ray_angle)) * 0.1;
	wall = false;
	size_t	i = 0;
	while (wall == false)
	{
		t_image_update_pixel(&data->minimaps_layer, ray_dir.x, ray_dir.y, color);
		ray_dir.x += step_x;
		ray_dir.y += step_y;
		wall = (data->maps[(int)ray_dir.y / MAP_SIZE][(int)ray_dir.x / MAP_SIZE] == '1');
		i++;
	}
	double distence = sqrt(pow(data->player.cam_pos.x - ray_dir.x, 2) + pow(data->player.cam_pos.y - ray_dir.y, 2));
	distence = distence * cos(mth_degtorad(ray_angle - data->player.angle));
	return distence);
}

void	put_player_shape(t_image *minimap_layer, int color, double size)
{
	t_data		*data;
	double		step_x;
	double		step_y;
	t_vector2	ray_dir;
	t_vector	plr_pos;
	double		plr_angle;

	data = data_hook(NULL);
	plr_angle = data->player.angle;
	plr_pos = data->player.cam_pos;
	int i = 0;
	while (i < 360)
	{
		ray_dir = (t_vector2){plr_pos.x, plr_pos.y};
		step_x = cos(mth_degtorad(plr_angle + i));
		step_y = sin(mth_degtorad(plr_angle + i));
		while (data->maps[(int)ray_dir.y / MAP_SIZE][(int)ray_dir.x / MAP_SIZE] != '1')
		{
			ray_dir.x += step_x;
			ray_dir.y += step_y;
			t_image_update_pixel(minimap_layer, ray_dir.x, ray_dir.y, color);
			if (sqrt(pow(plr_pos.x - ray_dir.x, 2) + pow(plr_pos.y - ray_dir.y, 2)) >= size)
				break;
		}
		i++;
	}
}

void	handle_input(t_data *data, double radi)
{
	if (data->keys.w.pressed == true)
	{
		data->player.pos.x += cos(radi) * SPEED;
		data->player.pos.y += sin(radi) * SPEED;
	}
	if (data->keys.s.pressed == true)
	{
		data->player.pos.x -= cos(radi) * SPEED;
		data->player.pos.y -= sin(radi) * SPEED;
	}
	if (data->keys.d.pressed == true)
	{
		data->player.pos.x -= sin(radi) * SPEED;
		data->player.pos.y += cos(radi) * SPEED;
	}
	if (data->keys.a.pressed == true)
	{
		data->player.pos.x += sin(radi) * SPEED;
		data->player.pos.y -= cos(radi) * SPEED;
	}
	data->player.angle -= (data->keys.left.pressed == true) * 2;
	data->player.angle += (data->keys.right.pressed == true) * 2;
	if (data->player.angle > 360 || data->player.angle < 0)
		data->player.angle = 360 * (data->player.angle < 0);
}
// # error there two errors : 1:{Raycasting rendering - wall's edge crossing issue} , 2{the wall is too bad like a circle}

int	get_color_distance(double distance)
{
	unsigned char	r,g,b;

	if ((distance / 30) < 1)
		distance = 1;
	r = 0 / (distance / 30);
	g = 255 / (distance / 30);
	b = 0 / (distance / 30);
	
	return (0 << 24 | r << 16 | g << 8 | b);
}

int	game_loop(t_data *data)
{
	handle_input(data, mth_degtorad(data->player.angle));
	data->player.cam_pos = (t_vector){data->player.pos.x + (MAP_SIZE / 2), data->player.pos.y + (MAP_SIZE / 2)};
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	// t_image_clear_color(&data->scene_layer, 0xffffffff);
	t_image_clear_color(&data->minimaps_layer, 0xffffffff);
	put_maps(data->maps, data->mlx);
	double ray_angle = data->player.angle - 30;
	// int rayscount = 0;
	double i = 0;
	while (i < WIN_WIDTH)
	{
		if (i == WIN_WIDTH / 2 || 1)
		{
			double distance = send_ray(ray_angle, 0xff0000);
			printf("[%f]\n", distance);
			if (distance > 1)
			{
				int wallHeight = (WIN_HEIGHT / distance) * SCAL;
				int	top = (WIN_HEIGHT / 2) - (wallHeight / 2);
				int walls = top + wallHeight;
				if (top < 0)
					top = 0;
				if (walls > WIN_HEIGHT)
					walls = WIN_HEIGHT;
				int y = 0;
				// printf("%d %f , wall : %f\n",y, ((WIN_HEIGHT / 2) - (wallHeight / 2)), wallHeight);
				while (y < top)
				{
					t_image_update_pixel(&data->scene_layer,i, y, RGB_CYAN);
					y++;
				}
				while (y < walls)
				{
					// t_image_update_pixel(&data->scene_layer, i, y, get_color_distance(distance));
					t_image_update_pixel(&data->scene_layer, i, y, get_color_distance(distance));
					y++;
				}
				while (y < WIN_HEIGHT)
				{
					t_image_update_pixel(&data->scene_layer, i, y, RGB_YELLOW);
					// if ((int) i % 10 == 0 && (int) y % 10 == 0)
					// 	t_image_update_pixel(&data->scene_layer, i, y, RGB_GOLD);
					y++;
				}
			}
		}
		// rayscount++;
		ray_angle += (double) 60 / WIN_WIDTH;
		i++;
	}
	put_player_shape(&data->minimaps_layer, RGB_GREEN, MAP_SIZE / 4);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->scene_layer.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->minimaps_layer.img_ptr, 0, 0);
	return (0);
}

void	run_game(t_data *data)
{
	t_vector	map_size;

	// # error make one image only and update it layer 1 : the scene, layer 2 : the maps, layer 3 : the player , layer 4 : the player raycasts :) 
	map_size.x = data->scene_info.maps_xsize * 10;
	map_size.y = data->scene_info.maps_ysize * 10;
	data->scene_layer = t_image_create(WIN_WIDTH, WIN_HEIGHT, 0xffffffff);
	data->minimaps_layer = t_image_create(data->scene_info.maps_xsize * 10, data->scene_info.maps_ysize * 10, 0xffffffff);
	init_player(data);
	init_keys(data);
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYDOWN, 0, ev_key_down, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYUP, 0, ev_key_up, data);
	mlx_loop(data->mlx.mlx_ptr);
}
