/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:03:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/06/04 18:57:49 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int ev_key_up(int keycode, t_data *data)
{
	t_key	*keys;
	int		i;

	keys = &data->keys.w;
	i = 0;
	while (i < 8)
	{
		printf("released : %d, expected : %d\n", keycode, keys[i].keycode);
		if (keys[i].keycode == keycode)
			keys[i].pressed = false;
		i++;
	}
	// if (keycode == KEY_W)
	// 	data->keys.w.pressed = false;
	// if (keycode == KEY_A)
	// 	data->keys.a.pressed = false;
	// if (keycode == KEY_S)
	// 	data->keys.s.pressed = false;
	// if (keycode == KEY_D)
	// 	data->keys.d.pressed = false;
	// if (keycode == KEY_UP)
	// 	data->keys.up.pressed = false;
	// if (keycode == KEY_DOWN)
	// 	data->keys.down.pressed = false;
	// if (keycode == KEY_LEFT)
	// 	data->keys.left.pressed = false;
	// if (keycode == KEY_RIGHT)
	// 	data->keys.right.pressed = false;
	return (0);
}

int ev_key_down(int keycode, t_data *data)
{
	// (void)data;
	if (keycode == KEY_ESC)
		safe_exit(0);
	// printf("pressed key : %d\n", keycode);
	// if (keycode == KEY_W)
	// 	data->keys.w.pressed = true;
	// if (keycode == KEY_A)
	// 	data->keys.a.pressed = true;
	// if (keycode == KEY_S)
	// 	data->keys.s.pressed = true;
	// if (keycode == KEY_D)
	// 	data->keys.d.pressed = true;
	// if (keycode == KEY_UP)
	// 	data->keys.up.pressed = true;
	// if (keycode == KEY_DOWN)
	// 	data->keys.down.pressed = true;
	// if (keycode == KEY_LEFT)
	// 	data->keys.left.pressed = true;
	// if (keycode == KEY_RIGHT)
	// 	data->keys.right.pressed = true;
	t_key	*keys;
	int		i;

	keys = &data->keys.w;
	i = 0;
	while (i < 8)
	{
		printf("pressed : %d, expected : %d\n", keycode, keys[i].keycode);
		if (keys[i].keycode == keycode)
			keys[i].pressed = true;
		i++;
	}
	return (0);
}
