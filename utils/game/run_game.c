/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/31 15:46:50 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_maps(char **maps, t_mlx mlx)
{
	t_vector	i;
	t_vector	j;
	t_vector	offset;

	i.y = 0;
	j.y = 0;
	(void)mlx;
	offset = (t_vector){0, 0};
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
	// mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	// mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->maps_image->img_ptr, 120, 170);
	// put_maps(data->maps, data->mlx);
	data++;
	return (0);
}

int key_down(int keycode, t_data *data)
{
	(void)data;
	if (keycode == 53) // esc key
		safe_exit(0);
	if (keycode == 49)
	{
		// on press space
	}
	printf("pressed key : %d\n", keycode);
	return (0);
}

void	run_game(t_data *data)
{
	data->maps_image = t_image_create(data->scene_info.maps_xsize * 25,data->scene_info.maps_ysize * 25, 0x000000);
	put_maps(data->maps, data->mlx);
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, 2, (1L<<0), key_down, data);
	mlx_loop(data->mlx.mlx_ptr);
}
