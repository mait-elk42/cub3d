/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:18:41 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/26 20:06:53 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	int	number;

	number = 0;
	if (str == NULL)
		return (-1);
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (-1);
		number = (number * 10) + (*str - 48);
		if (number > 255)
			return (-1);
		str++;
	}
	return (number);
}

int	check_rgb(char *color_line)
{
	char	*number;
	char	*comma;
	int		numbers = 0;

	if (char_times(color_line, ',') != 2)
	{
		put_error_custom("invalid color name", color_line);
		safe_exit(1);
	}
	while (color_line && *color_line)
	{
		comma = safe_strchr(color_line, ',');
		if (comma)
			*comma = '\0';
		number = color_line;
		printf("--[%i]--\n", atouch(number));
		if (atouch(number) == -1)
		{
			put_error_custom("invalid color name", number);
			safe_exit(1);
		}
		if (*number == '\0')
			{
			put_error_custom("invalid color name", number);
			safe_exit(1);
		}
		numbers++;
		color_line += safe_strlen(number) + (comma != NULL);
	}
	printf("%d\n", numbers);
	if (numbers != 3)
	{
		put_error_custom("invalid color name", "3 Numbers Required");
		safe_exit(1);
	}
	return (0);
}

void	check_color(char *line, int i)
{
	t_data	*data;
	char	*del;
	char	*color;

	data = data_hook(NULL);
	if (safe_strchr(line, ' ') == NULL)
	{
		put_error_custom("invalid color name", line);
		safe_exit(1);
	}
	del = safe_strchr(line, ' ');
	*del = '\0';
	color = del + 1;
	if ((i == 4 && str_equal(line, "F") == 0)
		|| (i == 5 && str_equal(line, "C") == 0))
	{
		put_error_custom("bad name or sort is not match", line);
		safe_exit(1);
	}
	check_rgb(color);
	// check_clrval_validation(color, line, i);
	//
	// if (*str_skip(color, "0123456789,") != '\0')
	// {
	// 	put_error_custom("invalid color value", color);
	// 	safe_exit(1);
	// }
}
