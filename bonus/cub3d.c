/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:09:17 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/22 14:55:48 by aabouqas         ###   ########.fr       */
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

#include <unistd.h>
#include <signal.h>


void	signal_handler(int signal)
{
	(void)signal;
	kill (data_hook(NULL)->child, SIGKILL);
	exit (1);
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
		signal(SIGHUP, signal_handler);
		while (1)
		{
			data.child = fork();
			if (data.child == 0)
				execve("/usr/bin/afplay", (char *[]) {"afplay", "assets/main_menu1.mp3", NULL}, NULL);
			waitpid(data.child, NULL, 0);
		}
		safe_exit(1);
	}
	run_game(&data);
	safe_exit(0);
}
