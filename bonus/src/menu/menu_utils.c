/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:47:21 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/30 19:41:41 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	put_to_win(int posx, int pox_y, t_image image)
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_data	*data;

	data = data_hook(NULL);
	mlx_ptr = data->mlx.mlx_ptr;
	mlx_win = data->mlx.window_ptr;
	mlx_put_image_to_window(mlx_ptr, mlx_win, image.img_ptr, posx, pox_y);
}

void	background_scale(t_data	*data, t_image	image)
{
	int			x;
	int			y;
	t_vector2	step;
	t_vector	pos;
	int			color;

	step.x = (float)image.width / WIN_WIDTH;
	step.y = (float)image.height / WIN_HEIGHT;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			pos.x = (int)(x * step.x) % image.width;
			pos.y = (int)(y * step.y) % image.height;
			color = image.buffer[pos.y * image.width + pos.x];
			t_image_update_pixel(&data->scene_layer, x, y, color);
			x++;
		}
		y++;
	}
	put_to_win(0, 0, data->scene_layer);
}

void	hide_menu(void)
{
	data_hook(NULL)->game_started = true;
	data_hook(NULL)->mouse.center_mouse = true;
	data_hook(NULL)->mouse.cam_sens_h = 0;
	data_hook(NULL)->mouse.cam_sens_v = 0;
	data_hook(NULL)->start++;
	mlx_mouse_hide();
}

void	rest_player(void)
{
	t_data	*data;

	data = data_hook(NULL);
	data->player.position.x = (data->p_data.player_pos.x * 32) + (32 / 2);
	data->player.position.y = (data->p_data.player_pos.y * 32) + (32 / 2);
	data->player.angle = data->p_data.player_angle;
}
