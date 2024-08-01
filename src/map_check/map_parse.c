/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:57:01 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/20 16:44:17 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	check_texture_content(char	*filename)
{
	t_data	*data;
	void	*ptr;
	int		w;
	int		h;

	data = data_hook(NULL);
	ptr = mlx_xpm_file_to_image(data->mlx.mlx_ptr, filename, &w, &h);
	if (ptr == NULL)
		return (false);
	mlx_destroy_image(data->mlx.mlx_ptr, ptr);
	ptr = NULL;
	return (true);
}

void	check_texture(char *varname, char *value)
{
	t_data	*data;
	int		fd;

	data = data_hook(NULL);
	if (check_file_ext(value, ".xpm") == false)
		safe_exit(1);
	fd = open(value, O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) == -1)
	{
		((fd != -1) && close(fd));
		eput_error_sys(value, 1);
	}
	close(fd);
	if (check_texture_content(value) == false)
		eput_error("invalid xpm file content", value, 1);
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

static bool	is_valid_line(t_data *data, char *line, int i)
{
	char	*value;

	if (i < 6)
	{
		data->lines = append_2d(data->lines, line);
		if (safe_strchr(line, ' ') == NULL)
			eput_error("bad define line", line, 1);
		line = str_skip_wsp(line);
		value = ft_strchr(line, ' ');
		*value = '\0';
		value = str_skip_wsp(value + 1);
		if (*line == '\0')
			return (put_error("found empty name", line), false);
		if (!is_valid_name_index(line, i))
			return (put_error("bad name or sort", line), false);
		else if (i > 3 && i <= 5)
			check_color(line[0], value);
		return (true);
	}
	if ((int)safe_strlen(line) > data->scene_info.map_xsize)
		data->scene_info.map_xsize = safe_strlen(line);
	return (data->scene_info.map_ysize++, true);
}

void	init_lines(void)
{
	char	*line;
	size_t	i;

	i = 0;
	line = get_next_line(data_hook(NULL)->fd_file_input);
	while (line)
	{
		if (ft_strchr(line, '\n'))
			*ft_strchr(line, '\n') = '\0';
		if (safe_strlen(line) > 0)
		{
			if (is_valid_line(data_hook(NULL), line, i) == false)
				safe_exit(1);
			if (i >= 6)
				data_hook(NULL)->map = append_2d(data_hook(NULL)->map, line);
			i++;
		}
		else if (free(line), i > 6)
			eput_error("invalid newline place", "newline", 1);
		line = get_next_line(data_hook(NULL)->fd_file_input);
	}
	if (data_hook(NULL)->fd_file_input > 0)
		close (data_hook(NULL)->fd_file_input);
	if (data_hook(NULL)->map == NULL || *data_hook(NULL)->map == NULL)
		eput_error("is empty", "[map]", 1);
}
