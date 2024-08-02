/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by aabouqas          #+#    #+#             */
/*   Updated: 2024/08/02 10:55:13 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

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
