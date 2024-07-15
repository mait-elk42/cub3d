/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/15 08:55:29 by mait-elk         ###   ########.fr       */
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
		t_image_update_pixel(image, round(from.x), round(from.y), color);
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

	(void)angle;
	player = data_hook(NULL)->player;
	distance = sqrt(pow(end.x - player.position.x, 2) + pow(end.y - player.position.y, 2));
	distance *= cos(deg_to_rad(((angle * 180) / M_PI) - player.angle));
	return (distance);
}

void	set_ray_side(t_ray *ray, float angle)
{
	ray->facing_down = angle > 0 && angle < M_PI;
	ray->facing_up = angle > M_PI && angle < (M_PI * 2);
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

t_ray	send_horizontal_ray(float ray_angle)
{
	t_data		*data;
	t_ray		ray;
	t_vector2	player_pos;
	t_vector2	step;
	t_vector2	intercept;
	bool		is_wall_hit;

	is_wall_hit = false;
	data = data_hook(NULL);
	set_ray_side(&ray, ray_angle);
	player_pos = data->player.position;
	intercept.y = floor(player_pos.y / TILE_SIZE) * TILE_SIZE;
	intercept.y += (TILE_SIZE * ray.facing_down);
	step.y = TILE_SIZE;
	step.x = TILE_SIZE / tan(ray_angle);
	if ((ray.facing_left && step.x > 0) || (ray.facing_right && step.x < 0))
		step.x *= -1;
	intercept.x = player_pos.x + (intercept.y - player_pos.y) / tan(ray_angle);
	if (ray.facing_up)
		step.y *= -1;
	if (data->maps[(int)player_pos.y / TILE_SIZE][(int)player_pos.x / TILE_SIZE] != '1')
	while (intercept.x > 0 && intercept.x < (data->screen.width * TILE_SIZE) && intercept.y > 0 && intercept.y < (data->screen.height * TILE_SIZE))
	{
		if (hit_wall_at((t_vector2){intercept.x, intercept.y - (ray.facing_up == true)}))
		{
			is_wall_hit = true;
			break;
		}
		intercept.y += step.y;
		intercept.x += step.x;
	}
	ray.intersept_point = intercept;
	if (is_wall_hit == true)
		ray.distance = get_distence(ray_angle, intercept);
	else
		ray.distance = INT_MAX;
	return(ray);
}

t_ray	send_virtical_ray(float ray_angle)
{
	t_data		*data;
	t_ray		ray;
	t_vector2	player_pos;
	t_vector2	step;
	t_vector2	intercept;
	bool		is_wall_hit;

	data = data_hook(NULL);
	is_wall_hit = false;
	player_pos = data->player.position;
	set_ray_side(&ray, ray_angle);
	step.x = TILE_SIZE;
	if (ray.facing_left)
		step.x *= -1;
	step.y = TILE_SIZE * tan(ray_angle);
	intercept.x = floor(player_pos.x / TILE_SIZE) * TILE_SIZE;
	if (ray.facing_right)
		intercept.x += TILE_SIZE;
	intercept.y = player_pos.y + (intercept.x - player_pos.x) * tan(ray_angle);
	if ((ray.facing_up && step.y > 0) || (ray.facing_down && step.y < 0))
		step.y *= -1;
	if (data->maps[(int)player_pos.y / TILE_SIZE][(int)player_pos.x / TILE_SIZE] != '1')
	while (intercept.x > 0 && intercept.x < (data->screen.width * TILE_SIZE) && intercept.y > 0 && intercept.y < (data->screen.height * TILE_SIZE))
	{
		if (hit_wall_at((t_vector2){intercept.x - ray.facing_left, intercept.y}))
		{
			is_wall_hit = true;
			break;
		}
		intercept.y += step.y;
		intercept.x += step.x;
	}
	ray.intersept_point = intercept;
	if (is_wall_hit == true)
		ray.distance = get_distence(ray_angle, ray.intersept_point);
	else
		ray.distance = INT_MAX;
	return (ray);
}

void	send_ray(t_ray *ray, double ray_angle)
{
	t_data	*data;
	t_ray	vertical;
	t_ray	horizontal;

	data = data_hook(NULL);
	ft_bzero(ray, sizeof (t_ray));
	ray_angle = deg_to_rad(ray_angle);
	horizontal = send_horizontal_ray(ray_angle);
	vertical = send_virtical_ray(ray_angle);
	if (horizontal.distance < vertical.distance)
	{
		if (horizontal.facing_up)
			horizontal.direction = NORTH;
		else if (horizontal.facing_down)
			horizontal.direction = SOUTH;
		else
			horizontal.direction = UNKNOWN;
		draw_line(&data->minimaps_layer, RGB_DARK_GREEN, data->player.position, horizontal.intersept_point);
		horizontal.side = HORIZONTAL;
		*ray = horizontal;
		return ;
	}
	draw_line(&data->minimaps_layer, RGB_DARK_GREEN, data->player.position, vertical.intersept_point);
	vertical.side = VERTICAL;
	if (vertical.facing_right)
		vertical.direction = EAST;
	else if (vertical.facing_left)
		vertical.direction = WEST;
	else
		horizontal.direction = UNKNOWN;
	*ray = vertical;
}

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

// bool	is_collided_wall(t_data	*data, t_vector2 axis)
// {
// 	char		**map;
// 	t_vector2	g_player;

// 	g_player = data->player.position;
// 	map = data->maps;

// 	if (map[(int)(g_player.y + (axis.y * 10)) / TILE_SIZE][(int)(g_player.x + (axis.x * 10)) / TILE_SIZE] == '1')
// 		return (true);
// 	if (map[(int)(g_player.y) / TILE_SIZE][(int)(g_player.x + (axis.x * 10)) / TILE_SIZE] == '1'
// 		&& map[(int)(g_player.y + (axis.y * 10)) / TILE_SIZE][(int)(g_player.x) / TILE_SIZE] == '1')
// 		return (true);
// 	return (false);
// }

bool	is_collided_wall(t_data	*data, t_vector2 axis)
{
	bool		mv_x;
	bool		mv_y;
	char		**map;
	t_vector2	g_player;

	g_player = data->player.position;
	map = data->maps;
	bool	is_collided_wall(t_data	*data, t_vector2 axis);
	draw_line(&data->minimaps_layer, 0x00ff00, data->player.position, (t_vector2){data->player.position.x + (axis.x * 20), data->player.position.y + (axis.y * 20)});
	if (map[(int)(g_player.y) / TILE_SIZE][(int)(g_player.x + (axis.x * 5)) / TILE_SIZE] != '1')
	mv_x = false;
	mv_y = false;
	if (map[(int)(g_player.y) / TILE_SIZE][(int)(g_player.x + (axis.x * 10)) / TILE_SIZE] != '1')
	{
		mv_x = true;
		data->player.position.x += axis.x * PLAYER_SPEED;
	}
	if (map[(int)(g_player.y + (axis.y * 10)) / TILE_SIZE][(int)(g_player.x) / TILE_SIZE] != '1')
	{
		mv_y = true;
		data->player.position.y += axis.y * PLAYER_SPEED;
	}
	if (mv_y != mv_x)
	{
		if (mv_x == true)
		{
			if (map[(int)(g_player.y) / TILE_SIZE][(int)(g_player.x + 10) / TILE_SIZE] == '1')
				data->player.position.x -= axis.x * PLAYER_SPEED;
			if (map[(int)(g_player.y) / TILE_SIZE][(int)(g_player.x - 10) / TILE_SIZE] == '1')
				data->player.position.x -= axis.x * PLAYER_SPEED;
		}
		if (mv_y == true)
		{
			if (map[(int)(g_player.y + 10) / TILE_SIZE][(int)(g_player.x) / TILE_SIZE] == '1')
				data->player.position.y -= axis.y * PLAYER_SPEED;
			if (map[(int)(g_player.y - 10) / TILE_SIZE][(int)(g_player.x) / TILE_SIZE] == '1')
				data->player.position.y -= axis.y * PLAYER_SPEED;
		}
	}
	if (map[(int)(g_player.y + (axis.y * 5)) / TILE_SIZE][(int)(g_player.x + (axis.x * 5)) / TILE_SIZE] == '1')
	{
		data->player.position.x -= axis.x * PLAYER_SPEED;
		data->player.position.y -= axis.y * PLAYER_SPEED;
	}
	return (false);
}

void	handle_input(t_data *data, float radi)
{
	char		**maps;
	t_vector2	axis;
	bool		press = false;

	axis = (t_vector2){0,0};
	maps = data->maps;
	if (data->key_pressed.w == true)
	{
		axis.x += cos(radi);
		axis.y += sin(radi);
		press = true;
	}
	if (data->key_pressed.s == true)
	{
		axis.x -= cos(radi);
		axis.y -= sin(radi);
		press = true;
	}
	if (data->key_pressed.d == true)
	{
		axis.x -= sin(radi);
		axis.y += cos(radi);
		press = true;
	}
	if (data->key_pressed.a == true)
	{
		axis.x += sin(radi);
		axis.y -= cos(radi);
		press = true;
	}

	if (press && is_collided_wall(data, axis) == false)
	{
		// data->player.position.x += axis.x * PLAYER_SPEED;
		// data->player.position.y += axis.y * PLAYER_SPEED;
	}
	data->player.angle -= (data->key_pressed.left == true) * CAM_SENS;
	data->player.angle += (data->key_pressed.right == true) * CAM_SENS;

	if (data->player.angle > 360)
		data->player.angle -= 360;
	if (data->player.angle < 0)
		data->player.angle += 360;
}

int	game_loop(t_data *data)
{
	t_ray	ray;
	// FPS PART 1
	static int	fps;
	static int	tfps;
	static long	ltime;
	if (ltime == 0)
		ltime = get_time();
	
	handle_input(data, deg_to_rad(data->player.angle));
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	if (data->game_started == false)
	{
		splash_screen(data);
		return (0);
	}
	t_image_clear_color(&data->minimaps_layer, 0xffffffff);
	put_bgd(&data->scene_layer, 0x79c0ff, 0xe5c359);
	put_maps(data->maps, &data->minimaps_layer);
	float angle = data->player.angle - (FOV / 2);
	if (angle < 0)
		angle += 360;
	if (angle > 360)
		angle -= 360;
	int i = 0;
	while (i < WIN_WIDTH)
	{
		// printf("%f\n", angle);
		if (i == WIN_WIDTH / 2 || 1)
		{
			send_ray(&ray, angle);
			put_wall(data, i, &ray);
		}
		// printf("ray :\t%d\t->[ angle: %f , intercept (x: %f, y: %f)]\n", i, angle, ray.intersept_point.x, ray.intersept_point.y);
		angle += (float) FOV / WIN_WIDTH;
		i++;
	}
	// exit(1);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->scene_layer.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->minimaps_layer.img_ptr, 0, 0);
	
	// FPS PART 2
	printf("FPS : %d\n", tfps);
	if (get_time() - ltime >= 1000)
	{
		tfps = fps;
		fps = 0;
		ltime = get_time();
	}
	fps++;
	
	return (0);
}

void	run_game(t_data *data)
{
	t_vector	map_size;

	map_size.x = data->scene_info.maps_xsize * TILE_SIZE;
	map_size.y = data->scene_info.maps_ysize * TILE_SIZE;
	data->scene_layer = t_image_create(WIN_WIDTH, WIN_HEIGHT, 0xffffffff);
	data->minimaps_layer = t_image_create(data->screen.width * TILE_SIZE, data->screen.height * TILE_SIZE, 0xffffffff);
	init_player(data);
	init_keys(data);
	data->texture_ea = t_image_loadfromxpm(data->scene_info.east_texture);
	data->texture_we = t_image_loadfromxpm(data->scene_info.west_texture);
	data->texture_so = t_image_loadfromxpm(data->scene_info.south_texture);
	data->texture_no = t_image_loadfromxpm(data->scene_info.north_texture);
	data->player.angle = 45;
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYDOWN, 0, ev_key_down, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYUP, 0, ev_key_up, data);
	mlx_loop(data->mlx.mlx_ptr);
}
