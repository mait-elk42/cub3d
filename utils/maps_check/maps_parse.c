/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:57:01 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/27 16:49:29 by mait-elk         ###   ########.fr       */
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
	{
		put_error_custom("invalid variable", line);
		safe_exit(1);
	}
	del = safe_strchr(line, ' ');
	if (ft_iswhite(*(del +1)))
	{
		put_error_custom("expected single w-space after name", line);
		safe_exit(1);
	}
	*del = '\0';
	path = del +1;
	if ((i == 0 && str_equal(line, "NO") == 0)
		|| (i == 1 && str_equal(line, "SO") == 0)
		|| (i == 2 && str_equal(line, "WE") == 0)
		|| (i == 3 && str_equal(line, "EA") == 0))
	{
		put_error_custom("bad name or sort is not match", line);
		safe_exit(1);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) == -1)
	{
		if (fd != -1)
			close(fd);
		put_error_syscall(path);
		safe_exit(1);
	}
	*(((char **)&data->scene_info.NORTH_texture + i)) = safe_strdup(path);
}

void	check_clrval_validation(char *color, char *name, int i)
{
	// char	*clr;

	(void)color;
	if ((i == 0 && str_equal(name, "C") == 0)
		|| (i == 3 && str_equal(name, "F") == 0))
	{
		put_error_custom("bad name or sort is not match", name);
		safe_exit(1);
	}
	// while (1)
	// {
	// 	clr = color;
	// 	while (color && *color != ',')
	// 		color++;
	// 	*color = '\0';
	// }
	
}

void	check_color(char *line, int i)
{
	t_data	*data;
	char	*del;
	char	*color;

	data = data_hook(NULL);
	// if (safe_strchr(line, ' ') == NULL)
	// {
	// 	put_error_custom("invalid color name", line);
	// 	safe_exit(1);
	// }
	del = safe_strchr(line, ' ');
	*del = '\0';
	color = del +1;
	color = str_skip(color, " \t");
	i = i+1;
	// if ((i == 4 && str_equal(line, "F") == 0)
	// 	|| (i == 5 && str_equal(line, "C") == 0))
	// {
	// 	put_error_custom("bad name or sort is not match", line);
	// 	safe_exit(1);
	// }
	// check_clrval_validation(color, line, i);
	//
	// if (*str_skip(color, "0123456789,") != '\0')
	// {
	// 	put_error_custom("invalid color value", color);
	// 	safe_exit(1);
	// }
}

void	check_lines()
{
	t_data			*data;
	char			**lines;
	size_t			i;

	data = data_hook(NULL);
	lines = data->lines;
	i = 0;
	while (lines && lines[i])
	{
		if (i >= 0 && i <= 3)
			check_variable(lines[i], i);
		else if (i > 3 && i <= 5)
		{
			// i++;
			// check_color(lines[i], i);
		}
		else
			data->maps = append_2d(data->maps, lines[i]);
		i++;
	}
}
