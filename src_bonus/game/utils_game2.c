/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_game2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 08:32:30 by aabouqas          #+#    #+#             */
/*   Updated: 2024/08/02 08:55:38 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	ev_destroy(t_data *data)
{
	(void)data;
	safe_exit(0);
	return (0);
}

void	normalize_sensibility(void)
{
	t_data	*data;

	data = data_hook(NULL);
	if (data->mouse.cam_sens_h > 15.0)
		data->mouse.cam_sens_h -= 10.0;
	else if (data->mouse.cam_sens_h > 10.0)
		data->mouse.cam_sens_h -= 2.0;
	else if (data->mouse.cam_sens_h > 0.0)
		data->mouse.cam_sens_h -= 0.4;
	else if (data->mouse.cam_sens_h <= 0.0)
		data->mouse.cam_sens_h = 0;
	if (data->mouse.cam_sens_v > 0.0)
		data->mouse.cam_sens_v -= 0.5;
	else if (data->mouse.cam_sens_v > 5.0)
		data->mouse.cam_sens_v -= 5;
	else if (data->mouse.cam_sens_v <= 0.0)
		data->mouse.cam_sens_v = 0;
}

void	put_2_window(void)
{
	t_data		*data;
	void		*mlx_win;
	void		*mlx_ptr;
	t_vector	pos;

	data = data_hook(NULL);
	mlx_ptr = data->mlx.mlx_ptr;
	mlx_win = data->mlx.window_ptr;
	pos.x = (WIN_WIDTH * MPSIZE) / 2;
	pos.y = (WIN_WIDTH * MPSIZE) / 2;
	mlx_put_image_to_window(mlx_ptr, mlx_win, data->scene_layer.img_ptr, 0, 0);
	mlx_put_image_to_window(mlx_ptr, mlx_win, \
		data->minimap_layer.img_ptr, pos.x, pos.x);
	mlx_put_image_to_window(mlx_ptr, mlx_win, data->north_icon.img_ptr, \
		data->north_icon_pos.x + pos.x, data->north_icon_pos.y + pos.x);
	normalize_sensibility();
	put_weapon();
	player_effects();
}
