/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:22:28 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/24 19:29:01 by aabouqas         ###   ########.fr       */
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

void	destroy_images(t_menu *menu)
{
	destroy_this(menu->logo.img_ptr);
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
}

void	load_menu_images(t_menu *menu)
{
	menu->logo = t_image_loadfromxpm("textures/cub_logo.xpm");
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
}

void	put_to_win(int posx, int pox_y, t_image image)
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_data	*data;

	data = data_hook(NULL);
	mlx_ptr = data->mlx.mlx_ptr;
	mlx_win = data->mlx.window_ptr;
	mlx_put_image_to_window(mlx_ptr, mlx_win, image.img_ptr, posx, pox_y);
}

int	show_menu()
{
	static int	n;
	static bool		Switch;
	t_data		*data;
	t_menu		menu;
	int			width_half;
	t_select	select;

	data = data_hook(NULL);
	width_half = WIN_WIDTH / 2;
	menu = data->menu;
	select = data->select_item;
	put_to_win(width_half - 240, (WIN_HEIGHT / 2) - 350, menu.logo);
	if (Switch)
		put_to_win(WIN_WIDTH - 240, (WIN_HEIGHT - 100), menu.hint);
	put_to_win(width_half - 140, ((WIN_HEIGHT / 2) -50), menu.us_new_game);
	put_to_win(width_half - 140, (WIN_HEIGHT / 2) +50, menu.us_cont);
	put_to_win(width_half - 140, (WIN_HEIGHT / 2) +150, menu.us_music);
	put_to_win(width_half - 140, (WIN_HEIGHT / 2) +250, menu.us_exit);
	if (data->select_item.item == 0)
		put_to_win(width_half - 140, ((WIN_HEIGHT / 2) -50), menu.s_new_game);
	if (data->select_item.item == 1)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) +50, menu.s_cont);
	if (data->select_item.item == 2)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) +150, menu.s_music);
	if (data->select_item.item == 3)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) +250, menu.s_exit);
	if (abs(n) % 30 == 0)
		Switch = Switch == false;
	n++;
	return (0);
}
