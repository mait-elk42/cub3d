/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:55:05 by mait-elk          #+#    #+#             */
/*   Updated: 2024/08/06 12:55:06 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	init_face_1(t_vector2 *points, t_vector2 offset, int size, int angle)
{
	float	x;
	float	y;

	t_image_clear_color(&data_hook(NULL)->scene_layer, 0xff000000);
	x = (cos(deg_to_rad(angle)) * size) + offset.x;
	y = (sin(deg_to_rad(angle)) * size) + offset.y;
	points[0] = (t_vector2){x, y};
	x = (cos(deg_to_rad(angle + 90)) * size) + offset.x;
	y = (sin(deg_to_rad(angle + 90)) * size) + offset.y;
	points[1] = (t_vector2){x, y};
	x = (cos(deg_to_rad(angle + 180)) * size) + offset.x;
	y = (sin(deg_to_rad(angle + 180)) * size) + offset.y;
	points[2] = (t_vector2){x, y};
	x = (cos(deg_to_rad(angle + 270)) * size) + offset.x;
	y = (sin(deg_to_rad(angle + 270)) * size) + offset.y;
	points[3] = (t_vector2){x, y};
}

void	init_face_2(t_vector2 *points, t_vector2 offset, int size, int angle)
{
	float	x;
	float	y;

	x = ((size / 2) + cos(deg_to_rad(angle)) * size) + offset.x;
	y = ((size / 2) + sin(deg_to_rad(angle)) * size) + offset.y;
	points[4] = (t_vector2){x, y};
	x = ((size / 2) + cos(deg_to_rad(angle + 90)) * size) + offset.x;
	y = ((size / 2) + sin(deg_to_rad(angle + 90)) * size) + offset.y;
	points[5] = (t_vector2){x, y};
	x = ((size / 2) + cos(deg_to_rad(angle + 180)) * size) + offset.x;
	y = ((size / 2) + sin(deg_to_rad(angle + 180)) * size) + offset.y;
	points[6] = (t_vector2){x, y};
	x = ((size / 2) + cos(deg_to_rad(angle + 270)) * size) + offset.x;
	y = ((size / 2) + sin(deg_to_rad(angle + 270)) * size) + offset.y;
	points[7] = (t_vector2){x, y};
}

void	put_cub(t_data *data, t_vector2 offset, int size)
{
	static float	angle;
	t_vector2		points[8];
	void			*win_ptr;
	void			*mlx_ptr;

	mlx_ptr = data->mlx.mlx_ptr;
	win_ptr = data->mlx.window_ptr;
	init_face_1(points, offset, size, angle);
	init_face_2(points, offset, size, angle);
	draw_line(&data->scene_layer, 0xff0000, points[0], points[1]);
	draw_line(&data->scene_layer, 0xff0000, points[1], points[2]);
	draw_line(&data->scene_layer, 0xff0000, points[2], points[3]);
	draw_line(&data->scene_layer, 0xff0000, points[3], points[0]);
	draw_line(&data->scene_layer, 0xff0000, points[4], points[5]);
	draw_line(&data->scene_layer, 0xff0000, points[5], points[6]);
	draw_line(&data->scene_layer, 0xff0000, points[6], points[7]);
	draw_line(&data->scene_layer, 0xff0000, points[7], points[4]);
	draw_line(&data->scene_layer, 0xff0000, points[0], points[4]);
	draw_line(&data->scene_layer, 0xff0000, points[1], points[5]);
	draw_line(&data->scene_layer, 0xff0000, points[2], points[6]);
	draw_line(&data->scene_layer, 0xff0000, points[3], points[7]);
	mlx_put_image_to_window(mlx_ptr, win_ptr, data->scene_layer.img_ptr, 0, 0);
	if (angle > 360)
		angle = 0;
	angle += 0.9;
}
