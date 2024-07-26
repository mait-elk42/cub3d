/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_instractions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:06:52 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/26 20:36:19 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	put_bgd(t_image *image, int ceil_color, int floor_color)
{
	t_vector	i;
	int			color;

	i.y = 0;
	color = ceil_color;
	while (i.y < image->height)
	{
		i.x = 0;
		while (i.x < image->width)
		{
			t_image_update_pixel(image, i.x, i.y, color);
			i.x++;
		}
		if (i.y == (image->height / 2))
			color = floor_color;
		i.y++;
	}
}

t_image	wall_side(t_ray *ray, float *pxunit)
{
	t_data		*data;
	t_image		t;
	t_vector2	intercept;

	data = data_hook(NULL);
	intercept = ray->intercept;
	// printf("%s\n", ray->hit_door ? "hitted door" : "nah");
	// if (ray->hit_door)
	// {
	// 	// printf("adasdasd\n");
	// 	// printf("11 >> %f %f\n", ray->intercept.x, ray->intercept.y);
	// 	// printf("22 >> %f %f\n", ray->door_intercept.x, ray->door_intercept.y);
	// 	intercept = ray->door_intercept;
	// }
	if (ray->side == HORIZONTAL)
	{
		t = data->texture_so;
		if (ray->direction == NORTH)
			t = data->texture_no;
		*pxunit = intercept.x / (float)TILE_SIZE;

	}
	else
	{
		t = data->texture_ea;
		if (ray->direction == WEST)
			t = data->texture_we;
		*pxunit = intercept.y / (float)TILE_SIZE;
	}
	if (ray->hit_door)
		t = data->texture_door;
	return (t);
}

void	put_wall(t_data *data, int i, t_ray *ray)
{
	t_wall_text	w;

	// if (ray->hit_door == true)
	// 	return ;
	w.wallheight = (WIN_HEIGHT / ray->distance) * 40;
	// if (ray->hit_door)
	// 	w.wallheight = (WIN_HEIGHT / ray->door_distance) * 40;
	w.top = (WIN_HEIGHT / 2) - (w.wallheight / 2);
	w.btm = w.top + w.wallheight;
	w.t = wall_side(ray, &w.pxunit);
	w.y = w.top;
	if (ray->direction == SOUTH || ray->direction == WEST)
		w.t_offset.x = w.t.width - (int)(w.pxunit * w.t.width) % w.t.width;
	else
		w.t_offset.x = (int)(w.pxunit * w.t.width) % w.t.width;
	// if (ray->hitchar == 'D')
	// 	w.y += 50;
	if (w.y < 0)
		w.y = 0;
	if (w.btm > WIN_HEIGHT)
		w.btm = WIN_HEIGHT;
	while (w.y < w.btm)
	{
		w.unit = (float)(w.y - w.top) / w.wallheight;
		w.t_offset.y = (int)(w.unit * w.t.height) % w.t.height;
		if (ray->hit_door)
			w.color = w.t.buffer[(((w.t_offset.y) * w.t.width) + (w.t_offset.x - (data->n * TILE_SIZE))) % (w.t.width * w.t.height)];
		else
			w.color = w.t.buffer[(((w.t_offset.y) * w.t.width) + (w.t_offset.x)) % (w.t.width * w.t.height)];
		t_image_update_pixel(&data->scene_layer, i, w.y, w.color);
		w.y++;
	}
}
