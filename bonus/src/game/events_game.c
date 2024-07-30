/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:03:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/30 18:24:49 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	key_edit(t_data *data, int keycode, bool v)
{
	if (keycode == KEY_W)
		data->key_pressed.w = v;
	if (keycode == KEY_A)
		data->key_pressed.a = v;
	if (keycode == KEY_S)
		data->key_pressed.s = v;
	if (keycode == KEY_D)
		data->key_pressed.d = v;
	if (keycode == KEY_UP)
		data->key_pressed.up = v;
	if (keycode == KEY_DOWN)
		data->key_pressed.down = v;
	if (keycode == KEY_LEFT)
		data->key_pressed.left = v;
	if (keycode == KEY_RIGHT)
		data->key_pressed.right = v;
	if (keycode == KEY_SPACE)
		data->key_pressed.space = v;
}

int	ev_key_up(int keycode, t_data *data)
{
	if (data->game_started == true)
		key_edit(data, keycode, false);
	return (0);
}

int	ev_key_down(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		data->game_started = false;
		data->select_item.cont_ignored = false;
		data->mouse.center_mouse = false;
		mlx_mouse_show();
	}
	handle_door(data, keycode);
	if (keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_RETURN)
		handle_selected_item(keycode);
	if (keycode == KEY_SPACE && data->one_jump == 0)
	{
		data->jumping = true;
		data->one_jump++;
	}
	if (data->game_started == true)
		key_edit(data, keycode, true);
	return (0);
}
