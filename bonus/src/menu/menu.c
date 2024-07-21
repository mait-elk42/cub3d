/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:22:28 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/21 18:46:19 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	destroy_images(t_menu *menu)
{
	t_data	*data;

	data = data_hook(NULL);
	if (menu->logo.img_ptr != NULL)
		mlx_destroy_image(data->mlx.mlx_ptr, menu->logo.img_ptr);
	if (menu->new_game.img_ptr != NULL)
		mlx_destroy_image(data->mlx.mlx_ptr, menu->new_game.img_ptr);
	if (menu->cont.img_ptr != NULL)
		mlx_destroy_image(data->mlx.mlx_ptr, menu->cont.img_ptr);
	if (menu->exit.img_ptr != NULL)
		mlx_destroy_image(data->mlx.mlx_ptr, menu->exit.img_ptr);
}

void	load_images(t_menu *menu, t_select select)
{
	destroy_images(menu);
	menu->logo = t_image_loadfromxpm("textures/cub_logo.xpm");
	if (select.new_game_selected)
		menu->new_game = t_image_loadfromxpm("textures/new_game_selected.xpm");
	else
		menu->new_game = t_image_loadfromxpm("textures/new_game_unselected.xpm");
	if (select.cont_ignored)
		menu->cont = t_image_loadfromxpm("textures/continue_ignored.xpm");
	else if (select.cont_selected)
		menu->cont = t_image_loadfromxpm("textures/continue_selected.xpm");
	else
		menu->cont = t_image_loadfromxpm("textures/continue_unselected.xpm");
	if (select.exit_selected)
		menu->exit = t_image_loadfromxpm("textures/exit_selected.xpm");
	else
		menu->exit = t_image_loadfromxpm("textures/exit_unselected.xpm");
}

void	show_menu()
{
	t_data		*data;
	t_menu		menu;
	t_select	select;
	t_image		hint;

	data = data_hook(NULL);
	menu = data->menu;
	select = data->select_item;
	load_images(&menu, select);
	hint = t_image_loadfromxpm("textures/enter_to_select.xpm");
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, menu.logo.img_ptr, (WIN_WIDTH / 2) - 240, (WIN_HEIGHT / 20));
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, menu.new_game.img_ptr, (WIN_WIDTH / 2) - 140, (WIN_HEIGHT / 2) - 50);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, menu.cont.img_ptr, (WIN_WIDTH / 2) - 140, (WIN_HEIGHT / 2) + 50);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, menu.exit.img_ptr, (WIN_WIDTH / 2) - 140, (WIN_HEIGHT / 2) + 150);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, hint.img_ptr, WIN_WIDTH - 280, WIN_HEIGHT - 80);
}
