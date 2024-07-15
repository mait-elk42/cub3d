/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/15 16:49:15 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_ray	send_virtical_ray(float ray_angle, t_size ss)
{
	t_data		*data;
	t_ray		ray;
	t_vector2	plyr_pos;
	t_vector2	step;
	t_vector2	inrcpt;

	data = data_hook(NULL);
	ray.hit_wall = false;
	plyr_pos = data->player.position;
	set_ray_side(&ray, ray_angle);
	step.x = TILE_SIZE;
	if (ray.face_left)
		step.x *= -1;
	step.y = TILE_SIZE * tan(ray_angle);
	inrcpt.x = floor(plyr_pos.x / TILE_SIZE) * TILE_SIZE;
	if (ray.face_right)
		inrcpt.x += TILE_SIZE;
	inrcpt.y = plyr_pos.y + (inrcpt.x - plyr_pos.x) * tan(ray_angle);
	if ((ray.face_up && step.y > 0) || (ray.face_down && step.y < 0))
		step.y *= -1;
	while (inrcpt.x > 0 && inrcpt.x < ss.width && inrcpt.y > 0 && inrcpt.y < ss.height)
	{
		if (check_wall((t_vector2){inrcpt.x - ray.face_left, inrcpt.y}))
		{
			ray.hit_wall = true;
			break;
		}
		inrcpt.y += step.y;
		inrcpt.x += step.x;
	}
	ray.intercept = inrcpt;
	ray.angle = ray_angle;
	return (ray);
}
