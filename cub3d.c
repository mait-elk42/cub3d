/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:09:17 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/20 12:16:29 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_leaks(int i)
{
	if (i == 1)
		atexit((void (*)(void))check_leaks);
	else
	{
		logger("====================leaks===========================");
		system("leaks cub3d | grep bytes");
		logger("====================lsof===========================");
		system("lsof -c cub3d");
		logger("=====================================================");
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	data_init(&data, ac, av);
	check_leaks(1);
	data.game_started = true;
	run_game(&data);
	safe_exit(0);
}
