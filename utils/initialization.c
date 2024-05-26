/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:47:26 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/26 09:34:21 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	data_init(t_data *data_ptr, int ac, char **av)
{
	data_hook(data_ptr);
	logger("checking args.");
	check_args(ac, av);
	ft_bzero(data_ptr, sizeof(t_data));
	check_extension(av[1]);
	init_lines(av[1]);
	check_lines();
	printf("%zu\n", (size_t)data_hook(NULL)->scene_info.CEILING_color);
}
