/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:57:01 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/25 20:05:58 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_lines(char *file_name)
{
	t_data	*data;
	char	*line;
	int		fd;

	data = data_hook(NULL);
	fd = open(file_name, O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) == -1)
	{
		((fd != -1) && close(fd));
		(put_error_syscall(file_name), exit(1));
	}
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
		free((char *)((size_t)line * (*line == 0 || *line == '\n')));
	}
	close(fd);
}


void	check_lines()
{
	t_scene_info	*scene_info;

	scene_info = &data_hook(NULL)->scene_info;
	scene_info->CEILING_color = (char *)100;
}