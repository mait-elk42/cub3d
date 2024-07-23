/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/23 11:01:28 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_vector2	get_virtical_intercept(t_ray ray)
{
	t_vector2	intercept;
	t_vector2	plyrpos;

	plyrpos = data_hook(NULL)->player.position;
	intercept.x = floor(plyrpos.x / TILE_SIZE) * TILE_SIZE;
	if (ray.face_right)
		intercept.x += TILE_SIZE;
	intercept.y = plyrpos.y + (intercept.x - plyrpos.x) * tan(ray.angle);
	return (intercept);
}

static void	cast_the_ray(t_vector2 step, t_size screen, t_ray *ray)
{
	size_t		width;
	size_t		height;
	t_vector2	point;

	width = screen.width;
	height = screen.height;
	point = ray->intercept;
	ray->hit_wall = false;
	while (point.x > 0 && point.x < width && point.y > 0 && point.y < height)
	{
		if (check_wall((t_vector2){point.x - ray->face_left, point.y}, ray))
			break ;
		point.y += step.y;
		point.x += step.x;
	}
	ray->intercept = point;
}

t_ray	send_virtical_ray(float ray_angle, t_size screen_size)
{
	t_data		*data;
	t_ray		ray;
	t_vector2	step;

	data = data_hook(NULL);
	ray.hit_wall = false;
	ray.angle = ray_angle;
	set_ray_side(&ray, ray_angle);
	step.x = TILE_SIZE;
	if (ray.face_left)
		step.x *= -1;
	step.y = TILE_SIZE * tan(ray_angle);
	if ((ray.face_up && step.y > 0) || (ray.face_down && step.y < 0))
		step.y *= -1;
	ray.intercept = get_virtical_intercept(ray);
	cast_the_ray (step, screen_size, &ray);
	return (ray);
}
