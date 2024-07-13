/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_instractions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:06:52 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/13 15:45:32 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_bgd(t_image *image, int ceil_color, int floor_color)
{
	t_vector	i;
	int			color;

	i.y = 0;
	color = ceil_color;
	while (i.y < image->sizey)
	{
		i.x = 0;
		while (i.x < image->sizex)
		{
			t_image_update_pixel(image, i.x, i.y, color);
			i.x++;
		}
		if (i.y == (image->sizey / 2))
			color = floor_color;
		i.y++;
	}
}

int	get_color_distance(t_ray ray, int color)
{
	unsigned char	r,g,b;
	char	*defc = (char *)&color;

	if ((ray.distance / 30) < 1)
		ray.distance = 1;
	r = defc[0];
	g = defc[1];
	b = defc[2];

	r /= (ray.distance / 30);
	g /= (ray.distance / 30);
	b /= (ray.distance / 30);
	
	return (0 << 24 | r << 16 | g << 8 | b);
}

void	put_wall(t_data *data, int i, t_ray *ray)
{
	int wallHeight = (WIN_HEIGHT / ray->distance) * TILE_SIZE;
	int	top = (WIN_HEIGHT / 2) - (wallHeight / 2);
	int btm = top + wallHeight;
	// draw_line(&data->scene_layer, 0x79c0ff, (t_vector2) {i, 0}, (t_vector2) {i, top});
	if (ray->distance != 2147483647.0)
	{
		if (ray->side == HORIZONTAL)
		{
			t_image t = data->texture_so;
			if (ray->direction == NORTH)
				t = data->texture_no;
			float px = ray->intersept_point.x / (float)TILE_SIZE;
			int texture_offset_X = (int)(px * t.sizex) % t.sizex;
			int y = top;
			if (y < 0)
				y += -top;
			if (btm > WIN_HEIGHT)
				btm = WIN_HEIGHT;
			while (y < btm)
			{
				// if (y > WIN_HEIGHT)
				// 	break ;
				float proportion = (float)(y - top) / wallHeight;
				int texture_offset_Y = (int)(proportion * t.sizey) % t.sizey;
				int c = t.buffer[texture_offset_Y * t.sizex + texture_offset_X];
				// c = get_color_distance(ray-> c); // useful
					t_image_update_pixel(&data->scene_layer, i, y, c);
				y++;
			}
		}
		else if (ray->side == VERTICAL)
		{
			t_image t = data->texture_ea;
			if (ray->direction == WEST)
				t = data->texture_we;
			float px = ray->intersept_point.y / (float)TILE_SIZE;
			int texture_offset_X = (int)(px * t.sizex) % t.sizex;
			int y = top;
			if (y < 0)
				y += -top;
			if (btm > WIN_HEIGHT)
				btm = WIN_HEIGHT;
			while (y < btm)
			{
				float proportion = (float)(y - top) / wallHeight;
				int texture_offset_Y = (int)(proportion * t.sizey) % t.sizey;
				int c = t.buffer[texture_offset_Y * t.sizex + texture_offset_X];
				// c = get_color_distance(ray-> c); // useful
				t_image_update_pixel(&data->scene_layer, i, y, c);
				y++;
			}
			// draw_line(&data->scene_layer,  0x00309E, (t_vector2) {i, top}, (t_vector2) {i, btm});
		}
	}
	// draw_line(&data->scene_layer, 0xe5c359, (t_vector2) {i, btm}, (t_vector2) {i, WIN_HEIGHT});

}