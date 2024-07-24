/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:40:41 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/24 20:14:52 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	signal_handler(int signal)
{
	if (signal == SIGUSR1)
	{
		if (getppid() == 1 || getppid() == -1)
		{
			kill (data_hook(NULL)->child, SIGKILL);
			exit (1);
		}
		return ;
	}
	kill (data_hook(NULL)->child, SIGKILL);
	exit (0);
}

int	track_parent(void)
{
	int	child;

	child = fork();
	if (child == 0)
	{
		while (kill (getppid(), SIGUSR1) == 0)
			;
		exit (0);
	}
	return child;
}

void	play_music(void)
{
	t_data	*data;
	char	*program_path;

	data = data_hook(NULL);
	data->background_music = fork();
	if (data->background_music == 0)
	{
		signal(SIGHUP, signal_handler);
		signal(SIGUSR1, signal_handler);
		int child = track_parent();
		while (1)
		{
			data->child = fork();
			if (data->child == 0)
			{
				program_path = "/usr/bin/afplay";
				execve(program_path,
					(char *[]){"afplay", "assets/sounds/main_menu1.mp3", NULL},
					NULL);
			}
			waitpid(data->child, NULL, 0);
		}
		safe_exit(1);
	}
}
