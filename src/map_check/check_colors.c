/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:18:41 by aabouqas          #+#    #+#             */
/*   Updated: 2024/08/03 18:16:04 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	set_value(char type, int number, int numbers)
{
	t_data	*data;

	data = data_hook(NULL);
	if (numbers > 3)
		eput_error("invalid color name", "3 Numbers Required", 1);
	if (type == 'C')
	{
		if (numbers == 0)
			data->scene_info.ceiling_color.r = number;
		if (numbers == 1)
			data->scene_info.ceiling_color.g = number;
		if (numbers == 2)
			data->scene_info.ceiling_color.b = number;
	}
	if (type == 'F')
	{
		if (numbers == 0)
			data->scene_info.floor_color.r = number;
		if (numbers == 1)
			data->scene_info.floor_color.g = number;
		if (numbers == 2)
			data->scene_info.floor_color.b = number;
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
	int		number;

	number = 0;
	if (str == NULL || *str == '\0')
		eput_error("Expected input 0 - 9", "Input", 1);
	i = 0;
	if (str[0] == '0' && safe_strlen(str) > 1)
		eput_error("Expected nonezero in indently", "Input", 1);
	if (str[i] == '-' || str[i] == '+')
		eput_error("Expected unsigned number", "Input", 1);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			eput_error("Expected input 0 - 9", "Input", 1);
		number = (number * 10) + (str[i] - 48);
		if (number > 255)
			eput_error("Expected range: 0 - 255", "Range", 1);
		i++;
	}
	return (number);
}

void	check_color(char type, char *value)
{
	t_data	*data;
	char	*number;
	char	*comma;
	int		numbers;

	data = data_hook(NULL);
	numbers = 0;
	if (char_times(value, ',') != 2)
		eput_error("Expected value r,g,b", "RGB missed", 1);
	while (value && *value)
	{
		comma = safe_strchr(value, ',');
		if (comma != NULL || safe_strchr(value, ',') == NULL)
		{
			(comma != NULL) && (*comma = '\0');
			number = value;
			set_value(type, atouch(number), numbers);
			value += safe_strlen(number) + (comma != NULL);
			numbers++;
		}
		else
			value++;
	}
	if (numbers != 3)
		eput_error("Expected value r,g,b", "RGB missed", 1);
}
