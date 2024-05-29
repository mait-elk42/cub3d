/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/29 19:18:32 by mait-elk         ###   ########.fr       */
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
	offset = (t_vector2){20, 20};
	while (maps[i.y])
	{
		i.x = 0;
		j.x = 0;
		while (maps[i.y][i.x])
		{
			int	y = 0;
			while (y < 19)
			{
				int	x = 0;
				while (x < 19)
				{
					if (maps[i.y][i.x] == '0')
						mlx_pixel_put(mlx.mlx_ptr, mlx.window_ptr, j.x + x + offset.x, j.y + y + offset.y, 0xffffff);
					if (maps[i.y][i.x] == '1')
						mlx_pixel_put(mlx.mlx_ptr, mlx.window_ptr, j.x + x + offset.x, j.y + y + offset .y, 0x0000ff);
					if (maps[i.y][i.x] == ' ')
						mlx_pixel_put(mlx.mlx_ptr, mlx.window_ptr, j.x + x + offset.x, j.y + y + offset .y, 0xff0000);
					if (maps[i.y][i.x] == 'N')
						mlx_pixel_put(mlx.mlx_ptr, mlx.window_ptr, j.x + x + offset.x, j.y + y + offset .y, 0x00ff00);
					x++;
				}
				y++;
			}
			i.x++;
			j.x+= 20;
		}
		i.y++;
		j.y+= 20;
	}
}

int	game_loop(t_data *data)
{
	(void)data;
	// mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	// put_maps(data->maps, data->mlx);
	return (0);
}

int key_down(int keycode, t_data *data)
{
	(void)data;
	if (keycode == 53) // esc key
		safe_exit(0);
	return (0);
}

void	run_game(t_data *data)
{
	void *image = mlx_new_image(data->mlx.mlx_ptr, 100, 100);
	int pixel_bits;
	int line_bytes;
	int endian;
	char *buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
	int color = 0xABCDEF;

	if (pixel_bits != 32)
		color = mlx_get_color_value(data->mlx.mlx_ptr, color);

	for(int y = 0; y < 100; ++y)
	for(int x = 0; x < 100; ++x)
	{
		int pixel = (y * line_bytes) + (x * 4);

		if (endian == 1)        // Most significant (Alpha) byte first
		{
			buffer[pixel + 0] = (color >> 24);
			buffer[pixel + 1] = (color >> 16) & 0xFF;
			buffer[pixel + 2] = (color >> 8) & 0xFF;
			buffer[pixel + 3] = (color) & 0xFF;
		}
		else if (endian == 0)   // Least significant (Blue) byte first
		{
			buffer[pixel + 0] = (color) & 0xFF;
			buffer[pixel + 1] = (color >> 8) & 0xFF;
			buffer[pixel + 2] = (color >> 16) & 0xFF;
			buffer[pixel + 3] = (color >> 24);
		}
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, image, 100, 100);
	image = NULL;
	buffer = NULL;
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, 2, 0, key_down, data);
}
