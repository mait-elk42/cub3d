/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:11:56 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/30 19:40:33 by aabouqas         ###   ########.fr       */
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
	// mlx_clear_window(data->mlx.mlx_ptr, data->mlx.window_ptr);
	// mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.window_ptr, data->maps_image->img_ptr, 120, 170);
	// put_maps(data->maps, data->mlx);
	t_vector2	v;
	t_vector2	v2;
	ft_bzero(&v, sizeof(v));
	ft_bzero(&v2, sizeof(v2));
	while (data->maps[v.y])
	{
		v.x = 0;
		while (data->maps[v.y], v.x)
		{
			// mlx_pixel_put(data->mlx, );
		}
		v.y++;
	}
	return (0);
}

int key_down(int keycode, t_data *data)
{
	(void)data;
	if (keycode == 53) // esc key
		safe_exit(0);
	if (keycode == 49)
	{
		for (int i = 0; i < data->scene_info.maps_ysize * 10; i++)
		for (int j = 0; j < data->scene_info.maps_xsize * 10; j++)
		{
			if (j * 10 % 2 == 0 && j < 10)
				t_image_update_pixel(data->maps_image, j, i, 0xffff00);
		}
	}
	printf("pressed key : %d\n", keycode);
	return (0);
}

void	run_game(t_data *data)
{
	// int	width = data->scene_info.maps_xsize * 10;
	// int	height = data->scene_info.maps_ysize * 10;
	// data->maps_image = t_image_create(width, height, 0xffffff);
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, data);
	mlx_hook(data->mlx.window_ptr, 2, 0, key_down, data);
	mlx_loop(data->mlx.mlx_ptr);
}
