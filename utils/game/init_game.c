/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:05:02 by mait-elk          #+#    #+#             */
/*   Updated: 2024/06/04 20:22:54 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_keys(t_data *data)
{
	data->keys.w.keycode = KEY_W;
	data->keys.a.keycode = KEY_A;
	data->keys.s.keycode = KEY_S;
	data->keys.d.keycode = KEY_D;
	data->keys.up.keycode = KEY_UP;
	data->keys.right.keycode = KEY_RIGHT;
	data->keys.down.keycode = KEY_DOWN;
	data->keys.left.keycode = KEY_LEFT;
}

