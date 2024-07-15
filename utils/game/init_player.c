/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:22:25 by mait-elk          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/11 14:43:17 by aabouqas         ###   ########.fr       */
=======
/*   Updated: 2024/07/13 15:07:08 by mait-elk         ###   ########.fr       */
>>>>>>> 9f80157f39dcea3e2af4ddb0b5284d25570c0e7c
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
<<<<<<< HEAD
				if (maps[v.y][v.x] == 'E')
					player->angle = 0;
				if (maps[v.y][v.x] == 'S')
					player->angle = 90;
				if (maps[v.y][v.x] == 'W')
					player->angle = 180;
				if (maps[v.y][v.x] == 'N')
					player->angle = 270;
				maps[v.y][v.x] = '0';
				// player->position = (t_vector2){v.x * TILE_SIZE, v.y * TILE_SIZE};
				printf("player in coord : x%d y%d\n", v.x, v.y);
				player->position = (t_vector2){(v.x * TILE_SIZE ) + (TILE_SIZE / 2), (v.y * TILE_SIZE ) + (TILE_SIZE / 2)};
				printf("cam_player in coord : x%f y%f\n", player->position.x, player->position.y);
				
				
=======
				player->angle += 0 * (maps[v.y][v.x] == 'E');
				player->angle += 90 * (maps[v.y][v.x] == 'S');
				player->angle += 180 * (maps[v.y][v.x] == 'W');
				player->angle += 270 * (maps[v.y][v.x] == 'N');
				maps[v.y][v.x] = 'P';
				player->position.x = (v.x * TILE_SIZE) + (TILE_SIZE / 2);
				player->position.y = (v.y * TILE_SIZE) + (TILE_SIZE / 2);
>>>>>>> 9f80157f39dcea3e2af4ddb0b5284d25570c0e7c
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
