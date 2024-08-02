/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 17:24:34 by mait-elk          #+#    #+#             */
/*   Updated: 2024/08/01 19:49:03 by mait-elk         ###   ########.fr       */
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

static int	mmpvertidoor(t_vector2 ppos, t_size sc, t_vector2 targ)
{
	t_data		*data;
	t_vector	grid;
	int			color;

	data = data_hook(NULL);
	grid.x = ppos.x / TILE_SIZE;
	grid.y = ppos.y / TILE_SIZE;
	color = 0xff0000;
	if (ppos.x > 0 && ppos.x < sc.width && ppos.y > 0 && ppos.y < sc.height)
	{
		color -= (data->map[grid.y][grid.x] == 'd') * 16646400;
		if (safe_strchr("dD", data->map[grid.y][grid.x]))
		{
			if (iinrange((int)ppos.y % TILE_SIZE,
					(TILE_SIZE / 2 - 3), (TILE_SIZE / 2 + 3))
				&& data->map[grid.y][grid.x - 1] == '1'
				&& data->map[grid.y][grid.x + 1] == '1')
			{
				t_image_update_pixel(
					&data->minimap_layer, targ.x, targ.y, color);
				return (1);
			}
		}
	}
	return (0);
}

static int	mmphoridoor(t_vector2 ppos, t_size sc, t_vector2 targ)
{
	t_data		*data;
	t_vector	grid;
	int			color;

	data = data_hook(NULL);
	grid.x = ppos.x / TILE_SIZE;
	grid.y = ppos.y / TILE_SIZE;
	color = 0xff0000;
	if (ppos.x > 0 && ppos.x < sc.width && ppos.y > 0 && ppos.y < sc.height)
	{
		color -= (data->map[grid.y][grid.x] == 'd') * 16646400;
		if (safe_strchr("dD", data->map[grid.y][grid.x]))
		{
			if (iinrange((int)ppos.x % TILE_SIZE,
					(TILE_SIZE / 2 - 3), (TILE_SIZE / 2 + 3))
				&& data->map[grid.y - 1][grid.x] == '1'
				&& data->map[grid.y + 1][grid.x] == '1')
			{
				t_image_update_pixel(
					&data->minimap_layer, targ.x, targ.y, color);
				return (1);
			}
		}
	}
	return (0);
}

int	is_door_minimap(t_vector2 ppos, t_size sc, t_vector2 targ)
{
	t_data		*data;
	char		**map;
	t_vector	grid;

	data = data_hook(NULL);
	map = data->map;
	grid.x = ppos.x / TILE_SIZE;
	grid.y = ppos.y / TILE_SIZE;
	if (grid.y > 0 && grid.y < (int)(sc.height / TILE_SIZE))
	{
		if (mmphoridoor(ppos, sc, targ))
			return (true);
	}
	if (grid.x > 0 && grid.x < (int)(sc.width / TILE_SIZE))
	{
		if (mmpvertidoor(ppos, sc, targ))
			return (true);
	}
	return (0);
}
