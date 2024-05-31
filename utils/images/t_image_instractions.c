/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_image_instractions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:05:46 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/30 12:49:01 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_image	*t_image_create(int sizex, int sizey, int default_color)
{
	t_data	*data;
	t_image	*img;
	int		y;
	int		x;

	data = data_hook(NULL);
	if (sizex < 0 || sizey < 0)
		eput_error("negative number", "[IMAGE]", 1);
	img = safe_calloc(sizeof(t_image));
	img->img_ptr = mlx_new_image(data->mlx.mlx_ptr, sizex, sizey);
	if (img->img_ptr == NULL)
		eput_error("cannot create image", "[IMAGE]", 1);
	img->buffer = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->line_bytes, &img->endian);
	img->sizex = sizex;
	img->sizey = sizey;
	y = 0;
	while (y < sizey)
	{
		x = 0;
		while (x < sizex)
		{
			int pixel_byte = (y * img->line_bytes) + (x * 4);
			if (img->endian == 1) // Most significant (Alpha) byte first
			{
				img->buffer[pixel_byte + 0] = (default_color >> 24);
				img->buffer[pixel_byte + 1] = (default_color >> 16);
				img->buffer[pixel_byte + 2] = (default_color >> 8);
				img->buffer[pixel_byte + 3] = (default_color);
			}
			else
			{
				img->buffer[pixel_byte + 0] = (default_color);
				img->buffer[pixel_byte + 1] = (default_color >> 8);
				img->buffer[pixel_byte + 2] = (default_color >> 16);
				img->buffer[pixel_byte + 3] = (default_color >> 24);
			}
			x++;
		}
		y++;
	}
	return (img);
}


void	t_image_update_pixel(t_image *imgptr, int x, int y, int new_color)
{
	int pixel_byte;

	if (imgptr == NULL || x < 0 | y < 0)
		return ;
	pixel_byte = (y * imgptr->line_bytes) + (x * 4);
	if (imgptr->endian == 1) // Most significant (Alpha) byte first
	{
		imgptr->buffer[pixel_byte + 0] = (new_color >> 24);
		imgptr->buffer[pixel_byte + 1] = (new_color >> 16);
		imgptr->buffer[pixel_byte + 2] = (new_color >> 8);
		imgptr->buffer[pixel_byte + 3] = (new_color);
	}
	else
	{
		imgptr->buffer[pixel_byte + 0] = (new_color);
		imgptr->buffer[pixel_byte + 1] = (new_color >> 8);
		imgptr->buffer[pixel_byte + 2] = (new_color >> 16);
		imgptr->buffer[pixel_byte + 3] = (new_color >> 24);
	}
}
