/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:57:01 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/29 09:59:04 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	check_texture(char *varname, char *value)
{
	t_data	*data;
	int		fd;

	(void)varname;
	data = data_hook(NULL);
	if (check_file_ext(value, ".xpm") == false)
		safe_exit(1);
	fd = open(value, O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) == -1)
	{
		if (fd != -1)
			close(fd);
		eput_error_sys(value, 1);
	}
	close(fd);
	if (str_equal(varname, "NO"))
		data->scene_info.north_texture = value;
	if (str_equal(varname, "SO"))
		data->scene_info.south_texture = value;
	if (str_equal(varname, "WE"))
		data->scene_info.west_texture = value;
	if (str_equal(varname, "EA"))
		data->scene_info.east_texture = value;
}

static bool	is_valid_name_index(char *name, int i)
{
	if ((i == 0 && str_equal(name, "NO"))
		|| (i == 1 && str_equal(name, "SO"))
		|| (i == 2 && str_equal(name, "WE"))
		|| (i == 3 && str_equal(name, "EA"))
		|| (i == 4 && str_equal(name, "F"))
		|| (i == 5 && str_equal(name, "C")))
		return (true);
	return (false);
}

static bool	is_valid_line(char *line, int i)
{
	char	*value;

	data_hook(NULL)->lines = append_2d(data_hook(NULL)->lines, line);
	if (i < 6)
	{
		if (safe_strchr(line, ' ') == NULL)
			eput_error("bad define line", line, 1);
		line = str_skip_wsp(line);
		value = ft_strchr(line, ' ');
		*value = '\0';
		value = str_skip_wsp(value +1);
		if (*line == '\0')
			return (put_error("found empty name", line), false);
		if (!is_valid_name_index(line, i))
			return (put_error("bad name or sort", line), false);
		ft_printf("checking %s=%s\n", line, value);
		if (i >= 0 && i <= 3)
			check_texture(line, value);
		else if (i > 3 && i <= 5)
			check_color(line[0], value);
		*value = ' ';
	}
	else
		data_hook(NULL)->maps = append_2d(data_hook(NULL)->maps, line);
	return (true);
}

static void	check_empty()
{
	t_data	*data;

	data = data_hook(NULL);
	if (data->maps == NULL)
		eput_error("is empty", "[MAPS]", 1);
}

void	init_lines(void)
{
	t_data	*data;
	char	*line;
	size_t	i;

	data = data_hook(NULL);
	i = 0;
	line = get_next_line(data->fd_file_input);
	while (line)
	{
		if (ft_strchr(line, '\n'))
			*ft_strchr(line, '\n') = '\0';
		if (safe_strlen(line) > 0)
		{
			if (is_valid_line(line, i) == false)
				safe_exit(1);
			i++;
		}
		else if (free(line), i > 6)
			eput_error("invalid newline place", "newline", 1);
		line = get_next_line(data->fd_file_input);
	}
	close(data->fd_file_input);
	check_empty();
}
