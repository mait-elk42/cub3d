/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:22:25 by mait-elk          #+#    #+#             */
/*   Updated: 2024/06/07 19:16:43 by aabouqas         ###   ########.fr       */
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
				if (maps[v.y][v.x] == 'E')
					player->angle = 0;
				if (maps[v.y][v.x] == 'S')
					player->angle = 90;
				if (maps[v.y][v.x] == 'W')
					player->angle = 180;
				if (maps[v.y][v.x] == 'N')
					player->angle = 270;
				maps[v.y][v.x] = '0';
				player->pos = (t_vector2){v.x * MAP_SIZE, v.y * MAP_SIZE};
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
