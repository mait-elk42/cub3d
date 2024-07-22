/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:13:38 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/22 13:00:45 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	handle_select_event(t_data *data)
{
	if (data->select_item.new_game_selected)
	{
		data->game_started = true;
		// data->mouse.center_mouse = true;
		return ;
	}
	if (data->select_item.cont_selected)
	{
		data->game_started = true;
		// data->mouse.center_mouse = true;
	}
	if (data->select_item.exit_selected)
	{
		kill (data->background_music, SIGHUP);
		safe_exit(0);
	}
}

void	handle_key_up(t_data *data)
{
	if (data->select_item.new_game_selected)
	{
		data->select_item.new_game_selected = false;
		data->select_item.exit_selected = true;
		data->select_item.cont_selected = false;
	}
	else if (data->select_item.exit_selected)
	{
		data->select_item.new_game_selected = false;
		data->select_item.cont_selected = true;
		data->select_item.exit_selected = false;
		if (data->select_item.cont_ignored)
		{
			data->select_item.new_game_selected = true;
			data->select_item.cont_selected = false;
		}
	}
	else
	{
		data->select_item.new_game_selected = true;
		data->select_item.cont_selected = false;
		data->select_item.exit_selected = false;
	}
}

void	handle_key_down(t_data *data)
{
	if (data->select_item.new_game_selected)
	{
		data->select_item.new_game_selected = false;
		data->select_item.exit_selected = false;
		data->select_item.cont_selected = true;
		if (data->select_item.cont_ignored)
		{
			data->select_item.cont_selected = false;
			data->select_item.exit_selected = true;
		}
	}
	else if (data->select_item.cont_selected)
	{
		data->select_item.new_game_selected = false;
		data->select_item.cont_selected = false;
		data->select_item.exit_selected = true;
	}
	else
	{
		data->select_item.new_game_selected = true;
		data->select_item.cont_selected = false;
		data->select_item.exit_selected = false;
	}
}

void	handle_selected_item(int key)
{
	t_data	*data;

	data = data_hook(NULL);
	if (key == KEY_RETURN)
		handle_select_event(data);
	if (key == KEY_UP)
		handle_key_up(data);
	if (key == KEY_DOWN)
		handle_key_down(data);
}
