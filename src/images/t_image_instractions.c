/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_image_instractions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:05:46 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/17 09:38:52 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_image	t_image_create(int sizex, int sizey, int default_color)
{
	t_data	*data;
	t_image	img;
	int		y;
	int		x;

	data = data_hook(NULL);
	if (sizex < 0 || sizey < 0)
		eput_error("negative number", "[IMAGE]", 1);
	img.img_ptr = mlx_new_image(data->mlx.mlx_ptr, sizex, sizey);
	if (img.img_ptr == NULL)
		eput_error("cannot create image", "[IMAGE]", 1);
	img.buffer = (int *)mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel,
			&img.line_bytes, &img.endian);
	img.sizex = sizex;
	img.sizey = sizey;
	y = -1;
	while (++y < sizey)
	{
		x = -1;
		while (++x < sizex)
			img.buffer[(y * (img.line_bytes / 4)) + (x)] = default_color;
	}
	return (img);
}

void	t_image_update_pixel(t_image *imgptr, int x, int y, int new_color)
{
	int	pixel_byte;

	if (imgptr == NULL || x < 0 | y < 0
		|| x > imgptr->sizex -1 || y > imgptr->sizey -1)
		return ;
	pixel_byte = (y * (imgptr->line_bytes / 4)) + x;
	imgptr->buffer[pixel_byte] = new_color;
}

void	t_image_clear_color(t_image *imgptr, int color)
{
	int		pixel_byte;
	int		x;
	int		y;

	if (imgptr == NULL)
		return ;
	y = 0;
	while (y < imgptr->sizey)
	{
		x = 0;
		while (x < imgptr->sizex)
		{
			pixel_byte = (y * (imgptr->line_bytes / 4)) + x;
			imgptr->buffer[pixel_byte + 0] = color;
			x++;
		}
		y++;
	}
}

t_image	t_image_loadfromxpm(char *filename)
{
	t_data	*data;
	t_image	img;

	data = data_hook(NULL);
	img.img_ptr = mlx_xpm_file_to_image(data->mlx.mlx_ptr,
			filename, &img.sizex, &img.sizey);
	if (img.img_ptr == NULL)
		eput_error("cannot load image", filename, 1);
	img.buffer = (int *)mlx_get_data_addr(img.img_ptr,
			&img.bits_per_pixel, &img.line_bytes, &img.endian);
	return (img);
}
