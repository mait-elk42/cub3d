/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/30 13:05:26 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_maps(char **maps, t_mlx mlx)
{
	t_vector2	i;
	t_vector2	j;
	t_vector2	offset;

	i.y = 0;
	j.y = 0;
	(void)mlx;
	offset = (t_vector2){0, 0};
	while (maps[i.y])
	{
		i.x = 0;
		j.x = 0;
		while (maps[i.y][i.x])
		{
			int	y = 0;
			while (y < 25)
			{
				int	x = 0;
				while (x < 25)
				{
					if (maps[i.y][i.x] == '0' || maps[i.y][i.x] == 'N')
						t_image_update_pixel(data_hook(NULL)->maps_image, j.x + x + offset.x, j.y + y + offset.y, 0xffffff);
					if (maps[i.y][i.x] == '1')
						t_image_update_pixel(data_hook(NULL)->maps_image, j.x + x + offset.x, j.y + y + offset .y, 0x0000ff);
					// if (maps[i.y][i.x] == 'N')
					// 	t_image_update_pixel(data_hook(NULL)->maps_image, j.x + x + offset.x, j.y + y + offset .y, 0x00ff00);
					x++;
				}
				y++;
			}
			i.x++;
			j.x+= 25;
		}
		i.y++;
		j.y+= 25;
	}
}

int	game_loop(t_data *data)
{
	(void)data;
	put_maps(data->maps, data->mlx);
	mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->maps_image->img_ptr, 100, 100);
	return (0);
}

int key_down(int keycode, t_data *data)
{
	(void)data;
	if (keycode == 53) // esc key
		safe_exit(0);
	if (keycode == 49)
	{
		// press space
		// for (int i = 0; i < data->scene_info.maps_ysize * 10; i++)
		// for (int j = 0; j < data->scene_info.maps_xsize * 10; j++)
		// {
		// 	if (j * 10 % 2 == 0 && j < 10)
		// 		t_image_update_pixel(data->maps_image, j, i, 0xffff00);
		// }
	}
	printf("pressed key : %d\n", keycode);
	return (0);
}

void	run_game(t_data *data)
{
	data->maps_image = t_image_create(data->scene_info.maps_xsize * 25
								,data->scene_info.maps_ysize * 25
								, 0x000000);
	// if (maps.bits_per_pixel != 32)
	// 	color = mlx_get_color_value(data->mlx.mlx_ptr, color);
	// for(size_t y = 0; y < maps.sizey * 10; ++y)
	// {
	// 	for(size_t x = 0; x < maps.sizex * 10; ++x)
	// 	{
	// 		int pixel = (y * maps.line_bytes) + (x * 4);
	// 		if (maps.endian == 1)        // Most significant (Alpha) byte first
	// 		{
	// 			maps.buffer[pixel + 0] = (color >> 24);
	// 			maps.buffer[pixel + 1] = (color >> 16);
	// 			maps.buffer[pixel + 2] = (color >> 8);
	// 			maps.buffer[pixel + 3] = (color);
	// 		}
	// 		else if (maps.endian == 0)   // Least significant (Blue) byte first
	// 		{
	// 			maps.buffer[pixel + 0] = (color);
	// 			maps.buffer[pixel + 1] = (color >> 8);
	// 			maps.buffer[pixel + 2] = (color >> 16);
	// 			maps.buffer[pixel + 3] = (color >> 24);
	// 		}
	// 	}
	// 	color+= 0x0000ff;
	// }

	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, 2, 0, key_down, data);
	mlx_loop(data->mlx.mlx_ptr);
}
