/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:22:28 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/31 11:36:20 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	destroy_this(void *img_ptr)
{
	void	*mlx_ptr;

	mlx_ptr = data_hook(NULL)->mlx.mlx_ptr;
	if (img_ptr != NULL)
		mlx_destroy_image(mlx_ptr, img_ptr);
}

void	destroy_menu(t_menu *menu)
{
	t_data	*data;
	int		i;

	data = data_hook(NULL);
	destroy_this(menu->logo.img_ptr);
	destroy_this(menu->bg.img_ptr);
	destroy_this(menu->hint.img_ptr);
	destroy_this(menu->s_new_game.img_ptr);
	destroy_this(menu->us_new_game.img_ptr);
	destroy_this(menu->s_cont.img_ptr);
	destroy_this(menu->us_cont.img_ptr);
	destroy_this(menu->ig_cont.img_ptr);
	destroy_this(menu->s_exit.img_ptr);
	destroy_this(menu->us_exit.img_ptr);
	destroy_this(menu->s_music.img_ptr);
	destroy_this(menu->us_music.img_ptr);
	while (i < 5)
		destroy_this(data->player.hand_frames[i++].img_ptr);
}

void	load_menu_images(t_menu *menu)
{
	menu->logo = t_image_loadfromxpm("textures/cub_logo.xpm");
	menu->bg = t_image_loadfromxpm("textures/bg.xpm");
	menu->hint = t_image_loadfromxpm("textures/enter_to_select.xpm");
	menu->s_new_game = t_image_loadfromxpm("textures/new_game_selected.xpm");
	menu->us_new_game = t_image_loadfromxpm("textures/new_game_unselected.xpm");
	menu->ig_cont = t_image_loadfromxpm("textures/continue_ignored.xpm");
	menu->s_cont = t_image_loadfromxpm("textures/continue_selected.xpm");
	menu->us_cont = t_image_loadfromxpm("textures/continue_unselected.xpm");
	menu->s_exit = t_image_loadfromxpm("textures/exit_selected.xpm");
	menu->us_exit = t_image_loadfromxpm("textures/exit_unselected.xpm");
	menu->s_music = t_image_loadfromxpm("textures/music_selected.xpm");
	menu->us_music = t_image_loadfromxpm("textures/music_unselected.xpm");
	data_hook(NULL)->select_item.new_game_selected = true;
	data_hook(NULL)->select_item.cont_ignored = true;
	data_hook(NULL)->music = true;
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
	put_to_win(width_half - 240, (WIN_HEIGHT / 2) - 350, menu.logo);
	if (_switch)
		put_to_win((WIN_WIDTH / 2) - 140, (WIN_HEIGHT - 80), menu.hint);
	put_to_win(width_half - 140, ((WIN_HEIGHT / 2) - 50), menu.us_new_game);
	if (data->start == 0)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 50, menu.ig_cont);
	else
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 50, menu.us_cont);
	put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 150, menu.us_music);
	put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 250, menu.us_exit);
	if (abs(n) % 35 == 0)
		_switch = _switch == false;
	n++;
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
	if (data->select_item.item == 0)
		put_to_win(width_half - 140, ((WIN_HEIGHT / 2) - 50), menu.s_new_game);
	if (data->select_item.item == 1)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 50, menu.s_cont);
	if (data->select_item.item == 2)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 150, menu.s_music);
	if (data->select_item.item == 3)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 250, menu.s_exit);
}
