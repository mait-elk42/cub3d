/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:03:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/06/11 17:44:18 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int ev_key_up(int keycode, t_data *data)
{
	int		i;
	t_key	*keys;

	keys = &data->keys.w;
	i = 0;
	if (data->game_started == true)
	{
		while (i < 9)
		{
			// printf("released : %d, expected : %d\n", keycode, keys[i].keycode);
			if (keys[i].keycode == keycode)
				keys[i].pressed = false;
			i++;
		}
	}
	return (0);
}

int ev_key_down(int keycode, t_data *data)
{
	int		i;
	t_key	*keys;

	// printf("%d\n", keycode);
	if (keycode == 35) // p character in keyboard
		data->game_started = false;
	if (keycode == KEY_SPACE)
		data->game_started = true;
	if (keycode == KEY_ESC)
		safe_exit(0);
	if (data->game_started == true)
	{
		keys = &data->keys.w;
		i = 0;
		while (i < 9)
		{
			// printf("pressed : %d, expected : %d\n", keycode, keys[i].keycode);
			if (keys[i].keycode == keycode)
				keys[i].pressed = true;
			i++;
		}
	}
	return (0);
}
