/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 08:35:46 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/15 13:05:46 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_maps(char **maps, t_image *img_layer)
{
	t_vector	i;
	t_vector	j;

	i.y = 0;
	j.y = 0;
	while (maps[i.y])
	{
		i.x = 0;
		j.x = 0;
		while (maps[i.y][i.x])
		{
			int	y = 0;
			while (y < TILE_SIZE)
			{
				int	x = 0;
				while (x < TILE_SIZE)
				{
					if (maps[i.y][i.x] == '1')
						t_image_update_pixel(img_layer, j.x + x, j.y + y, 0x0000ff);
					else if (maps[i.y][i.x] == '0' || maps[i.y][i.x] == 'P')
						t_image_update_pixel(img_layer, j.x + x, j.y + y, 0xffffff);
					x++;
				}
				y++;
			}
			i.x++;
			j.x+= TILE_SIZE;
		}
		i.y++;
		j.y+= TILE_SIZE;
	}
}

