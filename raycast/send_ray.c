/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/15 13:36:01 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	send_ray(t_ray *ray, double ray_angle)
{
	t_data	*data;
	t_ray	vertical;
	t_ray	horizontal;

	data = data_hook(NULL);
	ft_bzero(ray, sizeof (t_ray));
	ray_angle = deg_to_rad(ray_angle);
	
	horizontal = send_horizontal_ray(ray_angle);
	set_distence(&horizontal);

	vertical = send_virtical_ray(ray_angle);
	set_distence(&vertical);
	
	if (horizontal.distance <= vertical.distance)
	{
		set_directions(&horizontal, HORIZONTAL);
		draw_line(&data->minimaps_layer, RGB_DARK_GREEN, data->player.position, horizontal.intersept_point);
		*ray = horizontal;
		return ;
	}
	set_directions(&vertical, VERTICAL);
	draw_line(&data->minimaps_layer, RGB_DARK_GREEN, data->player.position, vertical.intersept_point);
	*ray = vertical;
}
