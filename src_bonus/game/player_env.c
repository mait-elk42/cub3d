/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:02:34 by mait-elk          #+#    #+#             */
/*   Updated: 2024/08/02 08:39:39 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	put_weapon(void)
{
	t_data		*data;
	t_image		wpn;
	t_vector2	p;
	static int	time;
	static int	i;

	data = data_hook(NULL);
	wpn = data->player.hand_frames[i];
	p.x = ((WIN_WIDTH / 2) + wpn.width * 0.3) + data->player.real_head;
	p.y = ((WIN_HEIGHT / 2) + wpn.height * 0.1) + data->player.real_head;
	mlx_put_image_to_window(data->mlx.mlx_ptr,
		data->mlx.window_ptr, wpn.img_ptr, p.x, p.y);
	if (time == 2)
	{
		i++;
		time = 0;
	}
	if (i == 5)
		i = 0;
	time++;
}

void	jumping(void)
{
	t_data	*data;

	data = data_hook(NULL);
	if (data->jumping)
	{
		if (data->jump != 27)
			data->jump += 3;
		if (data->jump == 27)
			data->jumping = false;
	}
	if (data->jumping == false)
	{
		if (data->jump != 0)
			data->jump -= 3;
		if (data->jump == 0)
			data->one_jump = 0;
	}
}

bool	running(void)
{
	t_data	*data;

	data = data_hook(NULL);
	if (data->key_pressed.shift && data->player.is_walking)
	{
		if (data->player.head_angle > 360)
			data->player.head_angle = 0;
		data->player.head_angle += 40;
		data->player.real_head = cos(deg_to_rad(data->player.head_angle)) * 15;
		return (true);
	}
	return (false);
}

void	player_effects(void)
{
	t_data	*data;

	data = data_hook(NULL);
	jumping();
	if (running() == true)
		return ;
	if (data->player.is_walking)
	{
		if (data->player.head_angle > 360)
			data->player.head_angle = 0;
		data->player.head_angle += 20;
		data->player.real_head = cos(deg_to_rad(data->player.head_angle)) * 10;
	}
	else
	{
		if (data->player.head_angle > 360)
			data->player.head_angle = 0;
		data->player.head_angle += 10;
		data->player.real_head = cos(deg_to_rad(data->player.head_angle)) * 5;
	}
}
