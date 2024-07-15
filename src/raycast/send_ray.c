/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/15 16:51:31 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	send_ray(t_ray *ray, double ray_angle)
{
	t_data	*data;
	t_ray	vertical;
	t_ray	horizontal;
	t_size	screen_size;

	data = data_hook(NULL);
	ray_angle = deg_to_rad(ray_angle);
	screen_size.width = data->screen.width * TILE_SIZE;
	screen_size.height = data->screen.height * TILE_SIZE;
	horizontal = send_horizontal_ray(ray_angle, screen_size);
	set_distence(&horizontal);
	vertical = send_virtical_ray(ray_angle, screen_size);
	set_distence(&vertical);
	if (horizontal.distance <= vertical.distance)
	{
		set_directions(&horizontal, HORIZONTAL);
		draw_line(&data->minimaps_layer, RGB_DARK_GREEN, data->player.position, horizontal.intercept);
		*ray = horizontal;
		return ;
	}
	set_directions(&vertical, VERTICAL);
	draw_line(&data->minimaps_layer, RGB_DARK_GREEN, data->player.position, vertical.intercept);
	*ray = vertical;
}
