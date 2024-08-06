/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:22:28 by aabouqas          #+#    #+#             */
/*   Updated: 2024/08/06 12:24:35 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	destroy_this(void **img_ptr)
{
	void	*mlx_ptr;

	if (*img_ptr == NULL)
		return ;
	mlx_ptr = data_hook(NULL)->mlx.mlx_ptr;
	if (mlx_ptr == NULL)
		return ;
	if (*img_ptr != NULL)
		mlx_destroy_image(mlx_ptr, *img_ptr);
	*img_ptr = NULL;
}

void	destroy_menu(t_menu *menu)
{
	t_data	*data;

	data = data_hook(NULL);
	destroy_this(&menu->logo.img_ptr);
	destroy_this(&menu->bg.img_ptr);
	destroy_this(&menu->hint.img_ptr);
	destroy_this(&menu->new_game_0.img_ptr);
	destroy_this(&menu->new_game_1.img_ptr);
	destroy_this(&menu->cont_0.img_ptr);
	destroy_this(&menu->cont_1.img_ptr);
	destroy_this(&menu->cont_2.img_ptr);
	destroy_this(&menu->exit_1.img_ptr);
	destroy_this(&menu->exit_0.img_ptr);
	destroy_this(&menu->music_0.img_ptr);
	destroy_this(&menu->music_1.img_ptr);
}

void	load_menu_images(t_menu *menu)
{
	menu->logo = t_image_load_xpm("textures/cub_logo.xpm");
	menu->bg = t_image_load_xpm("textures/bg.xpm");
	menu->hint = t_image_load_xpm("textures/hint.xpm");
	menu->new_game_1 = t_image_load_xpm("textures/new_game_1.xpm");
	menu->new_game_0 = t_image_load_xpm("textures/new_game_0.xpm");
	menu->cont_2 = t_image_load_xpm("textures/continue_2.xpm");
	menu->cont_1 = t_image_load_xpm("textures/continue_1.xpm");
	menu->cont_0 = t_image_load_xpm("textures/continue_0.xpm");
	menu->exit_1 = t_image_load_xpm("textures/exit_1.xpm");
	menu->exit_0 = t_image_load_xpm("textures/exit_0.xpm");
	menu->music_0 = t_image_load_xpm("textures/music_0.xpm");
	menu->music_1 = t_image_load_xpm("textures/music_1.xpm");
	data_hook(NULL)->select_item.new_game_1 = true;
	data_hook(NULL)->select_item.cont_2 = true;
}

void	set_defaults(t_menu menu)
{
	static char	n = 0;
	static bool	_switch;
	int			width_half;
	t_data		*data;

	data = data_hook(NULL);
	width_half = WIN_WIDTH / 2;
	put_to_win(0, 0, menu.bg);
	if (_switch)
		put_to_win((WIN_WIDTH / 2) - 140, (WIN_HEIGHT - 80), menu.hint);
	put_to_win(width_half - 140, ((WIN_HEIGHT / 2)), menu.new_game_0);
	if (data->start == 0)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 100, menu.cont_2);
	else
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 100, menu.cont_0);
	put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 200, menu.music_0);
	put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 300, menu.exit_0);
	if (abs(n) % 35 == 0)
		_switch = _switch == false;
	n++;
	n *= (n < 127);
}

void	show_menu(void)
{
	t_data		*data;
	t_menu		menu;
	int			width_half;
	t_select	select;

	data = data_hook(NULL);
	width_half = WIN_WIDTH / 2;
	menu = data->menu;
	select = data->select_item;
	set_defaults(menu);
	put_cub(data, (t_vector2){150, 150}, 100);
	put_cub(data, (t_vector2){WIN_WIDTH - 200, 150}, 100);
	put_cub(data, (t_vector2){(WIN_WIDTH / 2) - 50, 220}, 200);
	put_to_win((width_half - 240), ((WIN_HEIGHT / 2) - (350)), menu.logo);
	if (data->select_item.item == 0)
		put_to_win(width_half - 140, ((WIN_HEIGHT / 2)), menu.new_game_1);
	if (data->select_item.item == 1)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 100, menu.cont_1);
	if (data->select_item.item == 2)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 200, menu.music_1);
	if (data->select_item.item == 3)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 300, menu.exit_1);
}
