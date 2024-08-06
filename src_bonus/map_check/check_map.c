/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:40:46 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/23 10:29:00 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

bool	valid_roundwall(char *mapwall)
{
	while (mapwall && *mapwall)
	{
		if (safe_strchr("0NSEWD", *mapwall) != NULL)
			return (false);
		mapwall++;
	}
	return (true);
}

bool	is_valid_door(t_vector pos)
{
	t_data	*data;
	char	**map;

	data = data_hook(NULL);
	map = data->map;
	if (map[pos.y][pos.x] == 'D')
	{
		if (map[pos.y][pos.x - 1] == '1' && map[pos.y][pos.x + 1] == '1'
			&& map[pos.y - 1][pos.x] == '0' && map[pos.y + 1][pos.x] == '0')
			return (true);
		else if (map[pos.y][pos.x - 1] == '0' && map[pos.y][pos.x + 1] == '0'
			&& map[pos.y - 1][pos.x] == '1' && map[pos.y + 1][pos.x] == '1')
			return (true);
		else
			return (print(2, "Door error", 1), false);
	}
	return (true);
}

void	map_iteri(char **map, t_vector pos, bool *found_plr)
{
	if (safe_strchr(" 01NSEWD", map[pos.y][pos.x]) == NULL)
		eput_error("undefined character", map[pos.y], 1);
	if (safe_strchr("NSEW", map[pos.y][pos.x]) != NULL)
	{
		if (*found_plr == true)
			eput_error("duplicated player", map[pos.y], 1);
		*found_plr = true;
	}
	if (safe_strchr("0NSEWD", map[pos.y][pos.x]) != NULL)
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
	while (data->map && data->map[pos.y])
	{
		pos.x = 0;
		while (data->map && data->map[pos.y][pos.x])
		{
			if (pos.y != 0 && pos.x != 0)
			{
				if (is_valid_door(pos) == false)
					safe_exit(1);
			}
			map_iteri(data->map, pos, &found_plr);
			pos.x++;
		}
		pos.y++;
	}
	if (found_plr == false)
		eput_error("missing player", "[map]", 1);
}
