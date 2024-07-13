/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:22:25 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/13 15:07:08 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_angle_pos(char **maps, t_player *player)
{
	t_vector	v;

	v.y = 0;
	while (maps[v.y])
	{
		v.x = 0;
		while (maps[v.y][v.x])
		{
			if (safe_strchr("NEWS", maps[v.y][v.x]))
			{
				player->angle += 0 * (maps[v.y][v.x] == 'E');
				player->angle += 90 * (maps[v.y][v.x] == 'S');
				player->angle += 180 * (maps[v.y][v.x] == 'W');
				player->angle += 270 * (maps[v.y][v.x] == 'N');
				maps[v.y][v.x] = 'P';
				player->position.x = (v.x * TILE_SIZE) + (TILE_SIZE / 2);
				player->position.y = (v.y * TILE_SIZE) + (TILE_SIZE / 2);
			}
			v.x++;
		}
		v.y++;
	}
}

void	init_player(t_data *data)
{
	init_angle_pos(data->maps, &data->player);
}
