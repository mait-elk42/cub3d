/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:57:58 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/28 19:08:15 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

float progress = 16;

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

void	set_distance(t_ray *ray)
{
	t_data		*data;

	data = data_hook(NULL);
	if (ray->hit_wall == true || ray->hit_door == true)
	{
		// if (ray->hit_door)
		// {
		// 	ray->intercept.x += ray->step.x / 2;
		// 	ray->intercept.y += ray->step.y / 2;
		// }
		ray->distance = get_distance(ray->angle, ray->intercept);
		ray->distance_door = get_distance(ray->angle, ray->intercept_door);
		return ;
	}
	ray->distance = INT_MAX;
	ray->distance_door = INT_MAX;
	return ;
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

int	check_hit(t_vector2 coords, t_ray *ray, t_vector2 *point, t_vector2 step) // remember to read this : https://lodev.org/cgtutor/raycasting4.html [24/07/2024]
{
	t_size		grid;
	t_data		*data;
	t_size		screen_size;

	data = data_hook(NULL);
	screen_size = data->screen;
	grid = (t_size){(coords.x / TILE_SIZE), coords.y / TILE_SIZE};
	if (grid.width > screen_size.width || grid.height > screen_size.height)
		return (true);
	if (data->map[grid.height][grid.width] == 'd')
	{
		data->looking_door = true;
		data->door_pos = (t_vector){grid.width, grid.height};
		return (0);
	}
	
	// if (data->map[grid.height][grid.width] == 'D')
	// {
	// 	point->x += step.x / 2;
	// 	point->y += step.y / 2;
	// 	data->door_pos = (t_vector){grid.width, grid.height};
	// 	ray->hit_wall = true;
	// 	ray->hit_door = true;
	// 	return (1);
	// }

	// if (data->map[grid.height][grid.width] == 'D')
	// {
	// 	point->x += step.x / 2;
	// 	point->y += step.y / 2;
	// 	ray->hit_wall = true;
	// 	ray->hit_door = true;
	// 	return (1);
	// }

	if (data->map[grid.height][grid.width] == '1')
	{
		ray->hit_wall = true;
		return (1);
	}
	// else if (data->map[grid.height][grid.width] == 'D')
	// {
	// 	if (data->map[(int) data->player.position.y / 32][(int) data->player.position.x / 32] == 'D')
	// 	{
	// 		ray->hit_door = false;
	// 		return 0;
	// 	}
	// 	else if (ray->side == VERTICAL)
	// 	{
	// 		ray->hit_door = false;
	// 		ray->hit_wall = false;
	// 		if (((int)(point->y) % TILE_SIZE) >= data->d)
	// 			return (0);
	// 		ray->hit_door = true;
	// 		return (true);
	// 	}
	// 	// ray->hit_door = true;
	// 	return (false);
	// }
	return (false);
}
