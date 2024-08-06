/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:47:21 by aabouqas          #+#    #+#             */
/*   Updated: 2024/08/06 10:52:02 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	put_to_win(int pos_x, int pox_y, t_image image)
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_data	*data;

	data = data_hook(NULL);
	mlx_ptr = data->mlx.mlx_ptr;
	mlx_win = data->mlx.window_ptr;
	mlx_put_image_to_window(mlx_ptr, mlx_win, image.img_ptr, pos_x, pox_y);
}

void	hide_menu(void)
{
	data_hook(NULL)->game_started = true;
	data_hook(NULL)->mouse.center_mouse = true;
	data_hook(NULL)->mouse.cam_sens_h = 0;
	data_hook(NULL)->mouse.cam_sens_v = 0;
	data_hook(NULL)->start++;
	mlx_mouse_hide();
	kill (data_hook(NULL)->server, SIGPROF);
}

void	rest_player(void)
{
	t_data	*data;

	data = data_hook(NULL);
	data->player.position.x = (data->p_data.player_pos.x * 32) + (32 / 2);
	data->player.position.y = (data->p_data.player_pos.y * 32) + (32 / 2);
	data->player.angle = data->p_data.player_angle;
	data->up_down = 0;
	data->jump = 0;
	data->jumping = false;
}
