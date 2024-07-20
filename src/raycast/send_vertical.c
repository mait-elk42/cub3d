/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/20 13:40:27 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_vector2	get_virtical_intercept(t_ray ray)
{
	t_vector2	intercept;
	t_vector2	plyrpos;
	int			tile_size;

	tile_size = data_hook(NULL)->settings.tile_size;
	plyrpos = data_hook(NULL)->player.position;
	intercept.x = floor(plyrpos.x / tile_size) * tile_size;
	if (ray.face_right)
		intercept.x += tile_size;
	intercept.y = plyrpos.y + (intercept.x - plyrpos.x) * tan(ray.angle);
	return (intercept);
}

static void	cast_the_ray(t_vector2 step, t_size screen, t_ray *ray)
{
	size_t	width;
	size_t	height;

	width = screen.width;
	height = screen.height;
	while (
		ray->intercept.x > 0 && ray->intercept.x < width
		&& ray->intercept.y > 0 && ray->intercept.y < height
	)
	{
		if (check_wall((t_vector2){
				ray->intercept.x - ray->face_left, ray->intercept.y
			}))
		{
			ray->hit_wall = true;
			break ;
		}
		ray->intercept.y += step.y;
		ray->intercept.x += step.x;
	}
}

t_ray	send_virtical_ray(float ray_angle, t_size screen_size)
{
	t_data		*data;
	t_ray		ray;
	t_vector2	step;
	int			tile_size;

	data = data_hook(NULL);
	tile_size = data->settings.tile_size;
	ray.hit_wall = false;
	ray.angle = ray_angle;
	set_ray_side(&ray, ray_angle);
	step.x = tile_size;
	if (ray.face_left)
		step.x *= -1;
	step.y = tile_size * tan(ray_angle);
	if ((ray.face_up && step.y > 0) || (ray.face_down && step.y < 0))
		step.y *= -1;
	ray.intercept = get_virtical_intercept(ray);
	cast_the_ray (step, screen_size, &ray);
	return (ray);
}
