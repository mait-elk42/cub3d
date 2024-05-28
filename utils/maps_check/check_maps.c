/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:40:46 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/28 18:21:18 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
		if ((pos.y == 0 && safe_strchr(maps[pos.y], '0')) || (pos.x == 0 && maps[pos.y][pos.x] == '0'))
			eput_error("error maps in the rounds", maps[pos.y], 1);
		if (pos.y > 0 && (safe_strlen(maps[pos.y -1]) < (size_t)pos.x || maps[pos.y -1][pos.x] == ' '))
			eput_error("error maps in the TOP", maps[pos.y], 1);
		if (safe_strlen(maps[pos.y +1]) < (size_t)pos.x || maps[pos.y +1][pos.x] == ' ')
			eput_error("error maps in the DOWN", maps[pos.y], 1);
		if (pos.x > 0 && maps[pos.y][pos.x -1] == ' ')
			eput_error("error maps in the LEFT", maps[pos.y], 1);
		if (maps[pos.y][pos.x +1] == ' ')
			eput_error("error maps in the RIGHT", maps[pos.y], 1);
	}
}

void	check_maps(void)
{
	t_data	*data;
	char	**maps;
	t_vector2	pos;
	bool		found_plr;

	data = data_hook(NULL);
	maps = data->maps;
	pos.y = 0;
	found_plr = false;
	while (maps[pos.y])
	{
		pos.x = 0;
		while (maps[pos.y][pos.x])
		{
			maps_iteri(maps, pos, &found_plr);
			pos.x++;
		}
		pos.y++;
	}
}
