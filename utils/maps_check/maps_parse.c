/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:57:01 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/27 17:11:08 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	handle_line(char *line, int i)
{
	char	*varname;

	if (i < 6)
	{
		if (safe_strchr(line, ' ') == NULL)
			eput_error_custom("bad define line", line, 1);
		varname = ft_strchr(line, ' ');
		*varname = '\0';
		if (*line == '\0')
			eput_error_custom("found empty name", line, 1);
		if ((i == 0 && str_equal(line, "NO") == 0)
			|| (i == 1 && str_equal(line, "SO") == 0)
			|| (i == 2 && str_equal(line, "WE") == 0)
			|| (i == 3 && str_equal(line, "EA") == 0))
		eput_error_custom("bad name or sort is not match", line, 1);
	}
	else
	{
		if (*str_skip(line, "01 NSEW") != '\0')
		{
			line = str_skip(line, "01 NSEW");
			*(line +1) = '\0';
			eput_error_custom("bad character inside maps", line, 1);
		}
	}
}

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
			eput_error_custom("invalid newline place", "newline", 1);
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

void	check_variable(char *line, int i)
{
	t_data	*data;
	char	*del;
	char	*path;
	int		fd;

	data = data_hook(NULL);
	if (safe_strchr(line, ' ') == NULL)
		safe_exit(put_error("invalid variable", line));
	del = safe_strchr(line, ' ');
	if (ft_iswhite(*(del +1)))
	{
		put_error("expected single w-space after name", line);
		safe_exit(1);
	}
	*del = '\0';
	path = del +1;
	if ((i == 0 && str_equal(line, "NO") == 0)
		|| (i == 1 && str_equal(line, "SO") == 0)
		|| (i == 2 && str_equal(line, "WE") == 0)
		|| (i == 3 && str_equal(line, "EA") == 0))
	{
		put_error("bad name or sort is not match", line);
		safe_exit(1);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) == -1)
	{
		if (fd != -1)
			close(fd);
		put_error_sys(path);
		safe_exit(1);
	}
	*(((char **)&data->scene_info.NORTH_texture + i)) = safe_strdup(path);
}

void	check_lines()
{
	t_data	*data;
	char	**lines;
	char	*line;
	size_t	i;

	data = data_hook(NULL);
	lines = data->lines;
	i = 0;
	while (lines && lines[i])
	{
		line = lines[i];
		// printf("[%s]\n", line);
		if (i >= 0 && i <= 3)
			check_variable(line, i);
		else if (i > 3 && i <= 5)
			check_color(line, i);
		i++;
	}
}
