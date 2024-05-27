/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:57:01 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/27 20:04:19 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#define						var  		 	 	 	 	 	 10

void	check_variable(char *varname, char *value, int i)
{
	t_data	*data;
	int		fd;

	(void)i;
	(void)varname;
	data = data_hook(NULL);
	fd = open(value, O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) == -1)
	{
		if (fd != -1)
			close(fd);
		put_error_sys(value);
		safe_exit(1);
	}
	*(((char **)&data->scene_info.NORTH_texture + i)) = safe_strdup(value);
}

void	handle_line(char *line, int i)
{
	char	*value;

	if (i < 6)
	{
		if (safe_strchr(line, ' ') == NULL)
			eput_error("bad define line", line, 1);
		line = str_skip(line, " ");
		value = ft_strchr(line, ' ');
		*value = '\0';
		value++;
		value = str_skip(value, " ");
		if (*line == '\0')
			eput_error("found empty name", line, 1);
		if ((i == 0 && str_equal(line, "NO") == 0)
			|| (i == 1 && str_equal(line, "SO") == 0)
			|| (i == 2 && str_equal(line, "WE") == 0)
			|| (i == 3 && str_equal(line, "EA") == 0)
			|| (i == 4 && str_equal(line, "F") == 0)
			|| (i == 5 && str_equal(line, "C") == 0))
		eput_error("bad name or sort is not match", line, 1);
		ft_printf("checking %s=%s\n", line, value);/// line = 
		if (i >= 0 && i <= 3)
			check_variable(line, value, i);
		else if (i > 3 && i <= 5)
			check_color(line, value, i);
		*value = ' ';
	}
	data_hook(NULL)->lines = append_2d(data_hook(NULL)->lines, line);
}

// void	check_lines()
// {
// 	t_data	*data;
// 	char	**lines;
// 	char	*line;
// 	size_t	i;

// 	data = data_hook(NULL);
// 	lines = data->lines;
// 	i = 0;
// 	while (lines && lines[i])
// 	{
// 		line = lines[i];
// 		if (i >= 0 && i <= 3)
// 			check_variable(line, i);
// 		else if (i > 3 && i <= 5)
// 			check_color(line, i);
// 		i++;
// 	}
// }

void	init_lines(int fd)
{
	t_data	*data;
	char	*line;
	size_t	i;

	data = data_hook(NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strchr(line, '\n'))
			*ft_strchr(line, '\n') = '\0';
		if (safe_strlen(line) == 0 && i > 6)
			eput_error("invalid newline place", "newline", 1);
		if (safe_strlen(line) > 0)
		{
			// ft_printf("[%s][%d]\n", line, i);
			handle_line(line, i);
			i++;
		}
		line = get_next_line(fd);
	}
	close(fd);
}
