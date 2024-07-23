/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:40:46 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/17 12:43:29 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	valid_roundwall(char *mapwall)
{
	while (mapwall && *mapwall)
	{
		if (safe_strchr("0NSEW", *mapwall) != NULL)
			return (false);
		mapwall++;
	}
	return (true);
}

void	map_iteri(char **map, t_vector pos, bool *found_plr)
{
	if (safe_strchr(" 01NSEW", map[pos.y][pos.x]) == NULL)
		eput_error("undefined character", map[pos.y], 1);
	if (safe_strchr("NSEW", map[pos.y][pos.x]) != NULL)
	{
		if (*found_plr == true)
			eput_error("duplicated player", map[pos.y], 1);
		*found_plr = true;
	}
	if (safe_strchr("0NSEW", map[pos.y][pos.x]) != NULL)
	{
		if ((pos.y == 0 && valid_roundwall(map[pos.y]) == false)
			|| (pos.x == 0 && map[pos.y][pos.x] == '0'))
			eput_error("must be rounded by walls", map[pos.y], 1);
		if ((pos.y > 0 && (safe_strlen(map[pos.y -1]) < (size_t)pos.x))
			|| map[pos.y -1][pos.x] == ' ' || map[pos.y - 1][pos.x] == '\0')
			eput_error("must be rounded by walls", map[pos.y], 1);
		if (safe_strlen(map[pos.y +1]) < (size_t)pos.x
			|| map[pos.y +1][pos.x] == ' ' || map[pos.y + 1][pos.x] == '\0')
			eput_error("must be rounded by walls", map[pos.y], 1);
		if (pos.x > 0 && (map[pos.y][pos.x -1] == ' '
			|| map[pos.y][pos.x - 1] == '\0'))
			eput_error("must be rounded by walls", map[pos.y], 1);
		if (map[pos.y][pos.x +1] == ' ' || map[pos.y][pos.x +1] == '\0')
			eput_error("must be rounded by walls", map[pos.y], 1);
	}
}

void	check_map(void)
{
	t_data		*data;
	t_vector	pos;
	bool		found_plr;

	data = data_hook(NULL);
	pos.y = 0;
	found_plr = false;
	while (data->map[pos.y])
	{
		pos.x = 0;
		while (data->map[pos.y][pos.x])
		{
			map_iteri(data->map, pos, &found_plr);
			pos.x++;
		}
		pos.y++;
	}
	if (found_plr == false)
		eput_error("missing player", "[map]", 1);
}
