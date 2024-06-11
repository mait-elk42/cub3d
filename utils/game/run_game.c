/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/06/11 15:05:02 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_line(t_vector2 from, t_vector2 to)
{
	t_vector2	diff;
	double		step;

	diff.x = to.x - from.x;
	diff.y = to.y - from.y;
	if (fabs(diff.x) > fabs(diff.y))
		step = fabs(diff.x);
	else
		step = fabs(diff.y);
	double xinc = diff.x / step;
	double yinc = diff.y / step;
	int i = 0;
	while (i <= step)
	{
		t_image_update_pixel(&data_hook(NULL)->minimaps_layer, round(from.x), round(from.y), RGB_CYAN);
		from.x += xinc;
		from.y += yinc;
		i++;
	}
}

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
					else if (maps[i.y][i.x] == '0' || maps[i.y][i.x] == 'P')
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

void	init_ray_side(t_ray *ray, double stepx, double stepy, int hori)
{
	double	xdiff;
	double	ydiff;

	(void)stepx;
	(void)stepy;
	(void)ray;
	(void)hori;
	(void)xdiff;
	(void)ydiff;
	// #error debugging here :)

	if (ray->hit_wall.x > ray->hit_wall.y)
	{
		ray->side = EAST;
	}else
		ray->side = UNKNOWN;
	xdiff = ray->hit_wall.x - (floor(ray->hit_wall.x));
	ydiff = ray->hit_wall.y - (floor(ray->hit_wall.y));
	// printf("\033[H\033[2Jinformations : \n \
	// stepx\t: %f \n \
	// stepy\t: %f \n \
	// hit_x\t: %f \n \
	// hit_y\t: %f\n \
	// diffx\t: %f \n \
	// diffy\t: %f \n",
	// stepx, stepy, ray->hit_wall.x, ray->hit_wall.y, xdiff, ydiff);
	// printf("<%s>\n", (ray->hit_wall.x > ray->hit_wall.y) ? "more than" : "less than");
}

//
// void	send_ray2(double angle, int color, t_ray *ray_)
// {
// 	t_data		*data;
// 	double		step_x;
// 	double		step_y;
// 	t_vector2	ray_dir;
// 	data = data_hook(NULL);
// 	ray_dir = (t_vector2){ray_->hit_wall.x, ray_->hit_wall.y};
// 	step_x = cos(mth_degtorad(angle));
// 	step_y = sin(mth_degtorad(angle));
// 	while (1)
// 	{
// 		t_image_update_pixel(&data->minimaps_layer, ray_dir.x, ray_dir.y, color);
// 		ray_dir.x += step_x;
// 		ray_dir.y += step_y;
// 		if (sqrt(pow(ray_->hit_wall.x - ray_dir.x, 2) + pow(ray_->hit_wall.y - ray_dir.y, 2)) >= 15)
// 			break;
// 	}
// 	if (angle < 360)
// 		send_ray2(angle + 90, color, ray_);
// }

t_ray	send_ray(double angle, int color)
{
	t_data		*data;
	t_vector	pp;
	t_ray		ray;
	double		step_x;
	double		step_y;
	t_vector2	ray_dir;
	char		**map;

	data = data_hook(NULL);
	pp.x = (int)data->player.cam_pos.x / 20;
	pp.y = (int)data->player.cam_pos.y / 20;
	map = data->maps;
	ray_dir = (t_vector2){data->player.cam_pos.x, data->player.cam_pos.y};
	step_x = cos(mth_degtorad(angle)) * 0.2;
	step_y = sin(mth_degtorad(angle)) * 0.2;
	int	x;
	int	y;
	// printf("[%f]\n", data->player.angle);
	while (1)
	{
		x = (int)ray_dir.x / MINIMAP_TILE;
		y = (int)ray_dir.y / MINIMAP_TILE;
		if (map[y][x] == '0' && pp.x != x && pp.y != y)
		{
			if (angle >= 270 && angle <= 360 && map[y][x - 1] == '1' && map[y + 1][x] == '1' && map[y + 1][x - 1] == '0')
				break;
			if (angle >= 90 && angle <= 180 && map[y - 1][x] == '1' && map[y][x + 1] == '1' && map[y - 1][x + 1] == '0')
				break;
			if (angle >= 0 && angle <= 90 && map[y - 1][x] == '1' && map[y][x - 1] == '1' && map[y - 1][x - 1] == '0')
				break;
			if (angle >= 180 && angle <= 270 && map[y + 1][x] == '1' && map[y][x + 1] == '1' && map[y + 1][x + 1] == '0')
				break;
		}
		// if (((int)ray_dir.x % MINIMAP_TILE == 0 || (int)ray_dir.y % MINIMAP_TILE == 0) &&
		if (map[y][x] == '1')
			break ;
		t_image_update_pixel(&data->minimaps_layer, ray_dir.x, ray_dir.y, color);
		ray_dir.x += step_x;
		ray_dir.y += step_y;
	}
	ray.hit_wall = ray_dir;
	ray.distance = sqrt(pow(data->player.cam_pos.x - ray_dir.x, 2) + pow(data->player.cam_pos.y - ray_dir.y, 2));
	// init_ray_side(&ray, step_x, step_y, hori);
	// printf("%d\n", hori);
	// send_ray2(0, 0x000000, &ray);
	ray.distance *= cos(mth_degtorad(angle - data->player.angle));
	return (ray);
}

void	put_player_shape(int size)
{
	t_data		*data;
	t_vector2	v1;
	t_vector2	v2;
	t_vector2	v3;
	
	data = data_hook(NULL);

	v1.x = cos(mth_degtorad(data->player.angle)) * size + data->player.cam_pos.x;
	v1.y = sin(mth_degtorad(data->player.angle)) * size + data->player.cam_pos.y;

	v2.x = cos(mth_degtorad(data->player.angle + 120)) * size + data->player.cam_pos.x;
	v2.y = sin(mth_degtorad(data->player.angle + 120)) * size + data->player.cam_pos.y;

	v3.x = cos(mth_degtorad(data->player.angle + 270)) * size + data->player.cam_pos.x;
	v3.y = sin(mth_degtorad(data->player.angle + 270)) * size + data->player.cam_pos.y;

	draw_line(v1, v2);
	// draw_line(v1, v3);
	draw_line(v1, v3);
}

bool	is_collided_wall(t_data	*data, t_vector2 npos)
{
	npos.x = floor((npos.x / MINIMAP_TILE));
	npos.y = floor((npos.y / MINIMAP_TILE));
	return (data->maps[(int)npos.y][(int)npos.x] == '1');
}

// #error working in collition :)
void	handle_input(t_data *data, double radi)
{
	char		**maps;
	t_vector2	new_pos;

	new_pos = data->player.cam_pos;
	maps = data->maps;
	if (data->keys.w.pressed == true)
	{
		new_pos.x += cos(radi) * PLAYER_SPEED;
		new_pos.y += sin(radi) * PLAYER_SPEED;
	}
	if (data->keys.s.pressed == true)
	{
		new_pos.x -= cos(radi) * PLAYER_SPEED;
		new_pos.y -= sin(radi) * PLAYER_SPEED;
	}
	if (data->keys.d.pressed == true)
	{
		new_pos.x -= sin(radi) * PLAYER_SPEED;
		new_pos.y += cos(radi) * PLAYER_SPEED;
	}
	if (data->keys.a.pressed == true)
	{
		new_pos.x += sin(radi) * PLAYER_SPEED;
		new_pos.y -= cos(radi) * PLAYER_SPEED;
	}
	if (is_collided_wall(data, new_pos) == false)
	{
		data->player.cam_pos.x = new_pos.x;
		data->player.cam_pos.y = new_pos.y;
	}
	data->player.angle -= (data->keys.left.pressed == true) * PLAYER_SPEED;
	data->player.angle += (data->keys.right.pressed == true) * PLAYER_SPEED;
	// data->player.top_down += (data->keys.up.pressed == true) * CAM_SENS * 10;
	// data->player.top_down -= (data->keys.down.pressed == true) * CAM_SENS * 10;
	if (data->player.angle > 360 || data->player.angle < 0)
		data->player.angle = 360 * (data->player.angle < 0);
}
// # error there two errors : 1:{Raycasting rendering - wall's edge crossing issue} , 2{the wall is too bad like a circle}

int	get_color_distance(t_ray ray)
{
	unsigned char	r,g,b;

	if ((ray.distance / 20) < 1)
		ray.distance = 1;
	r = 0;
	g = 255;
	b = 0;
	if (ray.side == EAST)
	{
		r = 255;
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
	if (angle < 0)
		angle = 360 - (30 - data->player.angle);
	// int rayscount = 0;
	int i = 0;
	while (i < WIN_WIDTH)
	{
		if (i == WIN_WIDTH / 2 || 1)
		{
			t_ray ray = send_ray(angle, 0xff0000);
			// printf("side : %s\n", (ray.side == NORTH) ? "North" : ((ray.side == SOUTH) ? "SOUTH" : ((ray.side == EAST) ? "EAST" : ((ray.side == WEST) ? "WEST" : "UNKNOWN"))));
			if (ray.distance > 0)
			{
				int wallHeight = (WIN_HEIGHT / ray.distance) * MINIMAP_TILE;
				int	top = (WIN_HEIGHT / 2) - (wallHeight / 2);
				int btm = top + wallHeight;
				if (top < 0)
					top = 0;
				if (btm > WIN_HEIGHT)
					btm = WIN_HEIGHT;
				int y = 0;
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
		// if (angle > 360)
		// 	angle = 0;
		i++;
	}
	// put_player_shape(MINIMAP_TILE / 3);
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
	data->scene_layer = t_image_create(WIN_WIDTH, WIN_HEIGHT, 0xffffffff);
	data->minimaps_layer = t_image_create(data->scene_info.maps_xsize * MINIMAP_TILE, data->scene_info.maps_ysize * MINIMAP_TILE, 0xffffffff);
	init_player(data);
	init_keys(data);
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYDOWN, 0, ev_key_down, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYUP, 0, ev_key_up, data);
	mlx_loop(data->mlx.mlx_ptr);
}
