/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:57:58 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/26 20:13:35 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

float progress = 16;

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
		// ray->door_distance = get_distence(ray->angle, ray->door_intercept);
		return ;
	}
	ray->distance = INT_MAX;
	// ray->door_distance = INT_MAX;
	return ;
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
	// .. get char that ray hitted only if its 1 or D
	if (data->map[grid.height][grid.width] == 'D')
	{
		// if (data->map[(int) data->player.position.y / 32][(int) data->player.position.x / 32] == 'D')
		// {
			// ray->hit_door = false;
		// 	return 0;
		// }
		// else
		// printf("%f\n", (int)point->x % TILE_SIZE));
		// point->x += step.x / 2;
		// point->y += step.y / 2;
		ray->hit_door = true;
		ray->hit_wall = true;
		if (ray->side == VERTICAL &&((int)(point->y) % TILE_SIZE) > abs(data->n))
			return (0);
		// if (ray->side == HORIZONTAL &&((int)point->x % TILE_SIZE) > 16)
		// 	return (0);
		// ray->intercept = (t_vector2){point->x + (step.x / 2), point->y + (step.y / 2)};
		return (1);
	}
	if (data->map[grid.height][grid.width] == '1')
	{
		ray->hit_wall = true;
		ray->hit_door = false;
		return (1);
	}
	return (false);
}
