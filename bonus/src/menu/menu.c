/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:22:28 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/30 18:43:22 by mait-elk         ###   ########.fr       */
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

void	background_scale(t_data	*data, t_image	image)
{
	static int		x;
	static int		y;
	float	stepx;
	float	stepy;
	int		posx;
	int		posy;

	stepx = (float)image.width / WIN_WIDTH;
	stepy = (float)image.height / WIN_HEIGHT;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			posx = (int)(x * stepx) % image.width;
			posy = (int)(y * stepy) % image.height;
			t_image_update_pixel(&data->scene_layer, x, y, image.buffer[posy * image.width + posx]);
			x++;
		}
		y++;
	}
	put_to_win(0, 0, data->scene_layer);
}

void	set_defaults(t_menu menu)
{
	static char	n = 0;
	static bool	Switch;
	int			width_half;
	t_data		*data;

	data = data_hook(NULL);
	width_half = WIN_WIDTH / 2;
	background_scale(data, menu.bg);
	put_to_win(width_half - 240, (WIN_HEIGHT / 2) - 350, menu.logo);
	if (Switch)
		put_to_win((WIN_WIDTH / 2)- 140, (WIN_HEIGHT - 80), menu.hint);
	put_to_win(width_half - 140, ((WIN_HEIGHT / 2) -50), menu.us_new_game);
	if (data->start == 0)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) +50, menu.ig_cont);
	else
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) +50, menu.us_cont);
	put_to_win(width_half - 140, (WIN_HEIGHT / 2) +150, menu.us_music);
	put_to_win(width_half - 140, (WIN_HEIGHT / 2) +250, menu.us_exit);
	if (abs(n) % 35 == 0)
		Switch = Switch == false;
	n++;
}

int	show_menu()
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
		put_to_win(width_half - 140, ((WIN_HEIGHT / 2) -50), menu.s_new_game);
	if (data->select_item.item == 1)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) +50, menu.s_cont);
	if (data->select_item.item == 2)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) +150, menu.s_music);
	if (data->select_item.item == 3)
		put_to_win(width_half - 140, (WIN_HEIGHT / 2) +250, menu.s_exit);
	return (0);
}
