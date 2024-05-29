/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:40:46 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/29 11:54:16 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	valid_roundwall(char *mapswall)
{
	while (mapswall && *mapswall)
	{
		if (safe_strchr("0NSEW", *mapswall) != NULL)
			return (false);
		mapswall++;
	}
	return (true);
}

void	maps_iteri(char **maps, t_vector2 pos, bool *found_plr)
{
	if (safe_strchr(" 01NSEW", maps[pos.y][pos.x]) == NULL)
		eput_error("undefined character", maps[pos.y], 1);
	if (safe_strchr("NSEW", maps[pos.y][pos.x]) != NULL)
	{
		if (*found_plr == true)
			eput_error("duplicated player", maps[pos.y], 1);
		*found_plr = true;
	}
	if (safe_strchr("0NSEW", maps[pos.y][pos.x]) != NULL)
	{
		if ((pos.y == 0 && valid_roundwall(maps[pos.y]) == false)
			|| (pos.x == 0 && maps[pos.y][pos.x] == '0'))
			eput_error("maps must be rounded by walls", maps[pos.y], 1);
		if (pos.y > 0 && (safe_strlen(maps[pos.y -1]) < (size_t)pos.x
				|| maps[pos.y -1][pos.x] == ' '))
			eput_error("maps must be rounded by walls", maps[pos.y], 1);
		if (safe_strlen(maps[pos.y +1]) < (size_t)pos.x
			|| maps[pos.y +1][pos.x] == ' ')
			eput_error("maps must be rounded by walls", maps[pos.y], 1);
		if (pos.x > 0 && maps[pos.y][pos.x -1] == ' ')
			eput_error("maps must be rounded by walls", maps[pos.y], 1);
		if (maps[pos.y][pos.x +1] == ' ')
			eput_error("maps must be rounded by walls", maps[pos.y], 1);
	}
}

void	find_wf(char c, bool *found_wall, bool *found_floor)
{
	if (c == '1')
		*found_wall = true;
	if (c == '0')
		*found_floor = true;
}

void	check_maps(void)
{
	t_data		*data;
	t_vector2	pos;
	bool		found_plr;
	bool		found_wall;
	bool		found_floor;

	data = data_hook(NULL);
	pos.y = 0;
	found_plr = false;
	found_wall = false;
	found_floor = false;
	while (data->maps[pos.y])
	{
		pos.x = 0;
		while (data->maps[pos.y][pos.x])
		{
			find_wf(data->maps[pos.y][pos.x], &found_wall, &found_floor);
			maps_iteri(data->maps, pos, &found_plr);
			pos.x++;
		}
		pos.y++;
	}
	if (found_floor == false || found_wall == false)
		eput_error("missing wall or floor", "[MAPS]", 1);
}
