/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/13 08:23:00 by aabouqas         ###   ########.fr       */
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
	distance *= cos(deg_to_rad(((angle * 180) / M_PI) - player.angle));
	return (distance);
}

void	set_ray_side(t_ray *ray, float angle)
{
	ray->facing_down = angle > 0 && angle < M_PI;
	// ray->facing_up = ray->facing_down == false;
	ray->facing_up = angle > M_PI && angle < (M_PI * 2);
	ray->facing_right = angle < 0.5 * M_PI || angle > 1.5 * M_PI;
	ray->facing_left = angle > 0.5 * M_PI && angle < (1.5 * M_PI);
	// ray->facing_right = (angle >= 0 && angle <= (M_PI / 2)) || ((angle > ((2 * M_PI) - (M_PI / 2))) && (angle <= (M_PI * 2)));
}

int	hit_wall_at(t_vector2 cords)
{
	t_vector	grid;
	t_data		*data;

	data = data_hook(NULL);
	grid = (t_vector) {(cords.x / TILE_SIZE), cords.y / TILE_SIZE};
	return (data->maps[grid.y][grid.x] == '1');
	// return (1);
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
		// draw_line(&data->minimaps_layer, RGB_RED, (t_vector2){((data->screen.width / 2) * 32) + 32, ((data->screen.height / 2) * 32) + 32}, horizontal.intersept_point);
		horizontal.side = HORIZONTAL;
		*ray = horizontal;
		return ;
	}
	// draw_line(&data->minimaps_layer, RGB_RED, (t_vector2){((data->screen.width / 2) * 32) + 32, ((data->screen.height / 2) * 32) + 32}, vertical.intersept_point);
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
	player_pos = (t_vector2){(data->screen.width / 2) * 32, (data->screen.height / 2) * 32};
	p1.x = cos(deg_to_rad(data->player.angle - 120)) * size + player_pos.x;
	p1.y = sin(deg_to_rad(data->player.angle - 120)) * size + player_pos.y;

	p2.x = cos(deg_to_rad(data->player.angle + 120)) * size + player_pos.x;
	p2.y = sin(deg_to_rad(data->player.angle + 120)) * size + player_pos.y;

	p3.x = cos(deg_to_rad(data->player.angle)) * size + player_pos.x;
	p3.y = sin(deg_to_rad(data->player.angle)) * size + player_pos.y;

	draw_line(&data->scene_layer, 0xff0000,p1, p3);
	draw_line(&data->scene_layer, 0xff0000,p2, p3);
}

// bool	is_collided_wall(t_data	*data, t_vector2 next_pos)
// {
// 	char		**map;
// 	t_vector	p_pos;
// 	t_vector	n_pos;

// 	p_pos.x = (int) data->player.position.x / TILE_SIZE;
// 	p_pos.y = (int) data->player.position.y / TILE_SIZE;
// 	n_pos = (t_vector) {(data->player.position.x + next_pos.x) / 32, (data->player.position.y + next_pos.y) / 32};
// 	map = data->maps;
// 	if ((map[(int)n_pos.y][p_pos.x] == '1' && map[p_pos.y][(int)n_pos.x] == '1'))
// 		return (1);
// 	// the following commented part is to add some space between player and the wall
// 	if (map[(int) (data->player.position.y + (next_pos.y * 2)) / TILE_SIZE][(int) (data->player.position.x + (next_pos.x * 2)) / TILE_SIZE] == '1')
// 		return (1);
// 	// printf("[%f %f]\n", next_pos.x, next_pos.y);
// 	if ((int) next_pos.x < 0)
// 		next_pos.x -= COLISION;
// 	else if ((int) next_pos.x > 0)
// 		next_pos.x += COLISION;
// 	if ((int) next_pos.y < 0)
// 		next_pos.y -= COLISION;
// 	else if ((int) next_pos.y > 0)
// 		next_pos.y += COLISION;
// 	// p_player.x += next_pos.x;
// 	// p_player.y += next_pos.y;
// 	// g_player.x = p_player.x / TILE_SIZE;
// 	// g_player.y = p_player.y / TILE_SIZE;
// 	// return (map[g_player.y][g_player.x] == '1');
// 	// return (map[(int) (data->player.position.y + (next_pos.y + (next_pos.y < 0 ? -15 : +15))) / 32][(int) (data->player.position.x + (next_pos.x + (next_pos.x < 0 ? -15 : +15))) / 32] == '1');
// 	return (false);
// }


bool	is_collided_wall()
{
	t_data		*data;
	t_vector2	plyr_pos;
	t_vector2	end_point;
	t_vector	grid;
	char		**map;
	
	data = data_hook(NULL);
	map = data->maps;
	plyr_pos = data->player.position;
	int i = 0;
	while (i <= 360)
	{
		end_point.x = plyr_pos.x + cos(deg_to_rad(i)) * 10;
		end_point.y = plyr_pos.y + sin(deg_to_rad(i)) * 10;
		draw_line(&data->minimaps_layer, RGB_BROWN, data->player.position, end_point);
		grid.x = (int) (end_point.x / TILE_SIZE);
		grid.y = (int) (end_point.y / TILE_SIZE);
		if (map[grid.y][grid.y] == '1')
			return (true);
		i++;
	}
	return (false);
}

// #error working in collition :)
void	handle_input(t_data *data, float radi)
{
	char		**maps;
	t_vector2	next_pos;

	// next_pos = data->player.position;
	next_pos = (t_vector2) {0, 0};
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
	if (is_collided_wall())
	{
		// data->player.position = (t_vector2) next_pos;
		data->player.position.x += next_pos.x;
		data->player.position.y += next_pos.y;
	}
	data->player.angle -= (data->keys.left.pressed == true) * CAM_SENS;
	data->player.angle += (data->keys.right.pressed == true) * CAM_SENS;
	
	// data->player.top_down += (data->keys.up.pressed == true) * CAM_SENS * 10;
	// data->player.top_down -= (data->keys.down.pressed == true) * CAM_SENS * 10;
	if (data->player.angle >= 360 || data->player.angle < 0)
		data->player.angle = 360 * (data->player.angle < 0);
}

// # error there two errors : 1:{Raycasting rendering - wall's edge crossing issue} , 2{the wall is too bad like a circle}

int	get_color_distance(t_ray ray, int color)
{
	unsigned char	r,g,b;
	char	*defc = (char *)&color;

	if ((ray.distance / 30) < 1)
		ray.distance = 1;
	r = defc[0];
	g = defc[1];
	b = defc[2];

	r /= (ray.distance / 30);
	g /= (ray.distance / 30);
	b /= (ray.distance / 30);
	
	return (0 << 24 | r << 16 | g << 8 | b);
}

void	put_wall(t_data *data, int i)
{
	// int wallHeight = (WIN_HEIGHT / data->rays[i].distance) * TILE_SIZE;
	// int	top = (WIN_HEIGHT / 2) - (wallHeight / 2);
	// int btm = top + wallHeight;
	// printf("%f\n", data->rays[i].distance);
	int wallHeight = (double)(WIN_HEIGHT / data->rays[i].distance) * 30.0;// 30.0 is the scale of the walls -- recommanded to create a macro for it
	int	top = (WIN_HEIGHT / 2) - (wallHeight / 2);
	int btm = top + wallHeight;
	// printf("%f %d %d\n", data->rays[i].distance, top, btm);
	// if (btm > WIN_HEIGHT)
	// 	btm = WIN_HEIGHT;
	// if (top < 0)
	// 	top = 0;
	draw_line(&data->scene_layer, 0x79c0ff, (t_vector2) {i, 0}, (t_vector2) {i, top});
	if (data->rays[i].side == HORIZONTAL && data->rays[i].direction == UNKNOWN)
	{
		float px = data->rays[i].intersept_point.x / (float)TILE_SIZE;
		int texture_offset_X = (int)(px * data->texture_beta.sizex) % data->texture_beta.sizex;
		int y = top;
		if (y < 0)
			y = 0;
		// printf("%d %d\n", y, btm);
		while (y < btm)
		{
			if (y > WIN_HEIGHT)
				break ;
			float proportion = (float)(y - top) / wallHeight;
			int texture_offset_Y = (int)(proportion * data->texture_beta.sizey) % data->texture_beta.sizey;
			int c = data->texture_beta.buffer[texture_offset_Y * data->texture_beta.sizex + texture_offset_X];
			// c = get_color_distance(data->rays[i], c); // useful
			t_image_update_pixel(&data->scene_layer, i, y, c);
			y++;
		}
	}
	else if (data->rays[i].side == VERTICAL && data->rays[i].direction == WEST)
	{
		float px = data->rays[i].intersept_point.y / (float)TILE_SIZE;
		int texture_offset_X = (int)(px * data->texture_beta.sizex) % data->texture_beta.sizex;
		int y = top;
		while (y < btm)
		{
			float proportion = (float)(y - top) / wallHeight;
			int texture_offset_Y = (int)(proportion * data->texture_beta.sizey) % data->texture_beta.sizey;
			int c = data->texture_beta.buffer[texture_offset_Y * data->texture_beta.sizex + texture_offset_X];
			// c = get_color_distance(data->rays[i], c); // useful
			t_image_update_pixel(&data->scene_layer, i, y, c);
			y++;
		}
		// draw_line(&data->scene_layer,  0x00309E, (t_vector2) {i, top}, (t_vector2) {i, btm});
	}
	draw_line(&data->scene_layer, 0xe5c359, (t_vector2) {i, btm}, (t_vector2) {i, WIN_HEIGHT});
}

// void	put_wall(t_data *data, int i)
// {
// 	// int wallHeight = (WIN_HEIGHT / data->rays[i].distance) * TILE_SIZE;
// 	// int	top = (WIN_HEIGHT / 2) - (wallHeight / 2);
// 	// int btm = top + wallHeight;
// 	int wallHeight = (double)(WIN_HEIGHT / data->rays[i].distance) * 30.0;// 30.0 is the scale of the walls -- recommanded to create a macro for it
// 	int	top = (WIN_HEIGHT / 2) - (wallHeight / 2);
// 	int btm = top + wallHeight;
// 	if (btm > WIN_HEIGHT)
// 		 btm = WIN_HEIGHT;
// 	// if (top < 0)
// 	//	 top = 0;
// 	draw_line(&data->scene_layer, 0x79c0ff, (t_vector2) {i, 0}, (t_vector2) {i, top});
// 	if (data->rays[i].side == HORIZONTAL)
// 	{
// 		float px = data->rays[i].horizontal.x / (float)TILE_SIZE;
// 		int texture_offset_X = (int)(px * data->texture_beta.sizex) % data->texture_beta.sizex;
// 		int y = top;
// 		while (y < btm)
// 		{
// 			float proportion = (float)(y - top) / wallHeight;
// 			int texture_offset_Y = (int)(proportion * data->texture_beta.sizey) % data->texture_beta.sizey;
// 			int c = data->texture_beta.buffer[texture_offset_Y * data->texture_beta.sizex + texture_offset_X];
// 			t_image_update_pixel(&data->scene_layer, i, y, c);
// 			y++;
// 		}
// 	}
// 	else if (data->rays[i].side == VERTICAL)
// 		draw_line(&data->scene_layer,  RGB_DARK_GREEN, (t_vector2) {i, top}, (t_vector2) {i, btm});

// 	draw_line(&data->scene_layer, 0xe5c359, (t_vector2) {i, btm}, (t_vector2) {i, WIN_HEIGHT});
// }

int	game_loop(t_data *data)
{
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
	handle_input(data, deg_to_rad(data->player.angle));
	while (i < WIN_WIDTH)
	{
		if (i == WIN_WIDTH / 2 || 1)
		{
			send_ray(&data->rays[i], angle);
			put_wall(data, i);
		}
		angle += (float) 60 / WIN_WIDTH;
		i++;
	}
	// draw_mini_map();
	// double size = 1;
	// while (size <= 10)
	// {
	// 	put_player_shape(size);
	// 	size++;
	// }
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
	data->texture_beta = t_image_loadfromxpm("textures/brick.xpm");
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYDOWN, 0, ev_key_down, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYUP, 0, ev_key_up, data);
	mlx_loop(data->mlx.mlx_ptr);
}
