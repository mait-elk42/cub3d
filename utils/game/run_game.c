/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/06/08 12:28:49 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_maps(char **maps, t_image *img_layer)
{
	t_vector	i;
	t_vector	j;

	i.y = 0;
	j.y = 0;
	while (maps[i.y])
	{
		i.x = 0;
		j.x = 0;
		while (maps[i.y][i.x])
		{
			int	y = 0;
			while (y < MINIMAP_TILE)
			{
				//try to draw circle minimap :) using cos, sin and the map
				int	x = 0;
				while (x < MINIMAP_TILE)
				{
					if (maps[i.y][i.x] == '1')
						t_image_update_pixel(img_layer, j.x + x, j.y + y, 0x0000ff);
					else if (maps[i.y][i.x] == '0' || safe_strchr("NSEW", maps[i.y][i.x]))
						t_image_update_pixel(img_layer, j.x + x, j.y + y, 0xffffff);
					x++;
				}
				y++;
			}
			i.x++;
			j.x+= MINIMAP_TILE;
		}
		i.y++;
		j.y+= MINIMAP_TILE;
	}
}

void	init_ray_side(t_ray *ray, double stepx, double stepy)
{
	double	i;
	double	j;

	(void)stepx;
	(void)stepy;
	(void)ray;
	#error debugging here :)
	i = ray->hit_wall.x - ((int)ray->hit_wall.x);
	j = ray->hit_wall.y - ((int)ray->hit_wall.y);
	// printf("i%f j%f\n", i, j);
	if (i > j)
	{
		system("clear");
		printf("i%f j%f\n\r", i, j);
	}
	// if (i > j)
	// {
	// 	ray->side = NORTH;
	// }
	// if (i < j)
	// {
	// 	ray->side = SOUTH;
	// }
}

t_ray	send_ray(double angle, int color)
{
	t_data		*data;
	t_ray		ray;
	double		step_x;
	double		step_y;
	t_vector2	ray_dir;

	data = data_hook(NULL);
	ray_dir = (t_vector2){data->player.cam_pos.x, data->player.cam_pos.y};
	step_x = cos(mth_degtorad(angle));
	step_y = sin(mth_degtorad(angle));
	while (1)
	{
		if (data->maps[(int)ray_dir.y / MINIMAP_TILE][(int)ray_dir.x / MINIMAP_TILE] == '1')
			break;
		t_image_update_pixel(&data->minimaps_layer, ray_dir.x, ray_dir.y, color);
		ray_dir.x += step_x;
		ray_dir.y += step_y;
	}
	ray.hit_wall = ray_dir;
	ray.distance = sqrt(pow(data->player.cam_pos.x - ray_dir.x, 2) + pow(data->player.cam_pos.y - ray_dir.y, 2));
	init_ray_side(&ray, step_x, step_y);
	// distance *= cos(mth_degtorad(angle - data->player.angle));
	return (ray);
}

void	put_player_shape(t_image *minimap_layer, int color, double size)
{
	t_data		*data;
	double		step_x;
	double		step_y;
	t_vector2	ray_dir;
	t_vector2	plr_pos;
	double		plr_angle;

	data = data_hook(NULL);
	plr_angle = data->player.angle;
	plr_pos = data->player.cam_pos;
	int i = 0;
	while (i < 360)
	{
		ray_dir = (t_vector2){data->player.cam_pos.x, data->player.cam_pos.y};
		step_x = cos(mth_degtorad(plr_angle + i));
		step_y = sin(mth_degtorad(plr_angle + i));
		while (1)
		{
			if (data->maps[(int)ray_dir.y / MINIMAP_TILE][(int)ray_dir.x / MINIMAP_TILE] == '1')
				break;
			t_image_update_pixel(minimap_layer, ray_dir.x, ray_dir.y, color);
			ray_dir.x += step_x;
			ray_dir.y += step_y;
			if (sqrt(pow(data->player.cam_pos.x - ray_dir.x, 2) + pow(data->player.cam_pos.y - ray_dir.y, 2)) >= size)
				break;
		}
		i++;
	}
}

void	handle_input(t_data *data, double radi)
{
	if (data->keys.w.pressed == true)
	{
		data->player.cam_pos.x += cos(radi) * PLAYER_SPEED;
		data->player.cam_pos.y += sin(radi) * PLAYER_SPEED;
	}
	if (data->keys.s.pressed == true)
	{
		data->player.cam_pos.x -= cos(radi) * PLAYER_SPEED;
		data->player.cam_pos.y -= sin(radi) * PLAYER_SPEED;
	}
	if (data->keys.d.pressed == true)
	{
		data->player.cam_pos.x -= sin(radi) * PLAYER_SPEED;
		data->player.cam_pos.y += cos(radi) * PLAYER_SPEED;
	}
	if (data->keys.a.pressed == true)
	{
		data->player.cam_pos.x += sin(radi) * PLAYER_SPEED;
		data->player.cam_pos.y -= cos(radi) * PLAYER_SPEED;
	}
	data->player.angle -= (data->keys.left.pressed == true) * CAM_SENS;
	data->player.angle += (data->keys.right.pressed == true) * CAM_SENS;
	if (data->player.angle > 360 || data->player.angle < 0)
		data->player.angle = 360 * (data->player.angle < 0);
}
// # error there two errors : 1:{Raycasting rendering - wall's edge crossing issue} , 2{the wall is too bad like a circle}

int	get_color_distance(t_ray ray)
{
	unsigned char	r,g,b;

	if ((ray.distance / 20) < 1)
		ray.distance = 1;
	if (ray.side == NORTH)
	{
		r = 255;
		g = 0;
		b = 0;
	}
	else
	if (ray.side == SOUTH)
	{
		r = 255;
		g = 255;
		b = 0;
	}else
	{
		r = 0;
		g = 255;
		b = 0;
	}
	r /= (ray.distance / 20);
	g /= (ray.distance / 20);
	b /= (ray.distance / 20);
	
	return (0 << 24 | r << 16 | g << 8 | b);
}

int	game_loop(t_data *data)
{
	handle_input(data, mth_degtorad(data->player.angle));
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	t_image_clear_color(&data->scene_layer, 0xffffffff);
	t_image_clear_color(&data->minimaps_layer, 0xffffffff);
	put_maps(data->maps, &data->minimaps_layer);
	double angle = data->player.angle - 30;
	// int rayscount = 0;
	int i = 0;
	while (i < WIN_WIDTH)
	{
		if (i == WIN_WIDTH / 2 || 0)
		{
			t_ray ray = send_ray(angle, 0xff0000);
			// printf("side : %s\n", (ray.side == NORTH) ? "North" : ((ray.side == SOUTH) ? "SOUTH" : ((ray.side == EAST) ? "EAST" : ((ray.side == WEST) ? "WEST" : "UNKNOWN"))));
			if (ray.distance > 1)
			{
				// int wallHeight = floor ((WIN_HEIGHT / ray.distance) * 30) ;
				int wallHeight = (WIN_HEIGHT / ray.distance) * MINIMAP_TILE;
				// printf("%d\n", wallHeight);
				int	top = (WIN_HEIGHT / 2) - (wallHeight / 2);
				int btm = top + wallHeight;
				if (top < 0)
					top = 0;
				if (btm > WIN_HEIGHT)
					btm = WIN_HEIGHT;
				// printf("ray num %d : %f\n", i, distance);
				int y = 0;
				// while (y < WIN_HEIGHT / distance)
				// {
				// 	t_image_update_pixel(&data->scene_layer, i, y + 100, get_color_distance(distance));
				// 	y++;
				// }
				
				while (y < top)
				{
					t_image_update_pixel(&data->scene_layer, i, y, 0x000055);
					y++;
				}
				// printf("%d %f , wall : %f\n",y, ((WIN_HEIGHT / 2) - (wallHeight / 2)), wallHeight);
				while (y < btm)
				{
					t_image_update_pixel(&data->scene_layer, i, y, get_color_distance(ray));
					y++;
				}
				while (y < WIN_HEIGHT)
				{
					t_image_update_pixel(&data->scene_layer, i, y, 0xffff00);
					y++;
				}
			}
		}
		// rayscount++;
		angle += (double) 60 / WIN_WIDTH;
		i++;
	}
	put_player_shape(&data->minimaps_layer, RGB_GREEN, MINIMAP_TILE / 3);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->scene_layer.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->minimaps_layer.img_ptr, 0, 0);
	return (0);
}

void	run_game(t_data *data)
{
	t_vector	map_size;

	// # layer 1 : the scene, layer 2 : the maps &&  the player && raycasts
	map_size.x = data->scene_info.maps_xsize * MINIMAP_TILE;
	map_size.y = data->scene_info.maps_ysize * MINIMAP_TILE;
	data->scene_layer =  t_image_create(WIN_WIDTH, WIN_HEIGHT, 0xffffffff);
	data->minimaps_layer =  t_image_create(data->scene_info.maps_xsize * MINIMAP_TILE, data->scene_info.maps_ysize * MINIMAP_TILE, 0xffffffff);
	init_player(data);
	init_keys(data);
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYDOWN, 0, ev_key_down, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYUP, 0, ev_key_up, data);
	mlx_loop(data->mlx.mlx_ptr);
}
