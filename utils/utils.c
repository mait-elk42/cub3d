/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:17:07 by mait-elk          #+#    #+#             */
/*   Updated: 2024/06/04 18:32:08 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_data	*data_hook(t_data *data)
{
	static t_data	*save_data;

	if (data != NULL)
		save_data = data;
	return (save_data);
}

void	safe_exit(int status)
{
	t_data	*data;

	data = data_hook(NULL);
	free_tab(data->lines);
	data->lines = NULL;
	free(data->maps);
	data->maps = NULL;
	ft_bzero(&data->scene_info, sizeof(t_scene_info));
	close(data->fd_file_input);
	if (data->mlx.mlx_ptr != NULL && data->mlx.window_ptr != NULL)
		mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	free(data->mlx.mlx_ptr);
	data->mlx.mlx_ptr = NULL;
	// system("kill $(ps | grep 'afplay audios/background_music.mp3' | head -n 1 | awk '{printf $1}')");
	exit(status);
}

void	set_screen_size()
{
	t_data	*data;
	t_size	size;

	data = data_hook(NULL);
	size.height = 0;
	while (data->maps[size.height])
	{
		if (size.height == 0)
			size.width = safe_strlen(data->maps[size.height]);
		size.height++;
	}
	data->screen = size;
}

void	logger(char *msg)
{
	print(1, COLOR_BLUE"LOG : ", 0);
	print(1, msg, 1);
	print(1, COLOR_RESET, 0);
}
