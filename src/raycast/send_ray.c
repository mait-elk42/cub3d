/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/20 13:54:41 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	send_ray(t_ray *ray, double ray_angle)
{
	t_data		*data;
	t_ray		verti;
	t_ray		hori;
	t_size		screen_size;
	t_vector2	plyrpos;

	data = data_hook(NULL);
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
		return ;
	}
	set_directions(&verti, VERTICAL);
	*ray = verti;
}
