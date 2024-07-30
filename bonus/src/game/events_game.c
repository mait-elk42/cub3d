/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:03:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/30 13:14:28 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

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

void	door(t_data *data)
{
	t_vector	pos;
	t_vector	check;

	pos = (t_vector){(data->player.position.x) / TILE_SIZE, ((data->player.position.y) / TILE_SIZE)};
	check = (t_vector){0, 0};
	// printf("%f\n", data->player.angle);
	if (floor(data->player.angle) >= 60 && floor(data->player.angle) <= 120)
		check.y = 1;
	if (floor(data->player.angle) >= 240 && floor(data->player.angle) <= 300)
		check.y = -1;
	if (floor(data->player.angle) >= 330 || floor(data->player.angle) <= 30)
		check.x = 1;
	if (floor(data->player.angle) >= 150 && floor(data->player.angle) <= 210)
		check.x = -1;
	if (check.x != 0 || check.y != 0)
	{
		if (data->map[pos.y + check.y][pos.x + check.x] == 'D')
			data->map[pos.y + check.y][pos.x + check.x] = 'd';
		else if (data->map[pos.y + check.y][pos.x + check.x] == 'd')
			data->map[pos.y + check.y][pos.x + check.x] = 'D';
	}
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
	// printf("%d\n", keycode);
	if (keycode == 14) // e key
		door(data);
	if (keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_RETURN)
		handle_selected_item(keycode);
	if (keycode == KEY_SPACE && data->one_jump == 0)
	{
		data->jumping = true;
		data->one_jump++;
	}
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
		if (keycode == KEY_UP)
			data->key_pressed.up = true;
		if (keycode == KEY_DOWN)
			data->key_pressed.down = true;
		if (keycode == KEY_LEFT)
			data->key_pressed.left = true;
		if (keycode == KEY_RIGHT)
			data->key_pressed.right = true;
		if (keycode == KEY_SPACE)
			data->key_pressed.space = true;
	}
	return (0);
}
