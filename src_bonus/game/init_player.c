/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:22:25 by mait-elk          #+#    #+#             */
/*   Updated: 2024/08/02 11:10:56 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	init_angle_pos(char **map, t_player *player)
{
	t_vector	v;

	v.y = 0;
	while (map[v.y])
	{
		v.x = 0;
		while (map[v.y][v.x])
		{
			if (safe_strchr("NEWS", map[v.y][v.x]))
			{
				player->angle += 0 * (map[v.y][v.x] == 'E');
				player->angle += 90 * (map[v.y][v.x] == 'S');
				player->angle += 180 * (map[v.y][v.x] == 'W');
				player->angle += 270 * (map[v.y][v.x] == 'N');
				map[v.y][v.x] = 'P';
				player->position.x = (v.x * TILE_SIZE) + (TILE_SIZE / 2);
				player->position.y = (v.y * TILE_SIZE) + (TILE_SIZE / 2);
				data_hook(NULL)->p_data.player_pos = v;
				data_hook(NULL)->p_data.player_angle = player->angle;
			}
			v.x++;
		}
		v.y++;
	}
}

void	put_player_shape(double size)
{
	t_data		*data;
	t_vector2	player_pos;
	t_vector2	p1;
	t_vector2	p2;
	t_vector2	p3;

	data = data_hook(NULL);
	player_pos = data->player.position;
	p1.x = cos(deg_to_rad(270 - 120)) * size + ((WIN_WIDTH * MPSIZE) / 2);
	p1.y = sin(deg_to_rad(270 - 120)) * size + ((WIN_WIDTH * MPSIZE) / 2);
	p2.x = cos(deg_to_rad(270 + 120)) * size + ((WIN_WIDTH * MPSIZE) / 2);
	p2.y = sin(deg_to_rad(270 + 120)) * size + ((WIN_WIDTH * MPSIZE) / 2);
	p3.x = cos(deg_to_rad(270)) * size + ((WIN_WIDTH * MPSIZE) / 2);
	p3.y = sin(deg_to_rad(270)) * size + ((WIN_WIDTH * MPSIZE) / 2);
	draw_line(&data->minimap_layer, 0xff0000, p1, p3);
	draw_line(&data->minimap_layer, 0xff0000, p2, p3);
}

void	init_player(t_data *data)
{
	init_angle_pos(data->map, &data->player);
	data->player.hand_frames[0] = t_image_load_xpm("textures/weapon/0.xpm");
	data->player.hand_frames[1] = t_image_load_xpm("textures/weapon/1.xpm");
	data->player.hand_frames[2] = t_image_load_xpm("textures/weapon/2.xpm");
	data->player.hand_frames[3] = t_image_load_xpm("textures/weapon/3.xpm");
	data->player.hand_frames[4] = t_image_load_xpm("textures/weapon/4.xpm");
}
