/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:57:58 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/31 16:53:15 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float	get_distance(float angle, t_vector2 end)
{
	double		distance;
	t_player	player;
	t_vector2	plyrpos;
	float		angle_in_deg;

	angle_in_deg = (angle * 180) / M_PI;
	player = data_hook(NULL)->player;
	plyrpos = player.position;
	distance = sqrt(pow(end.x - plyrpos.x, 2) + pow(end.y - plyrpos.y, 2));
	distance *= cos(deg_to_rad(angle_in_deg - player.angle));
	return (distance);
}

void	set_ray_side(t_ray *ray)
{
	ray->face_down = ray->angle > 0 && ray->angle < M_PI;
	ray->face_up = ray->angle > M_PI && ray->angle < (M_PI * 2);
	ray->face_right = ray->angle < 0.5 * M_PI || ray->angle > 1.5 * M_PI;
	ray->face_left = ray->angle > 0.5 * M_PI && ray->angle < (1.5 * M_PI);
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

int	check_hit(t_vector2 coords, t_ray *ray)
{
	t_size		grid;
	t_data		*data;
	t_size		screen_size;

	data = data_hook(NULL);
	screen_size = data->screen;
	grid = (t_size){(coords.x / TILE_SIZE), coords.y / TILE_SIZE};
	if (grid.width > screen_size.width || grid.height > screen_size.height)
		return (true);
	if (data->map[grid.height][grid.width] == '1')
	{
		ray->hit_wall = true;
		return (1);
	}
	return (false);
}
