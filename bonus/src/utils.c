/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:17:07 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/30 17:12:33 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

t_data	*data_hook(t_data *data)
{
	static t_data	*save_data;

	if (data != NULL)
		save_data = data;
	return (save_data);
}

void	destroy_textures(void)
{
	t_data			*data;
	t_scene_info	scene;

	data = data_hook(NULL);
	scene = data->scene_info;
	if (data->texture_ea.img_ptr != NULL)
		mlx_destroy_image(data->mlx.mlx_ptr, data->texture_ea.img_ptr);
	if (data->texture_no.img_ptr != NULL)
		mlx_destroy_image(data->mlx.mlx_ptr, data->texture_no.img_ptr);
	if (data->texture_so.img_ptr != NULL)
		mlx_destroy_image(data->mlx.mlx_ptr, data->texture_so.img_ptr);
	if (data->texture_we.img_ptr != NULL)
		mlx_destroy_image(data->mlx.mlx_ptr, data->texture_we.img_ptr);
}

void	safe_exit(int status)
{
	t_data	*data;

	data = data_hook(NULL);
	free_tab(data->lines);
	data->lines = NULL;
	ft_bzero(&data->scene_info, sizeof(t_scene_info));
	close(data->fd_file_input);
	if (data->mlx.mlx_ptr != NULL && data->mlx.window_ptr != NULL)
		mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	if (data->mlx.mlx_ptr != NULL)
		destroy_textures();
	free(data->mlx.mlx_ptr);
	data->mlx.mlx_ptr = NULL;
	exit(status);
}

void	set_screen_size(void)
{
	t_data	*data;
	t_size	size;
	size_t	width;

	data = data_hook(NULL);
	size.height = 0;
	size.width = 0;
	while (data->map[size.height])
	{
		width = safe_strlen(data->map[size.height]);
		if (size.width < width)
			size.width = width;
		size.height++;
	}
	data->screen = size;
}

long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, 0);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
