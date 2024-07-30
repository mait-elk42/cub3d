/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:09:17 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/30 19:16:08 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	check_leaks(int i)
{
	if (i == 1)
		atexit((void (*)(void))check_leaks);
	else
	{
		printf("====================leaks===========================");
		system("leaks cub3d | grep bytes");
		printf("====================lsof===========================");
		system("lsof -c cub3d");
		printf("=====================================================");
	}
}

void	leaks()
{
	system("leaks cub3d_bonus");
}

int	main(int ac, char **av)
{
	// atexit(leaks);
	t_data	data;

	data_init(&data, ac, av);
	data.game_started = false;
	play_music();
	run_game(&data);
	safe_exit(0);
	exit (0);
}
