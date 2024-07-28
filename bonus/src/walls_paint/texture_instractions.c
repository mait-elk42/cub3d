/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_instractions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:06:52 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/28 19:14:16 by aabouqas         ###   ########.fr       */
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

t_image	wall_side(t_ray *ray, float *xunit)
{
	t_data		*data;
	t_image		t;
	t_vector2	intercept;

	data = data_hook(NULL);
	intercept = ray->intercept;
	if (ray->side == HORIZONTAL)
	{
		t = data->texture_so;
		if (ray->direction == NORTH)
			t = data->texture_no;
		*xunit = intercept.x / (float)TILE_SIZE;
	}
	else
	{
		t = data->texture_ea;
		if (ray->direction == WEST)
			t = data->texture_we;
		*xunit = intercept.y / (float)TILE_SIZE;
	}
	*xunit -= (int)(*xunit);
	if (ray->hit_door)
		t = data->texture_door;
	return (t);
}

void	put_wall(t_data *data, int i, t_ray *ray)
{
	t_wall_text	w;

	// if (ray->hit_door)
	// 	return ;
	w.wallheight = (WIN_HEIGHT / ray->distance) * 40;
	w.top = (WIN_HEIGHT / 2) - (w.wallheight / 2);
	w.btm = w.top + w.wallheight;
	w.t = wall_side(ray, &w.xunit);
	w.t_offset.x = (int)(w.xunit * w.t.width);
	if (ray->direction == SOUTH || ray->direction == WEST)
		w.t_offset.x = w.t.width - (int)(w.xunit * w.t.width);
	w.y = imax(0, w.top);
	w.btm = imin(WIN_HEIGHT, w.btm);
	while (w.y < w.btm)
	{
		w.yunit = (float)(w.y - w.top) / w.wallheight;
		w.t_offset.y = (int)(w.yunit * w.t.height) % w.t.height;
		w.color = w.t.buffer[(((w.t_offset.y) * w.t.width) + (w.t_offset.x)) % (w.t.width * w.t.height)];
		t_image_update_pixel(&data->scene_layer, i, w.y, w.color);
		w.y++;
	}
}
