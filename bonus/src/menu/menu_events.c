/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:13:38 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/24 20:19:07 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	handle_select_event(t_data *data)
{
	int		selected_item;

	selected_item = data->select_item.item;
	printf ("%d\n", selected_item);
	if (data->game_started == true)
		return ;
	if (selected_item == 0 || selected_item == 1)
	{
		data->game_started = true;
		data->mouse.center_mouse = true;
		data->mouse.cam_sens = 0;
		mlx_mouse_hide();
	}
	if (data->select_item.item == 0)
	{
		// restart the game
	}
	if (data->select_item.item == 2)
	{
		if (data->music == true)
		{
			data->music = false;
			kill (data->background_music, SIGHUP);
		}
		else if (data->music == false)
		{
			data->music = true;
			play_music();
		}
	}
	if (data->select_item.item == 3)
	{
		kill (data->background_music, SIGHUP);
		safe_exit(0);
	}
}

void	handle_key_up(t_data *data)
{
	if (data->game_started == true)
		return ;
	if (data->select_item.item == 0)
		data->select_item.item = 4;
	data->select_item.item--;
}

void	handle_key_down(t_data *data)
{
	if (data->game_started == true)
		return ;
	if (data->select_item.item == 3)
		data->select_item.item = -1;
	data->select_item.item++;
}

void	handle_selected_item(int key)
{
	t_data	*data;

	data = data_hook(NULL);
	if (key == KEY_RETURN)
		handle_select_event(data);
	if (key == KEY_UP || key == KEY_DOWN)
		play_effect("assets/sounds/navigation_effect.mp3");
	if (key == KEY_UP)
		handle_key_up(data);
	if (key == KEY_DOWN)
		handle_key_down(data);
}
