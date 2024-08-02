/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:03:15 by mait-elk          #+#    #+#             */
/*   Updated: 2024/08/01 19:05:45 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	ev_destroy(t_data *data)
{
	(void)data;
	safe_exit(0);
	return (0);
}

void	key_edit(t_data *data, int keycode, bool v)
{
	if (keycode == KEY_W)
		data->kpr.w = v;
	if (keycode == KEY_A)
		data->kpr.a = v;
	if (keycode == KEY_S)
		data->kpr.s = v;
	if (keycode == KEY_D)
		data->kpr.d = v;
	if (keycode == KEY_UP)
		data->kpr.up = v;
	if (keycode == KEY_DOWN)
		data->kpr.down = v;
	if (keycode == KEY_LEFT)
		data->kpr.left = v;
	if (keycode == KEY_RIGHT)
		data->kpr.right = v;
	if (keycode == KEY_SPACE)
		data->kpr.space = v;
	if (keycode == KEY_SHIFT)
		data->kpr.shift = v;
}

int	ev_key_up(int keycode, t_data *data)
{
	if (data->game_started == true)
		key_edit(data, keycode, false);
	return (0);
}

static void	mouse_hv(int x, int y, t_data *d)
{
	int			width_half;
	int			height_half;

	width_half = WIN_WIDTH / 2;
	height_half = WIN_HEIGHT / 2;
	if (y < height_half)
	{
		d->mouse.to_down = false;
		d->mouse.to_up = true;
	}
	if (y > height_half)
	{
		d->mouse.to_down = true;
		d->mouse.to_up = false;
	}
	if (x > width_half)
	{
		d->mouse.to_right = true;
		d->mouse.to_left = false;
	}
	if (x < width_half)
	{
		d->mouse.to_right = false;
		d->mouse.to_left = true;
	}
}

int	ev_mouse_moved(int x, int y, void *data)
{
	t_data		*d;
	int			width_half;
	int			height_half;

	d = (t_data *)data;
	if (d->game_started == false)
		return (0);
	width_half = WIN_WIDTH / 2;
	height_half = WIN_HEIGHT / 2;
	mouse_hv(x, y, data);
	d->mouse.cam_sens_h = fabs((width_half - x) * 0.02);
	d->mouse.cam_sens_v = fabs((height_half - y) * 0.02);
	if (d->mouse.center_mouse)
		mlx_mouse_move(d->mlx.window_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
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
