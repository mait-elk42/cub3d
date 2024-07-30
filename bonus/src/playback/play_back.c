/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:40:41 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/30 18:41:20 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	signal_handler(int signal)
{
	if (signal == SIGUSR1)
	{
		if (getppid() == 1 || getppid() == -1)
		{
			kill (data_hook(NULL)->child.pid, SIGKILL);
			data_hook(NULL)->child.pid = -1;
			exit (1);
		}
		return ;
	}
	kill (data_hook(NULL)->child.pid, SIGKILL);
	exit (0);
}

int	track_parent(void)
{
	int	child;

	child = fork();
	if (child == 0)
	{
		while (getppid() > 0 && kill (getppid(), SIGUSR1) == 0)
			;
		exit (0);
	}
	return (child);
}

void	play_music(void)
{
	t_data	*data;
	char	*pn;

	data = data_hook(NULL);
	return ;
	data->background_music = fork();
	pn = "afplay";
	if (data->background_music == 0)
	{
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
		track_parent();
		while (1)
		{
			data->child.pid = fork();
			if (data->child.pid == 0)
			{
				execvp(pn, (char *[]){pn,
					"assets/sounds/main_menu4.mp3", NULL});
				safe_exit(1);
			}
			waitpid(data->child.pid, NULL, 0);
		}
		safe_exit(1);
	}
}
