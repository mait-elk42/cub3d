/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:09:17 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/21 19:09:24 by aabouqas         ###   ########.fr       */
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

	// check_leaks(1);
	data_init(&data, ac, av);
	data.game_started = false;
	data.background_music = fork();
	if (data.background_music == 0)
	{
		while (1)
		{
			execve("/usr/bin/afplay", (char *[]) {"afplay", "assets/main_menu2.mp3", NULL}, NULL);
		}
		safe_exit(1);
	}
	run_game(&data);
	safe_exit(0);
}
