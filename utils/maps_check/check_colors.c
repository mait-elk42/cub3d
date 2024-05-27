/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:18:41 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/27 19:43:22 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	set_value(char type, int number, int numbers)
{
	t_data	*data;

	data = data_hook(NULL);
	if (numbers > 3)
		safe_exit(put_error("invalid color name", "3 Numbers Required"));
	if (type == 'C')
	{
		if (numbers == 0)
			data->scene_info.CEILING_color.r = number;
		if (numbers == 1)
			data->scene_info.CEILING_color.g = number;
		if (numbers == 2) 
			data->scene_info.CEILING_color.b = number;
	}
	if (type == 'F')
	{
		if (numbers == 0)
			data->scene_info.FLOOR_color.r = number;
		if (numbers == 1)
			data->scene_info.FLOOR_color.g = number;
		if (numbers == 2)
			data->scene_info.FLOOR_color.b = number;
	}
}

int	char_times(char *str, char c)
{
	int	time;

	time = 0;
	while (str && *str)
	{
		time += *str == c;
		str++;
	}
	return (time);
}

int	atouch(char *str)
{
	size_t	i;
	int	number;

	number = 0;
	if (str == NULL || *str == '\0')
		safe_exit(put_error("Expected input 0 - 9", "Input"));
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		safe_exit(put_error("Expected input 0 - 9", "Input"));
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			safe_exit(put_error("Expected input 0 - 9", "Input"));
		number = (number * 10) + (str[i] - 48);
		if (number > 255)
			safe_exit(put_error("Expected range: 0 - 255", "Range"));
		i++;
	}
	return (number);
}

int	check_rgb(char type, char *color_line)
{
	char	*number;
	char	*comma;
	int		numbers = 0;

	if (char_times(color_line, ',') != 2)
		safe_exit(put_error("Expected value r,g,b", "RGB missed"));
	while (color_line && *color_line)
	{
		comma = safe_strchr(color_line, ',');
		if (comma)
			*comma = '\0';
		number = color_line;
		set_value(type, atouch(number), numbers);
		numbers++;
		color_line += safe_strlen(number) + (comma != NULL);
	}
	return (0);
}

void	check_color(char *varname, char *value, int i)
{
	t_data	*data;
	// char	*tmp;
	// char	*color;

	(void)i;
	// (void)varname;
	data = data_hook(NULL);
	// if (safe_strchr(line, ' ') == NULL)
	// 	safe_exit(put_error("Expected input \"C/F r,g,b\"", "Input"));
	// tmp = safe_strchr(line, ' ');
	// *tmp = '\0';
	// color = tmp + 1;
	// if ((i == 4 && varname[0] != 'F') || (i == 5 && varname[0] != 'C'))
	// {
	// 	safe_exit(put_error("Expected input \"C/F r,g,b\"", "Input"));
	// 	// put_error("Bad name or sort is not match", line);
	// 	safe_exit(1);
	// }
	check_rgb(varname[0], value);
}
