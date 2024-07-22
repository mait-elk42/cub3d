/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/22 18:19:37 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

t_vector2	get_horizontal_intercept(t_ray ray, float ray_angle)
{
	t_vector2	intercpt;
	t_vector2	player_pos;

	player_pos = data_hook(NULL)->player.position;
	intercpt.y = floor(player_pos.y / TILE_SIZE) * TILE_SIZE;
	if (ray.face_down)
		intercpt.y += TILE_SIZE;
	intercpt.x = player_pos.x + (intercpt.y - player_pos.y) / tan(ray_angle);
	return (intercpt);
}

static int	cast_the_ray(t_vector2 step, t_size screen, t_ray *ray)
{
	size_t	width;
	size_t	height;

	width = screen.width;
	height = screen.height;
	while (
		ray->intercept.x > 0 && ray->intercept.x < width
		&& ray->intercept.y > 0 && ray->intercept.y < height)
	{
		if (ray->face_right)
			if (check_wall((t_vector2){ray->intercept.x -1, ray->intercept.y}))
				return (ray->hit_wall = true, 1);
		if (ray->face_up)
			if (check_wall((t_vector2){ray->intercept.x, ray->intercept.y -1}))
				return (ray->hit_wall = true, 1);
		if (check_wall(ray->intercept))
			return (ray->hit_wall = true, 1);
		ray->intercept.x += step.x;
		ray->intercept.y += step.y;
	}
	ray->hit_wall = false;
	return (0);
}

t_ray	send_horizontal_ray(float ray_angle, t_size screen_size)
{
	t_data		*data;
	t_ray		ray;
	t_vector2	step;

	data = data_hook(NULL);
	ray.angle = ray_angle;
	ray.hit_wall = false;
	set_ray_side (&ray, ray_angle);
	step.y = TILE_SIZE;
	if (ray.face_up)
		step.y *= -1;
	step.x = TILE_SIZE / tan(ray_angle);
	if ((ray.face_left && step.x > 0) || (ray.face_right && step.x < 0))
		step.x *= -1;
	ray.intercept = get_horizontal_intercept(ray, ray_angle);
	cast_the_ray(step, screen_size, &ray);
	return (ray);
}
