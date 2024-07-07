/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/07 19:04:48 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_line(t_image *image, int color, t_vector2 from, t_vector2 to)
{
	t_vector2	diff;
	t_vector2	inc;
	float		step;

	diff.x = to.x - from.x;
	diff.y = to.y - from.y;
	if (fabs(diff.x) > fabs(diff.y))
		step = fabs(diff.x);
	else
		step = fabs(diff.y);
	inc.x = diff.x / step;
	inc.y = diff.y / step;
	int i = 0;
	while (i <= step)
	{
		t_image_update_pixel(image, from.x, from.y, color);
		from.x += inc.x;
		from.y += inc.y;
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
			while (y < TILE_SIZE)
			{
				//try to draw circle minimap :) using cos, sin and the map
				int	x = 0;
				while (x < TILE_SIZE)
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
			j.x+= TILE_SIZE;
		}
		i.y++;
		j.y+= TILE_SIZE;
	}
}

float	get_distence(float angle, t_vector2 end)
{
	double		distance;
	t_player	player;

	player = data_hook(NULL)->player;
	distance = sqrt(pow(end.x - player.position.x, 2) + pow(end.y - player.position.y, 2));
	// distance *= cos(deg_to_rad(((angle * 180) / M_PI) - player.angle));
	distance *= cos(deg_to_rad(rad_to_deg(angle) - player.angle));
	return (distance);
}

void	set_ray_side(t_ray *ray, float angle)
{
	ray->facing_down = angle > 0 && angle < M_PI;
	ray->facing_up = angle > M_PI && angle < (M_PI * 2);
	// ray->facing_right = (angle >= 0 && angle <= (M_PI / 2)) || ((angle > ((2 * M_PI) - (M_PI / 2))) && (angle <= (M_PI * 2)));
	ray->facing_right = angle < 0.5 * M_PI || angle > 1.5 * M_PI;
	ray->facing_left = angle > 0.5 * M_PI && angle < (1.5 * M_PI);
}

int	hit_wall_at(t_vector2 cords)
{
	t_vector	grid;
	t_data		*data;

	data = data_hook(NULL);
	grid = (t_vector) {(cords.x / TILE_SIZE), cords.y / TILE_SIZE};
	return (data->maps[grid.y][grid.x] == '1');
}

t_ray	send_horizontal_ray(t_ray *ray, float ray_angle)
{
	t_vector2	player_pos;
	t_data		*data;
	t_vector2	step;
	t_vector2	intersept;
	t_vector2	increase;
	bool		hori_hit;

	hori_hit = false;
	data = data_hook(NULL);
	set_ray_side(ray, ray_angle);
	player_pos = data->player.position;
	intersept.y = floor(player_pos.y / TILE_SIZE) * TILE_SIZE;
	intersept.y += (TILE_SIZE * ray->facing_down);
	step.y = TILE_SIZE;
	step.x = TILE_SIZE / tan(ray_angle);
	if ((ray->facing_left && step.x > 0) || (ray->facing_right && step.x < 0))
		step.x *= -1;
	intersept.x = player_pos.x + (intersept.y - player_pos.y) / tan(ray_angle);
	if (ray->facing_up)
		step.y *= -1;
	increase = intersept;
	while (increase.x > 0 && increase.x < (data->screen.width * TILE_SIZE) && increase.y > 0 && increase.y < (data->screen.height * TILE_SIZE))
	{
		if (hit_wall_at((t_vector2){increase.x, increase.y - (ray->facing_up == true)}))
		{
			hori_hit = true;
			break;
		}
		increase.y += step.y;
		increase.x += step.x;
	}
	if (hori_hit == true)
	{
		ray->horizontal = increase;
		ray->distance = get_distence(ray_angle, ray->horizontal);
	}
	else
	{
		ray->horizontal = (t_vector2){0, 0};
		ray->distance = INT_MAX;
	}
	return(*ray);
}

t_ray	send_virtical_ray(t_ray *ray, float ray_angle)
{
	t_data		*data;
	t_vector2	player_pos;
	t_vector2	step;
	t_vector2	intersept;
	t_vector2	increase;
	bool		vertical_hit;

	data = data_hook(NULL);
	vertical_hit = false;
	player_pos = data->player.position;
	set_ray_side(ray, ray_angle);
	step.x = TILE_SIZE;
	if (ray->facing_left)
		step.x *= -1;
	step.y = TILE_SIZE * tan(ray_angle);
	intersept.x = floor(player_pos.x / TILE_SIZE) * TILE_SIZE;
	if (ray->facing_right)
		intersept.x += TILE_SIZE;
	intersept.y = player_pos.y + (intersept.x - player_pos.x) * tan(ray_angle);
	if ((ray->facing_up && step.y > 0) || (ray->facing_down && step.y < 0))
		step.y *= -1;
	increase = intersept;
	while (increase.x > 0 && increase.x < (data->screen.width * TILE_SIZE) && increase.y > 0 && increase.y < (data->screen.height * TILE_SIZE))
	{
		if (hit_wall_at((t_vector2){increase.x - ray->facing_left, increase.y}))
		{
			vertical_hit = true;
			break;
		}
		increase.y += step.y;
		increase.x += step.x;
	}
	if (vertical_hit == true)
	{
		ray->vertical = increase;
		ray->distance = get_distence(ray_angle, ray->vertical);
	} else
	{
		ray->vertical = (t_vector2) {0, 0};
		ray->distance = INT_MAX;
	}
	return (*ray);
}

void	send_ray(t_ray *ray, double ray_angle)
{
	t_data	*data;
	t_ray	vertical;
	t_ray	horizontal;

	data = data_hook(NULL);
	ft_bzero(ray, sizeof (t_ray));
	ray_angle = deg_to_rad(ray_angle);
	horizontal = send_horizontal_ray(ray, ray_angle);
	vertical = send_virtical_ray(ray, ray_angle);
	// printf("[%f ||| %f]\n", horizontal.distance, vertical.distance);
	if (horizontal.distance < vertical.distance)
	{
		// draw_line(&data->minimaps_layer, RGB_RED, data->player.position, ray->horizontal);
		horizontal.side = HORIZONTAL;
		*ray = horizontal;
		return ;
	}
	// draw_line(&data->minimaps_layer, RGB_RED, data->player.position, ray->vertical);
	vertical.side = VERTICAL;
	*ray = vertical;
}

// t_ray	send_ray(float angle, int color)
// {
// 	t_data		*data;
// 	t_vector	pp;
// 	t_ray		ray;
// 	float		step_x;
// 	float		step_y;
// 	t_vector2	ray_dir;
// 	char		**map;

// 	data = data_hook(NULL);
// 	pp.x = (int)data->player.position.x / TILE_SIZE;
// 	pp.y = (int)data->player.position.y / TILE_SIZE;
// 	map = data->maps;
// 	ray_dir = (t_vector2){data->player.position.x, data->player.position.y};
// 	step_x = cos(deg_to_rad(angle)) * 0.2;
// 	step_y = sin(deg_to_rad(angle)) * 0.2;
// 	int	x;
// 	int	y;
// 	while (1)
// 	{
// 		x = (int)(ray_dir.x) / TILE_SIZE;
// 		y = (int)(ray_dir.y) / TILE_SIZE;
// 		t_image_update_pixel(&data->minimaps_layer, ray_dir.x, ray_dir.y, color);
// 		ray_dir.x += step_x;
// 		ray_dir.y += step_y;
// 		if (map[y][x] == '1' || map[(int)(ray_dir.y) / TILE_SIZE][(int)(ray_dir.x - step_x) / TILE_SIZE] == '1')
// 			break ;
// 	}
// 	ray.hit_wall = ray_dir;
// 	ray.distance = sqrt(pow(data->player.position.x - ray_dir.x, 2) + pow(data->player.position.y - ray_dir.y, 2));
// 	// init_ray_side(&ray, step_x, step_y, hori);
// 	// if (side)
// 	// printf("%d\n", hori);
// 	ray.distance *= cos(deg_to_rad(angle - data->player.angle));
// 	return (ray);
// }



void	put_player_shape(double size)
{
	t_data		*data;
	t_vector2	player_pos;
	t_vector2	p1;
	t_vector2	p2;
	t_vector2	p3;
	
	data = data_hook(NULL);
	player_pos = data->player.position;
	p1.x = cos(deg_to_rad(data->player.angle - 120)) * size + player_pos.x;
	p1.y = sin(deg_to_rad(data->player.angle - 120)) * size + player_pos.y;

	p2.x = cos(deg_to_rad(data->player.angle + 120)) * size + player_pos.x;
	p2.y = sin(deg_to_rad(data->player.angle + 120)) * size + player_pos.y;

	p3.x = cos(deg_to_rad(data->player.angle)) * size + player_pos.x;
	p3.y = sin(deg_to_rad(data->player.angle)) * size + player_pos.y;

	draw_line(&data->minimaps_layer, 0xff0000,p1, p3);
	draw_line(&data->minimaps_layer, 0xff0000,p2, p3);
}

bool	is_collided_wall(t_data	*data, t_vector2 next_pos)
{
	char		**map;
	t_vector	p_pos;
	t_vector	n_pos;

	map = data->maps;
	p_pos.x = (int) (data->player.position.x) / TILE_SIZE;
	p_pos.y = (int) (data->player.position.y) / TILE_SIZE;
	// the following commented part is to add some space between player and the wall
	// if (p_pos.x <= ((n_pos.x) / TILE_SIZE) && p_pos.y <= ((n_pos.y) / TILE_SIZE))
	// {
			// n_pos.x += 10;
			// n_pos.y += 10;
	// }
	n_pos = (t_vector) {next_pos.x / TILE_SIZE, next_pos.y / TILE_SIZE};
	if ((map[(int)n_pos.y][p_pos.x] == '1' && map[p_pos.y][(int)n_pos.x] == '1'))
		return (1);
	return (map[(int) n_pos.y][(int) n_pos.x] == '1');
}

// #error working in collition :)
void	handle_input(t_data *data, float radi)
{
	char		**maps;
	t_vector2	next_pos;

	next_pos = data->player.position;
	maps = data->maps;
	if (data->keys.w.pressed == true)
	{
		next_pos.x += cos(radi) * PLAYER_SPEED;
		next_pos.y += sin(radi) * PLAYER_SPEED;
	}
	if (data->keys.s.pressed == true)
	{
		next_pos.x -= cos(radi) * PLAYER_SPEED;
		next_pos.y -= sin(radi) * PLAYER_SPEED;
	}
	if (data->keys.d.pressed == true)
	{
		next_pos.x -= sin(radi) * PLAYER_SPEED;
		next_pos.y += cos(radi) * PLAYER_SPEED;
	}
	if (data->keys.a.pressed == true)
	{
		next_pos.x += sin(radi) * PLAYER_SPEED;
		next_pos.y -= cos(radi) * PLAYER_SPEED;
	}
	if (is_collided_wall(data, next_pos) == false)
		data->player.position = next_pos;
	data->player.angle -= (data->keys.left.pressed == true) * CAM_SENS;
	data->player.angle += (data->keys.right.pressed == true) * CAM_SENS;
	
	// data->player.top_down += (data->keys.up.pressed == true) * CAM_SENS * 10;
	// data->player.top_down -= (data->keys.down.pressed == true) * CAM_SENS * 10;
	if (data->player.angle >= 360 || data->player.angle < 0)
		data->player.angle = 360 * (data->player.angle < 0);
}

// # error there two errors : 1:{Raycasting rendering - wall's edge crossing issue} , 2{the wall is too bad like a circle}

int	get_color_distance(t_ray ray)
{
	unsigned char	r,g,b;

	if ((ray.distance / TILE_SIZE) < 1)
		ray.distance = 1;
	r = 0;
	g = 255;
	b = 0;
	// if (ray.side == HORIZONTAL)
	// {
	// 	r = 255;
	// 	g = 255;
	// 	b = 0;
	// }
	r /= (ray.distance / TILE_SIZE);
	g /= (ray.distance / TILE_SIZE);
	b /= (ray.distance / TILE_SIZE);
	
	return (0 << 24 | r << 16 | g << 8 | b);
}

int	game_loop(t_data *data)
{
	handle_input(data, deg_to_rad(data->player.angle));
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	if (data->game_started == false)
	{
		data->keys.left.pressed = true;
		data->keys.d.pressed = true;
		splash_screen(data);
		return (0);
	}
	t_image_clear_color(&data->minimaps_layer, 0xffffffff);
	t_image_clear_color(&data->scene_layer, 0xffffffff);
	put_maps(data->maps, &data->minimaps_layer);
	float angle = data->player.angle - 30;
	// if (angle < 0)
	// 	angle = 360 - (30 - data->player.angle);
	int i = 0;
	while (i < WIN_WIDTH)
	{
		// (i == (WIN_WIDTH - 100) / 2 || i == (WIN_WIDTH + 100) / 2)
		if (1)
		{
			send_ray(&data->rays[i], angle);
			// printf ("[%f]\n", data->rays[i].distance);
			int wallHeight = (WIN_HEIGHT / data->rays[i].distance) * TILE_SIZE;
			int	top = (WIN_HEIGHT / 2) - (wallHeight / 2);
			int btm = top + wallHeight;
			if (btm > WIN_HEIGHT)
				btm = WIN_HEIGHT;
			if (top < 0)
				top = 0;
			if (data->rays[i].side == HORIZONTAL)
				draw_line(&data->scene_layer, RGB_GREEN, (t_vector2) {i, top + 1}, (t_vector2) {i, btm - 1});
			else
				draw_line(&data->scene_layer, RGB_DARK_GREEN, (t_vector2) {i, top + 1}, (t_vector2) {i, btm - 1});
		}
		angle += (float) 60 / WIN_WIDTH;
		i++;
	}
	double size = 1;
	while (size <= 10)
	{
		put_player_shape(size);
		size++;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->scene_layer.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->minimaps_layer.img_ptr, 0, 0);
	return (0);
}

void	run_game(t_data *data)
{
	t_vector	map_size;

	// # layer 1 : the scene, layer 2 : the maps &&  the player && raycasts
	map_size.x = data->scene_info.maps_xsize * TILE_SIZE;
	map_size.y = data->scene_info.maps_ysize * TILE_SIZE;
	data->scene_layer = t_image_create(WIN_WIDTH, WIN_HEIGHT, 0xffffffff);
	data->minimaps_layer = t_image_create(data->screen.width * TILE_SIZE, data->screen.height * TILE_SIZE, 0xffffffff);
	init_player(data);
	init_keys(data);
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYDOWN, 0, ev_key_down, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYUP, 0, ev_key_up, data);
	mlx_loop(data->mlx.mlx_ptr);
}
