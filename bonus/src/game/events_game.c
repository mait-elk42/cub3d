/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:03:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/21 13:50:31 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ev_key_up(int keycode, t_data *data)
{
	if (data->game_started == true)
	{
		if (keycode == KEY_W)
			data->key_pressed.w = false;
		if (keycode == KEY_A)
			data->key_pressed.a = false;
		if (keycode == KEY_S)
			data->key_pressed.s = false;
		if (keycode == KEY_D)
			data->key_pressed.d = false;
		if (keycode == KEY_UP)
			data->key_pressed.up = false;
		if (keycode == KEY_DOWN)
			data->key_pressed.down = false;
		if (keycode == KEY_LEFT)
			data->key_pressed.left = false;
		if (keycode == KEY_RIGHT)
			data->key_pressed.right = false;
		if (keycode == KEY_SPACE)
			data->key_pressed.space = false;
	}
	return (0);
}

void	handle_up_down(int key)
{
	t_data	*data;

	data = data_hook(NULL);
	if (key == KEY_RETURN)
	{
		if (data->select_item.new_game_selected)
		{
			data->game_started = true;
			return ;
		}
		if (data->select_item.exit_selected)
		{
			kill (data->background_music, 9);
			safe_exit(0);
		}
	}
	if (key == KEY_UP)
	{
		if (data->select_item.new_game_selected)
		{
			data->select_item.new_game_selected = false;
			data->select_item.exit_selected = true;
			data->select_item.cont_selected = false;
		} else if (data->select_item.exit_selected)
		{
			data->select_item.new_game_selected = false;
			data->select_item.cont_selected = true;
			data->select_item.exit_selected = false;
		} else {
			data->select_item.new_game_selected = true;
			data->select_item.cont_selected = false;
			data->select_item.exit_selected = false;
		}
	}
	if (key == KEY_DOWN)
	{
		if (data->select_item.new_game_selected)
		{
			data->select_item.new_game_selected = false;
			data->select_item.exit_selected = false;
			data->select_item.cont_selected = true;
		} else if (data->select_item.cont_selected)
		{
			data->select_item.new_game_selected = false;
			data->select_item.cont_selected = false;
			data->select_item.exit_selected = true;
		} else {
			data->select_item.new_game_selected = true;
			data->select_item.cont_selected = false;
			data->select_item.exit_selected = false;
		}
	}
}

int	ev_key_down(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		data->game_started = false;
	if (keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_RETURN)
		handle_up_down(keycode);
	if (data->game_started == true)
	{
		if (keycode == KEY_W)
			data->key_pressed.w = true;
		if (keycode == KEY_A)
			data->key_pressed.a = true;
		if (keycode == KEY_S)
			data->key_pressed.s = true;
		if (keycode == KEY_D)
			data->key_pressed.d = true;
		if (keycode == KEY_LEFT)
			data->key_pressed.left = true;
		if (keycode == KEY_RIGHT)
			data->key_pressed.right = true;
		if (keycode == KEY_SPACE)
			data->key_pressed.space = true;
	}
	return (0);
}
