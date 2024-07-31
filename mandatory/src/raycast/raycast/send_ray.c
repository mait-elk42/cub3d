/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/31 15:05:14 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

t_vector2	send_horizontal(t_ray *ray)
{
	t_vector2	step;
	t_vector2	start;
	int			width;
	int			height;

	width = (int) data_hook(NULL)->screen.width * 32;
	height = (int) data_hook(NULL)->screen.height * 32;
	step = get_step(*ray, HORIZONTAL);
	start = get_intercept_h(*ray);
	while (start.x > 0 && start.x < width && start.y > 0 && start.y < height)
	{
		ray->side = HORIZONTAL;
		if (check_hit((t_vector2){start.x, start.y - ray->face_up}, \
			ray, &start, step))
			break ;
		start.x += step.x;
		start.y += step.y;
	}
	return (start);
}

t_vector2	send_vertical(t_ray *ray)
{
	t_vector2	step;
	t_vector2	start;
	int			width;
	int			height;

	width = (int) data_hook(NULL)->screen.width * 32;
	height = (int) data_hook(NULL)->screen.height * 32;
	step = get_step(*ray, VERTICAL);
	start = get_intercept_v(*ray);
	while (start.x > 0 && start.x < width && start.y > 0 && start.y < height)
	{
		ray->side = VERTICAL;
		if (check_hit((t_vector2){start.x - ray->face_left, start.y}, \
			ray, &start, step))
			break ;
		start.x += step.x;
		start.y += step.y;
	}
	return (start);
}

void	send_ray(t_ray *ray)
{
	t_vector2	intercept_h;
	t_vector2	intercept_v;
	float		dis_h;
	float		dis_v;

	ray->angle = deg_to_rad(ray->angle);
	set_ray_side (ray);
	intercept_h = send_horizontal(ray);
	intercept_v = send_vertical(ray);
	dis_h = get_distance(ray->angle, intercept_h);
	dis_v = get_distance(ray->angle, intercept_v);
	if (dis_h <= dis_v)
	{
		set_directions(ray, HORIZONTAL);
		ray->intercept = intercept_h;
		ray->side = HORIZONTAL;
		ray->hit_door = ray->hit_door_h;
		ray->distance = dis_h;
		return ;
	}
	set_directions(ray, VERTICAL);
	ray->intercept = intercept_v;
	ray->side = VERTICAL;
	ray->hit_door = ray->hit_door_v;
	ray->distance = dis_v;
}
