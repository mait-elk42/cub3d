/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:09:17 by mait-elk          #+#    #+#             */
/*   Updated: 2024/08/01 17:46:04 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	main(int ac, char **av)
{
	t_data	data;

	data_init(&data, ac, av);
	data.game_started = false;
	run_game(&data);
	safe_exit(0);
}
