/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/15 13:40:39 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_ray	send_virtical_ray(float ray_angle)
{
	t_data		*data;
	t_ray		ray;
	t_vector2	plyr_pos;
	t_vector2	step;
	t_vector2	inrcpt;
	t_size		sc_size;

	data = data_hook(NULL);
	ray.hit_wall = false;
	sc_size = data_hook(NULL)->screen;
	sc_size = (t_size) {sc_size.width * 32, sc_size.height * 32};
	plyr_pos = data->player.position;
	set_ray_side(&ray, ray_angle);
	step.x = TILE_SIZE;
	if (ray.facing_left)
		step.x *= -1;
	step.y = TILE_SIZE * tan(ray_angle);
	inrcpt.x = floor(plyr_pos.x / TILE_SIZE) * TILE_SIZE;
	if (ray.facing_right)
		inrcpt.x += TILE_SIZE;
	inrcpt.y = plyr_pos.y + (inrcpt.x - plyr_pos.x) * tan(ray_angle);
	if ((ray.facing_up && step.y > 0) || (ray.facing_down && step.y < 0))
		step.y *= -1;
	while (inrcpt.x > 0 && inrcpt.x < sc_size.width && inrcpt.y > 0 && inrcpt.y < sc_size.height)
	{
		if (hit_wall_at((t_vector2){inrcpt.x - ray.facing_left, inrcpt.y}))
		{
			ray.hit_wall = true;
			break;
		}
		inrcpt.y += step.y;
		inrcpt.x += step.x;
	}
	ray.intersept_point = inrcpt;
	ray.angle = ray_angle;
	return (ray);
}
