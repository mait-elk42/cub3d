/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/29 09:33:16 by mait-elk         ###   ########.fr       */
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
	while (point.x > 0 && point.x < width && point.y > 0 && point.y < height)
	{
		if (check_hit((t_vector2){point.x, point.y}, ray, &point, step))
			break ;
		if (check_hit((t_vector2){point.x, point.y - ray->face_up}, ray, &point, step))
			break ;
		point.x += step.x;
		point.y += step.y;
	}
	ray->intercept = point;
}

t_ray	send_horizontal_ray(float ray_angle, t_size screen_size)
{
	t_ray		ray;
	t_vector2	step;

	ft_bzero(&ray, sizeof(t_ray));
	ray.angle = ray_angle;
	ray.side = HORIZONTAL;
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
