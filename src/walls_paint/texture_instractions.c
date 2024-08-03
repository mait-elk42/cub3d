/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_instractions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:06:52 by mait-elk          #+#    #+#             */
/*   Updated: 2024/08/03 13:09:09 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
	t_data	*data;
	t_image	t;

	data = data_hook(NULL);
	if (ray->side == HORIZONTAL)
	{
		t = data->texture_so;
		if (ray->direction == NORTH)
			t = data->texture_no;
		*pxunit = ray->intercept.x / (float)TILE_SIZE;
	}
	else
	{
		t = data->texture_ea;
		if (ray->direction == WEST)
			t = data->texture_we;
		*pxunit = ray->intercept.y / (float)TILE_SIZE;
	}
	*pxunit -= floor(*pxunit);
	return (t);
}

void	put_wall(t_data *data, int i, t_ray *ray)
{
	t_wall_text	w;

	w.wallheight = (WIN_HEIGHT / ray->distance) * 40;
	w.top = (WIN_HEIGHT / 2) - (w.wallheight / 2);
	w.btm = w.top + w.wallheight;
	w.t = wall_side(ray, &w.pxunit);
	w.y = w.top;
	if (ray->direction == SOUTH || ray->direction == WEST)
		w.t_offset.x = w.t.width - (int)(w.pxunit * w.t.width);
	else
		w.t_offset.x = (int)(w.pxunit * w.t.width);
	if (w.y < 0)
		w.y = 0;
	if (w.btm > WIN_HEIGHT)
		w.btm = WIN_HEIGHT;
	while (w.y < w.btm)
	{
		w.unit = (float)(w.y - w.top) / w.wallheight;
		w.t_offset.y = (int)(w.unit * w.t.height) % w.t.height;
		w.color = w.t.buffer[((w.t_offset.y * w.t.width)
				+ (w.t_offset.x)) % (w.t.width * w.t.height)];
		t_image_update_pixel(&data->scene_layer, i, w.y, w.color);
		w.y++;
	}
}
