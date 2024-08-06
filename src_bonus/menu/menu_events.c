/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:13:38 by aabouqas          #+#    #+#             */
/*   Updated: 2024/08/06 11:43:28 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	handle_select_event(t_data *data)
{
	int	selected_item;

	selected_item = data->select_item.item;
	if (data->game_started == true)
		return ;
	if (selected_item == 0)
		reset_doors(data->map);
	if (selected_item == 0 || selected_item == 1)
		hide_menu();
	if (data->select_item.item == 2)
		kill (data->server, SIGUSR2);
	if (data->select_item.item == 0)
		rest_player();
	if (data->select_item.item == 3)
		safe_exit(0);
}

void	handle_key_up(t_data *data)
{
	if (data->start == 0 && data->select_item.item == 2)
		data->select_item.item--;
	if (data->game_started == true)
		return ;
	if (data->select_item.item == 0)
		data->select_item.item = 4;
	data->select_item.item--;
}

void	handle_key_down(t_data *data)
{
	if (data->start == 0 && data->select_item.item == 0)
		data->select_item.item++;
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
	if ((key == KEY_DOWN || key == KEY_UP) && data->game_started == false)
		kill (data->server, SIGHUP);
	if (key == KEY_UP)
		handle_key_up(data);
	if (key == KEY_DOWN)
		handle_key_down(data);
}
