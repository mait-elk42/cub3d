/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:57:58 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/17 09:05:31 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float	get_distence(float angle, t_vector2 end)
{
	double		distance;
	t_player	player;
	t_vector2	plyrpos;

	player = data_hook(NULL)->player;
	plyrpos = player.position;
	distance = sqrt(pow(end.x - plyrpos.x, 2) + pow(end.y - plyrpos.y, 2));
	distance *= cos(deg_to_rad(((angle * 180) / M_PI) - player.angle));
	return (distance);
}

void	set_distence(t_ray *ray)
{
	t_data		*data;

	data = data_hook(NULL);
	if (ray->hit_wall == true)
	{
		ray->distance = get_distence(ray->angle, ray->intercept);
		return ;
	}
	ray->distance = INT_MAX;
}

void	set_ray_side(t_ray *ray, float angle)
{
	ray->face_down = angle > 0 && angle < M_PI;
	ray->face_up = angle > M_PI && angle < (M_PI * 2);
	ray->face_right = angle < 0.5 * M_PI || angle > 1.5 * M_PI;
	ray->face_left = angle > 0.5 * M_PI && angle < (1.5 * M_PI);
}

void	set_directions(t_ray *ray, int ray_type)
{
	if (ray_type == HORIZONTAL)
	{
		if (ray->face_up)
			ray->direction = NORTH;
		else if (ray->face_down)
			ray->direction = SOUTH;
		else
			ray->direction = UNKNOWN;
		ray->side = HORIZONTAL;
		return ;
	}
	if (ray->face_right)
		ray->direction = EAST;
	else if (ray->face_left)
		ray->direction = WEST;
	else
		ray->direction = UNKNOWN;
	ray->side = VERTICAL;
}

int	check_wall(t_vector2 coords)
{
	t_vector	grid;
	t_data		*data;

	data = data_hook(NULL);
	grid = (t_vector){(coords.x / TILE_SIZE), coords.y / TILE_SIZE};
	if (data->maps[grid.y][grid.x] == '1')
		return (true);
	return (false);
}
