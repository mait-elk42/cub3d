/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/23 09:13:06 by aabouqas         ###   ########.fr       */
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
		if (ray->face_right)
			if (check_hit((t_vector2){point.x -1, point.y}, ray, &point, step))
				break;
		if (ray->face_up)
			if (check_hit((t_vector2){point.x, point.y -1}, ray, &point, step))
				break;
		if (check_hit(point, ray, &point, step))
			break ;
		point.x += step.x;
		point.y += step.y;
	}
	ray->intercept = point;
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
