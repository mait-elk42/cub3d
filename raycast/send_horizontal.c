/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/15 13:40:35 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_ray	send_horizontal_ray(float ray_angle)
{
	t_data		*data;
	t_ray		ray;
	t_vector2	plyr_pos;
	t_vector2	step;
	t_vector2	inrcpt;

	data = data_hook(NULL);
	ray.hit_wall = false;
	set_ray_side(&ray, ray_angle);
	plyr_pos = data->player.position;
	inrcpt.y = floor(plyr_pos.y / TILE_SIZE) * TILE_SIZE;
	inrcpt.y += (TILE_SIZE * ray.facing_down);
	step.y = TILE_SIZE;
	step.x = TILE_SIZE / tan(ray_angle);
	if ((ray.facing_left && step.x > 0) || (ray.facing_right && step.x < 0))
		step.x *= -1;
	inrcpt.x = plyr_pos.x + (inrcpt.y - plyr_pos.y) / tan(ray_angle);
	if (ray.facing_up)
		step.y *= -1;
	while (inrcpt.x > 0 && inrcpt.x < (data->screen.width * TILE_SIZE) && inrcpt.y > 0 && inrcpt.y < (data->screen.height * TILE_SIZE))
	{
		if (
			(ray.facing_right && hit_wall_at((t_vector2){inrcpt.x - 1, inrcpt.y})) || 
			 hit_wall_at((t_vector2){inrcpt.x, inrcpt.y - (ray.facing_up == true)})
		)
		{
			ray.hit_wall = true;
			break;
		}
		inrcpt.y += step.y;
		inrcpt.x += step.x;
	}
	ray.intersept_point = inrcpt;
	ray.angle = ray_angle;
	return(ray);
}
