/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:57:01 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/26 12:23:53 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_lines(int fd)
{
	t_data	*data;
	char	*line;

	data = data_hook(NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (*line != 0 && *line != '\n')
		{
			if (ft_strchr(line, '\n'))
				*ft_strchr(line, '\n') = '\0';
			data->lines = append_2d(data->lines, line);
		}
		if (*line == 0 || *line == '\n')
			free(line);
	}
	close(fd);
}


void	check_lines()
{
	t_scene_info	*scene_info;

	scene_info = &data_hook(NULL)->scene_info;
	scene_info->CEILING_color = (char *)100;
}
