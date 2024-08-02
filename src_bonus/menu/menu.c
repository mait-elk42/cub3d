/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:22:28 by aabouqas          #+#    #+#             */
/*   Updated: 2024/08/02 09:00:48 by aabouqas         ###   ########.fr       */
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
	int		i;

	i = 0;
	(void)menu;
	data = data_hook(NULL);
	destroy_this(&menu->logo.img_ptr);
	destroy_this(&menu->bg.img_ptr);
	destroy_this(&menu->hint.img_ptr);
	destroy_this(&menu->s_new_game.img_ptr);
	destroy_this(&menu->us_new_game.img_ptr);
	destroy_this(&menu->s_cont.img_ptr);
	destroy_this(&menu->us_cont.img_ptr);
	destroy_this(&menu->ig_cont.img_ptr);
	destroy_this(&menu->s_exit.img_ptr);
	destroy_this(&menu->us_exit.img_ptr);
	while (i < 5)
		destroy_this(&data->player.hand_frames[i++].img_ptr);
}

void	load_menu_images(t_menu *menu)
{
	menu->logo = t_image_load_xpm("textures/cub_logo.xpm");
	menu->bg = t_image_load_xpm("textures/bg.xpm");
	menu->hint = t_image_load_xpm("textures/hint.xpm");
	menu->s_new_game = t_image_load_xpm("textures/new_game_selected.xpm");
	menu->us_new_game = t_image_load_xpm("textures/new_game_unselected.xpm");
	menu->ig_cont = t_image_load_xpm("textures/continue_ignored.xpm");
	menu->s_cont = t_image_load_xpm("textures/continue_selected.xpm");
	menu->us_cont = t_image_load_xpm("textures/continue_unselected.xpm");
	menu->s_exit = t_image_load_xpm("textures/exit_selected.xpm");
	menu->us_exit = t_image_load_xpm("textures/exit_unselected.xpm");
	data_hook(NULL)->select_item.new_game_selected = true;
	data_hook(NULL)->select_item.cont_ignored = true;
	data_hook(NULL)->select_item.new_game_selected = true;
	data_hook(NULL)->select_item.cont_ignored = true;
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
	put_to_win(width_half - 140, ((WIN_HEIGHT / 2)), menu.us_new_game);
	if (data->start == 0)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 115, menu.ig_cont);
	else
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 115, menu.us_cont);
	put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 230, menu.us_exit);
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
	float		o;

	data = data_hook(NULL);
	width_half = WIN_WIDTH / 2;
	menu = data->menu;
	o = (cos (deg_to_rad(data->offset)) * 30);
	select = data->select_item;
	set_defaults(menu);
	put_to_win((width_half - 240), ((WIN_HEIGHT / 2) - (350)) + o, menu.logo);
	if (data->select_item.item == 0)
		put_to_win(width_half - 140, ((WIN_HEIGHT / 2)), menu.s_new_game);
	if (data->select_item.item == 1)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 115, menu.s_cont);
	if (data->select_item.item == 2)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) + 230, menu.s_exit);
	data->offset += 2.8;
	if (data->offset > 360)
		data->offset = 0;
}
