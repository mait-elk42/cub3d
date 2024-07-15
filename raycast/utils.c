/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:57:58 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/15 13:39:33 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float	get_distence(float angle, t_vector2 end)
{
	double		distance;
	t_player	player;

	(void)angle;
	player = data_hook(NULL)->player;
	distance = sqrt(pow(end.x - player.position.x, 2) + pow(end.y - player.position.y, 2));
	distance *= cos(deg_to_rad(((angle * 180) / M_PI) - player.angle));
	return (distance);
}

void	set_distence(t_ray *ray)
{
	t_data		*data;
	t_vector2	intercept_point;

	data = data_hook(NULL);
	intercept_point = ray->intersept_point;
	if (ray->hit_wall == true)
	{
		ray->distance = get_distence(ray->angle, intercept_point);
		return ;
	}
	ray->distance = INT_MAX;
}

void	set_ray_side(t_ray *ray, float angle)
{
	ray->facing_down = angle > 0 && angle < M_PI;
	ray->facing_up = angle > M_PI && angle < (M_PI * 2);
	ray->facing_right = angle < 0.5 * M_PI || angle > 1.5 * M_PI;
	ray->facing_left = angle > 0.5 * M_PI && angle < (1.5 * M_PI);
}

void	set_directions(t_ray *ray, int ray_type)
{
	if (ray_type == HORIZONTAL)
	{
		if (ray->facing_up)
			ray->direction = NORTH;
		else if (ray->facing_down)
			ray->direction = SOUTH;
		else
			ray->direction = UNKNOWN;
		ray->side = HORIZONTAL;
		return ;
	}
	if (ray->facing_right)
		ray->direction = EAST;
	else if (ray->facing_left)
		ray->direction = WEST;
	else
		ray->direction = UNKNOWN;
	ray->side = VERTICAL;
}

int	hit_wall_at(t_vector2 coords)
{
	t_vector	grid;
	t_data		*data;

	data = data_hook(NULL);
	grid = (t_vector) {(coords.x / TILE_SIZE), coords.y / TILE_SIZE};
	if (data->maps[grid.y][grid.x] == '1')
		return (true);
	return (false);
}
