/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:47:26 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/26 12:22:08 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	data_init(t_data *data_ptr, int ac, char **av)
{
	int	fd;

	data_hook(data_ptr);
	ft_bzero(data_ptr, sizeof(t_data));
	fd = check_file(ac, av);
	init_lines(fd);
	check_lines();
	printf("%zu\n", (size_t)data_hook(NULL)->scene_info.CEILING_color);
}
