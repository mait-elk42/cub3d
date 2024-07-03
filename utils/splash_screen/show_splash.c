/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_splash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:53:34 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/02 12:20:12 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <sys/time.h>
unsigned long n = 0;

void	splash_screen(t_data *data)
{
	(void)data;
	//
	// printf("press space to play.\n");
	// int color = 0xffff00;
	// t_image i = t_image_create(WIN_WIDTH, WIN_HEIGHT, color);
	// static int x_ = 0;
	// int x, y;
	// y = 0;
	// while (y < WIN_HEIGHT)
	// {
	// 	x = 0;
	// 	while (x < WIN_WIDTH)
	// 	{
	// 		if (x % (MINIMAP_TILE * 10) == 0 || y % (MINIMAP_TILE * 10) == 0)
	// 			color = 0xff0000;
	// 		else if (x % (MINIMAP_TILE * 5) == 0 || y % (MINIMAP_TILE * 5) == 0)
	// 			color = 0xffff00;
	// 		t_image_update_pixel(&i, x, y, color);
	// 		x++;
	// 	}
	// 	y++;
	// }
	// mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, i.img_ptr, x_, 0);
	// mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, i.img_ptr, -WIN_WIDTH+x_, 0);
	// x_+=10;
	// if (x_ > WIN_WIDTH)
	// 	x_ = 0;
	// static unsigned char opacity = 1;
	// // t_image p = t_image_loadfromxpm("textures/splash_icon.xpm");
	// t_image p = t_image_create(250, 250, 0xffffffff);
	// int y = 0;
	// while (y < p.sizey)
	// {
	// 	int x = 0;
	// 	while (x < p.sizex)
	// 	{
	// 		t_image_update_pixel(&p, x, y, (x * y * 2) * opacity);
	// 		x++;
	// 	}
	// 	y++;
	// }
	// opacity++;
	// mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr,  p.img_ptr, (WIN_WIDTH / 2) - p.sizex / 2, (WIN_HEIGHT / 2) - p.sizey / 2);
	
	t_image image = t_image_create(WIN_WIDTH, WIN_HEIGHT, 0x00000000);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->scene_layer.img_ptr, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, image.img_ptr, 0, 0);
	t_image background = t_image_create(WIN_WIDTH, 100, RGB_BLUE);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, background.img_ptr, 0, (WIN_HEIGHT - 200));
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->logo, 700, 150);
	if (n % 2)
	{
		mlx_string_put(data->mlx.mlx_ptr, data->mlx.window_ptr, (WIN_WIDTH / 2) - 100, (WIN_HEIGHT - 160), RGB_WHITE, "Press Space To Continue.");
		time_t time = 0;
		while (time < 9999999)
			time++;
	} else
	{
		mlx_string_put(data->mlx.mlx_ptr, data->mlx.window_ptr, (WIN_WIDTH / 2) - 100, (WIN_HEIGHT - 160), RGB_BLACK, "Press Space To Continue.");
		time_t time = 0;
		while (time < 9999999)
			time++;
	}
	if (n == 5)
		n = 0;
	// mlx_destroy_image(data->mlx.mlx_ptr, logo);
	n++;
}
