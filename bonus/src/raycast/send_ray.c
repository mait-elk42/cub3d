/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/28 19:41:53 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	send_ray(t_ray *ray, double ray_angle)
{
	t_data		*data;
	t_ray		verti;
	t_ray		hori;
	t_size		screen_size;
	t_vector2	plyrpos;

	data = data_hook(NULL);
	ft_bzero(ray, sizeof(t_ray));
	plyrpos = data->player.position;
	ray_angle = deg_to_rad(ray_angle);
	screen_size.width = data->screen.width * TILE_SIZE;
	screen_size.height = data->screen.height * TILE_SIZE;
	hori = send_horizontal_ray(ray_angle, screen_size);
	set_distence(&hori);
	verti = send_virtical_ray(ray_angle, screen_size);
	set_distence(&verti);

	if (hori.distance <= verti.distance)
	{
		set_directions(&hori, HORIZONTAL);
		*ray = hori;
	}
	else
	{
		set_directions(&verti, VERTICAL);
		*ray = verti;
	}
	if (ray->hit_door == true && ray->distance < 30)
		data->looking_door = true;
	// printf("h %d , v %d\n", hori.hit_door, verti.hit_door);
	// if (ray->hit_door && data->player_looking_at_door == false && ray->distance < 30)
	// 	data->player_looking_at_door = true;
}
