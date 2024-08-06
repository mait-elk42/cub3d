/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:03:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/08/03 19:39:35 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ev_destroy(t_data *data)
{
	(void)data;
	safe_exit(0);
	return (0);
}

int	ev_key_up(int keycode, t_data *data)
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
	return (0);
}

int	ev_key_down(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		safe_exit(0);
	if (keycode == KEY_W)
		data->key_pressed.w = true;
	if (keycode == KEY_A)
		data->key_pressed.a = true;
	if (keycode == KEY_S)
		data->key_pressed.s = true;
	if (keycode == KEY_D)
		data->key_pressed.d = true;
	if (keycode == KEY_UP)
		data->key_pressed.up = false;
	if (keycode == KEY_DOWN)
		data->key_pressed.down = false;
	if (keycode == KEY_LEFT)
		data->key_pressed.left = true;
	if (keycode == KEY_RIGHT)
		data->key_pressed.right = true;
	if (keycode == KEY_SPACE)
		data->key_pressed.space = true;
	return (0);
}
