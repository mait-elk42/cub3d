/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/06/11 17:46:57 by mait-elk         ###   ########.fr       */
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
	static int kk;
	while (i < step)
	{
		#include <pthread.h>
		pthread
		ft_printf("%d\n", kk++);
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

// void	init_ray_side(t_ray *ray, double stepx, double stepy, int hori)
// {
// 	double	xdiff;
// 	double	ydiff;

// 	(void)stepx;
// 	(void)stepy;
// 	(void)ray;
// 	(void)hori;
// 	(void)xdiff;
// 	(void)ydiff;
// 	// #error debugging here :)

// 	if (ray->hit_wall.x > ray->hit_wall.y)
// 	{
// 		ray->side = EAST;
// 	}else
// 		ray->side = UNKNOWN;
// 	xdiff = ray->hit_wall.x - (floor(ray->hit_wall.x));
// 	ydiff = ray->hit_wall.y - (floor(ray->hit_wall.y));
// 	// printf("\033[H\033[2Jinformations : \n \
// 	// stepx\t: %f \n \
// 	// stepy\t: %f \n \
// 	// hit_x\t: %f \n \
// 	// hit_y\t: %f\n \
// 	// diffx\t: %f \n \
// 	// diffy\t: %f \n",
// 	// stepx, stepy, ray->hit_wall.x, ray->hit_wall.y, xdiff, ydiff);
// 	// printf("<%s>\n", (ray->hit_wall.x > ray->hit_wall.y) ? "more than" : "less than");
// }

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


double	get_distence(double angle, t_vector2 end)
{
	double		distence;
	t_player	player;

	player = data_hook(NULL)->player;
	distence = sqrt(pow(player.cam_pos.x - end.x, 2) + pow(player.cam_pos.y - end.y, 2));
	distence *= cos(mth_degtorad((angle * 180 / M_PI) - player.angle));
	return (distence);
}

t_vector2	get_vert_interseption(double ray_angle)
{
	t_vector2	player_pos;
	t_vector2	intersept;
	t_data		*data;

	data = data_hook(NULL);
	player_pos = (t_vector2) {data->player.cam_pos.x, data->player.cam_pos.y};
	intersept.x = floor(player_pos.x / TILE_SIZE) * TILE_SIZE;
	intersept.y = player_pos.y + (player_pos.x - intersept.x) / tan(ray_angle);
	// printf("[%f | %f || %f]\n", intersept.x, intersept.y, ray_angle);
	return (intersept);
}

void	set_ray_side(t_ray *ray, double angle)
{
	ray->facing_down = angle > 0 && angle < M_PI;
	ray->facing_up = ray->facing_down == false;
	ray->facing_right = angle < 0.5 * M_PI || angle > 1.5 * M_PI;
	ray->facing_left = ray->facing_right == false;
	// printf ("up %d down %d left %d right %d\n", ray->facing_up, ray->facing_down, ray->facing_left, ray->facing_right);
}

int	hit_wall_at(t_vector2 cords)
{
	t_vector	grid;
	t_data		*data;

	data = data_hook(NULL);
	grid = (t_vector) {(int) floor(cords.x / TILE_SIZE), (int) floor(cords.y / TILE_SIZE)};
	// printf("%d | %d\n", grid.x, grid.y);
	return (data->maps[grid.y][grid.x] == '1');
}

t_ray	send_horizontal_ray(t_ray *ray, double ray_angle)
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
	player_pos = data->player.cam_pos;
	intersept.y = floor(player_pos.y / TILE_SIZE) * TILE_SIZE;
	if (ray->facing_down)
		intersept.y += TILE_SIZE;
	step.y = TILE_SIZE;
	step.x = TILE_SIZE / tan(ray_angle);
	intersept.x = data->player.cam_pos.x + (intersept.y - data->player.cam_pos.y) / tan(ray_angle);
	if (ray->facing_up)
		step.y *= -1;
	if ((ray->facing_left && step.x > 0) || (ray->facing_right && step.x < 0))
		step.x *= -1;
	increase.x = intersept.x;
	increase.y = intersept.y;
	// printf("[%f | %f] | [%f | %f]\n",increase.x, increase.y, step.x, step.y);
	while (increase.x > 0 && increase.x < (data->screen.width * TILE_SIZE) && increase.y > 0 && increase.y < (data->screen.height * TILE_SIZE))
	{
		// if ((ray->facing_up && hit_wall_at((t_vector2){increase.x, increase.y - 1})) || hit_wall_at(increase))
		if (hit_wall_at(increase))
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
		// if (ray->facing_up)
		// 	ray->horizontal.y--;
		ray->distance = get_distence(ray_angle, ray->horizontal);
	}
	else
	{
		ray->horizontal = increase;
		ray->distance = INT_MAX;
	}
	return(*ray);
}

t_ray	send_virtical_ray(t_ray *ray, double ray_angle)
{
	t_data		*data;
	t_vector2	player_pos;
	t_vector2	step;
	t_vector2	intersept;
	t_vector2	increase;
	bool		vertical_hit;

	data = data_hook(NULL);
	vertical_hit = false;
	player_pos = data->player.cam_pos;
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
	increase.x = intersept.x;
	increase.y = intersept.y;
	while (increase.x > 0 && increase.x < (data->screen.width * TILE_SIZE) && increase.y > 0 && increase.y < (data->screen.height * TILE_SIZE))
	{
		if ((ray->facing_left && hit_wall_at((t_vector2){increase.x - 1, increase.y})) || hit_wall_at(increase))
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
		// if (ray->facing_left)
		// 	ray->vertical.x--;
		ray->distance = get_distence(ray_angle, ray->vertical);
	} else {
		// ray->vertical = (t_vector2) {-1,-1};
		ray->vertical = increase;
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
	// ft_bzero(ray, sizeof (t_ray));
	ray_angle = mth_degtorad(ray_angle);
	horizontal = send_horizontal_ray(ray, ray_angle);
	vertical = send_virtical_ray(ray, ray_angle);
	// printf("[%f ||| %f]\n", horizontal.distance, vertical.distance);
	if (horizontal.distance < vertical.distance)
	{
		draw_line(&data->minimaps_layer, RGB_BLACK, data->player.cam_pos, ray->horizontal);
		horizontal.side = HORIZONTAL;
		*ray = horizontal;
		return ;
	}
	draw_line(&data->minimaps_layer, RGB_BLACK, data->player.cam_pos, ray->vertical);
	vertical.side = VERTICAL;
	*ray = vertical;
}

// t_ray	send_ray(double angle, int color)
// {
// 	t_data		*data;
// 	t_vector	pp;
// 	t_ray		ray;
// 	double		step_x;
// 	double		step_y;
// 	t_vector2	ray_dir;
// 	char		**map;

// 	data = data_hook(NULL);
// 	pp.x = (int)data->player.cam_pos.x / 20;
// 	pp.y = (int)data->player.cam_pos.y / 20;
// 	map = data->maps;
// 	ray_dir = (t_vector2){data->player.cam_pos.x, data->player.cam_pos.y};
// 	step_x = cos(mth_degtorad(angle)) * 0.2;
// 	step_y = sin(mth_degtorad(angle)) * 0.2;
// 	int	x;
// 	int	y;
// 	while (1)
// 	{
// 		x = (int)(ray_dir.x) / MINIMAP_TILE;
// 		y = (int)(ray_dir.y) / MINIMAP_TILE;
// 		t_image_update_pixel(&data->minimaps_layer, ray_dir.x, ray_dir.y, color);
// 		ray_dir.x += step_x;
// 		ray_dir.y += step_y;
// 		if (map[y][x] == '1' || map[(int)(ray_dir.y) / MINIMAP_TILE][(int)(ray_dir.x - step_x) / MINIMAP_TILE] == '1')
// 			break ;
// 	}
// 	ray.hit_wall = ray_dir;
// 	ray.distance = sqrt(pow(data->player.cam_pos.x - ray_dir.x, 2) + pow(data->player.cam_pos.y - ray_dir.y, 2));
// 	// init_ray_side(&ray, step_x, step_y, hori);
// 	// if (side)
// 	// printf("%d\n", hori);
// 	ray.distance *= cos(mth_degtorad(angle - data->player.angle));
// 	return (ray);
// }



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

	// draw_line(v1, v2);
	// // draw_line(v1, v3);
	// draw_line(v1, v3);
}

bool	is_collided_wall(t_data	*data, t_vector2 next_pos)
{
	char		**map;
	t_vector	p_pos;
	t_vector	n_pos;

	map = data->maps;
	p_pos.x = (int) data->player.cam_pos.x / MINIMAP_TILE;
	p_pos.y = (int) data->player.cam_pos.y / MINIMAP_TILE;
	// the following commented part is to add some space between player and the wall
	// if (p_pos.x <= ((n_pos.x) / MINIMAP_TILE) && p_pos.y <= ((n_pos.y) / MINIMAP_TILE))
	// {
			// n_pos.x += 10;
			// n_pos.y += 10;
	// }
	n_pos = (t_vector) {next_pos.x / MINIMAP_TILE, next_pos.y / MINIMAP_TILE};
	if ((map[(int)n_pos.y][p_pos.x] == '1' && map[p_pos.y][(int)n_pos.x] == '1'))
		return (1);
	return (map[(int) n_pos.y][(int) n_pos.x] == '1');
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
		data->player.cam_pos = new_pos;
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

	if ((ray.distance / 20) < 1)
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
	r /= (ray.distance / 20);
	g /= (ray.distance / 20);
	b /= (ray.distance / 20);
	
	return (0 << 24 | r << 16 | g << 8 | b);
}

int	game_loop(t_data *data)
{
	handle_input(data, mth_degtorad(data->player.angle));
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	if (data->game_started == false)
	{
		data->keys.left.pressed = true;
		data->keys.d.pressed = true;
		// splash_screen(data);
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
		if (i == WIN_WIDTH / 2 || i % 2 == 0)
		{
			// t_ray ray = send_ray(angle, 0xff0000);
			 send_ray(&data->rays[i], angle);
			// if (i == WIN_WIDTH / 2)
			// {
			// 	printf("%f | %d\n", data->rays[i].distance, data->rays[i].side);
			// }
			int wallHeight = (WIN_HEIGHT / data->rays[i].distance) * MINIMAP_TILE;
			int	top = (WIN_HEIGHT / 2) - (wallHeight / 2);
			int btm = top + wallHeight;
			if (btm > WIN_HEIGHT)
				btm = WIN_HEIGHT;
			if (top < 0)
				top = 0;
			if (data->rays[i].side == HORIZONTAL)
				draw_line(&data->scene_layer, RGB_GREEN, (t_vector2) {i, top}, (t_vector2) {i, btm});
			else if (data->rays[i].side == VERTICAL)
				draw_line(&data->scene_layer, RGB_DARK_GREEN, (t_vector2) {i, top}, (t_vector2) {i, btm});
		}
		angle += (float) 60 / WIN_WIDTH;
		if (angle > 360)
			angle = 0;
		i++;
	}
	// put_player_shape(MINIMAP_TILE / 3);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->scene_layer.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->minimaps_layer.img_ptr, 0, 0);
	return (0);
}

void	run_game(t_data *data)
{
	t_size	map_size;

	// # layer 1 : the scene, layer 2 : the maps &&  the player && raycasts
	map_size.width = data->scene_info.maps_xsize * MINIMAP_TILE;
	map_size.height = data->scene_info.maps_ysize * MINIMAP_TILE;
	data->scene_layer = t_image_create(WIN_WIDTH, WIN_HEIGHT, 0xffffffff);
	data->minimaps_layer = t_image_create(map_size.width, map_size.height, 0xffffffff);
	init_player(data);
	init_keys(data);
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYDOWN, 0, ev_key_down, data);
	mlx_hook(data->mlx.window_ptr, ON_KEYUP, 0, ev_key_up, data);
	mlx_loop(data->mlx.mlx_ptr);
}

