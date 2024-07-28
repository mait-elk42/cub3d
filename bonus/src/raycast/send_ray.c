/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/28 19:16:56 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	send_ray2(t_ray *ray, double ray_angle)
{
	t_data		*data;
	t_ray		verti;
	t_ray		hori;
	t_size		screen_size;
	t_vector2	plyrpos;

	data = data_hook(NULL);
	ft_bzero(ray, sizeof(t_ray));
	plyrpos = data->player.position;
	ray_angle = deg_to_rad(ray_angle);
	screen_size.width = data->screen.width * TILE_SIZE;
	screen_size.height = data->screen.height * TILE_SIZE;
	verti = send_virtical_ray(ray_angle, screen_size);
	set_distance(&verti);
	hori = send_horizontal_ray(ray_angle, screen_size);
	set_distance(&hori);

	if (hori.distance <= verti.distance)
	{
		set_directions(&hori, HORIZONTAL);
		*ray = hori;
		return ;
	}
	set_directions(&verti, VERTICAL);
	*ray = verti;
	// if (hori.hit_door && ray->hit_door == false)
		// ray->hit_door = true;
	// printf("%f %f\n", ray->d, ray->w);
}

t_vector2	get_step(t_ray ray, int type)
{
	t_vector2	step;

	if (type == VERTICAL)
	{
		step.x = TILE_SIZE;
		if (ray.face_left)
			step.x *= -1;
		step.y = TILE_SIZE * tan(ray.angle);
		if ((ray.face_up && step.y > 0) || (ray.face_down && step.y < 0))
			step.y *= -1;
		return (step);
	}
	step.y = TILE_SIZE;
	if (ray.face_up)
		step.y *= -1;
	step.x = TILE_SIZE / tan(ray.angle);
	if ((ray.face_left && step.x > 0) || (ray.face_right && step.x < 0))
		step.x *= -1;
	return (step);
}

t_vector2	get_intercept_v(t_ray ray)
{
	t_vector2	intercept;
	t_vector2	player_pos;

	player_pos = data_hook(NULL)->player.position;
	intercept.x = floor(player_pos.x / TILE_SIZE) * TILE_SIZE;
	if (ray.face_right)
		intercept.x += TILE_SIZE;
	intercept.y = player_pos.y + (intercept.x - player_pos.x) * tan(ray.angle);
	return (intercept);
}

t_vector2	get_intercept_h(t_ray ray)
{
	t_vector2	intercept;
	t_vector2	player_pos;

	player_pos = data_hook(NULL)->player.position;
	intercept.y = floor(player_pos.y / TILE_SIZE) * TILE_SIZE;
	if (ray.face_down)
		intercept.y += TILE_SIZE;
	intercept.x = player_pos.x + (intercept.y - player_pos.y) / tan(ray.angle);
	return (intercept);
}

void	send_ray(t_ray *ray)
{
	t_vector2	step_h;
	t_vector2	step_v;
	t_vector2	intercept_h;
	t_vector2	intercept_v;
	float		dis_h;
	float		dis_v;
	char		**map;
	int			width;
	int			height;

	dis_h = 0;
	dis_v = 0;
	ray->angle = deg_to_rad(ray->angle);
	set_ray_side(ray);
	step_v = get_step(*ray, VERTICAL);
	step_h = get_step(*ray, HORIZONTAL);
	intercept_h = get_intercept_h(*ray);
	intercept_v = get_intercept_v(*ray);
	map = data_hook(NULL)->map;
	width = data_hook(NULL)->screen.width * 32;
	height = data_hook(NULL)->screen.height * 32;
	set_ray_side(ray);
	while (intercept_h.x > 0 && intercept_h.x < width && intercept_h.y > 0 && intercept_h.y < height)
	{
		if (map[(int)(intercept_h.y - ray->face_up) / 32][(int)intercept_h.x / 32] == '1')
			break;
		intercept_h.x += step_h.x;
		intercept_h.y += step_h.y;
	}
	
	while (intercept_v.x > 0 && intercept_v.x < width && intercept_v.y > 0 && intercept_v.y < height)
	{
		if (map[(int)intercept_v.y / 32][(int)(intercept_v.x - ray->face_left) / 32] == '1')
			break;
		intercept_v.x += step_v.x;
		intercept_v.y += step_v.y;
	}
	ray->hit_door = false;
	if (get_distance(ray->angle, intercept_h) < get_distance(ray->angle, intercept_v))
	{
		ray->intercept = intercept_h;
		ray->side = HORIZONTAL;
		ray->hit_wall = true;
		ray->distance = get_distance(ray->angle, intercept_h);
		// ray->hit_door = ray->hit_door_h == true;
	} else {
		ray->intercept = intercept_v;
		ray->side = VERTICAL;
		ray->hit_wall = true;
		ray->distance = get_distance(ray->angle, intercept_v);
		ray->hit_door = ray->hit_door_v == true;
	}
}
