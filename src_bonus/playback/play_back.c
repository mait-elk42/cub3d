/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:40:41 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/31 16:50:16 by mait-elk         ###   ########.fr       */
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
			data_hook(NULL)->child.pid = -4;
			exit (0);
		}
		return ;
	}
	kill (data_hook(NULL)->child.pid, SIGKILL);
	data_hook(NULL)->child.pid = -4;
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

int	catch_signals(void)
{
	bool	error;

	error = false;
	if (signal(SIGUSR1, signal_handler) == SIG_ERR)
		error = true;
	if (signal(SIGUSR2, signal_handler) == SIG_ERR)
		error = true;
	if (error)
	{
		print(2, "Unable to catch signals", 1);
		return (-1);
	}
	return (0);
}

void	start(void)
{
	t_data	*data;

	data = data_hook(NULL);
	while (1)
	{
		data->child.pid = fork();
		if (data->child.pid == 0)
		{
			execvp("afplay", (char *[]){"afplay",
				"assets/sounds/main_menu4.mp3", NULL});
			safe_exit(-1);
		}
		if (data->child.pid == -1)
		{
			print(2, "Unexpected Error", 1);
			break ;
		}
		if (waitpid (data->child.pid, data->child.ret_val, 0) <= 0)
			break ;
		if (WEXITSTATUS(data->child.ret_val) == -1)
			break ;
	}
}

void	play_music(void)
{
	t_data	*data;

	data = data_hook(NULL);
	data->background_music = fork();
	if (data->background_music == 0)
	{
		if (catch_signals() == -1)
			exit (1);
		track_parent();
		start();
		safe_exit(1);
	}
	if (data->child.pid == -1)
		print (2, "Unable to play music", 1);
}
