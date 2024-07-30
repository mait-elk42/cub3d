/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:24:34 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/30 17:26:33 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	handle_door(t_data *data, int keycode)
{
	t_vector2	ppos;
	t_vector	pos;
	t_vector	check;

	if (keycode != KEY_E)
		return ;
	ppos = data->player.position;
	pos = (t_vector){(ppos.x) / TILE_SIZE, ((ppos.y) / TILE_SIZE)};
	check = (t_vector){0, 0};
	if (floor(data->player.angle) >= 60 && floor(data->player.angle) <= 120)
		check.y = 1;
	if (floor(data->player.angle) >= 240 && floor(data->player.angle) <= 300)
		check.y = -1;
	if (floor(data->player.angle) >= 330 || floor(data->player.angle) <= 30)
		check.x = 1;
	if (floor(data->player.angle) >= 150 && floor(data->player.angle) <= 210)
		check.x = -1;
	if (check.x != 0 || check.y != 0)
	{
		if (data->map[pos.y + check.y][pos.x + check.x] == 'D')
			data->map[pos.y + check.y][pos.x + check.x] = 'd';
		else if (data->map[pos.y + check.y][pos.x + check.x] == 'd')
			data->map[pos.y + check.y][pos.x + check.x] = 'D';
	}
}
