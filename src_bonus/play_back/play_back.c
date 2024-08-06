/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:58:35 by aabouqas          #+#    #+#             */
/*   Updated: 2024/08/06 12:48:29 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	tracker(void)
{
	t_data	*data;

	data = data_hook(NULL);
	data->tracker = fork();
	if (data->tracker == 0)
	{
		while (true)
		{
			if (getppid() == 1 || getppid() == -1)
			{
				kill (0, SIGKILL);
				exit (0);
			}
			usleep (800);
		}
	}
	if (data->tracker == -1)
		exit (1);
}

void	*make_sound(void *param)
{
	pid_t	child;
	int		ret;

	child = fork();
	(void)param;
	if (child == 0)
	{
		close (2);
		execlp("afplay", "afplay", "assets/nav_effect.mp3", NULL);
		exit (1);
	}
	waitpid(child, &ret, 0);
	if (WEXITSTATUS(ret) == 1)
		print(2, "\033[33mWARNING : Failed to play sound effect\033[0m", 1);
	return (NULL);
}

void	play_effect(void)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, make_sound, NULL);
	pthread_detach(thread);
}

void	play_music(void)
{
	t_data	*data;
	int		val;

	data = data_hook(NULL);
	val = 0;
	data->bgm = fork();
	if (data->bgm == 0)
	{
		close (2);
		if (data->music == 0)
			execlp("afplay", "afplay", "assets/sounds/main_menu.mp3", NULL);
		else if (data->music == 1)
			execlp("afplay", "afplay", "assets/sounds/cave.mp3", NULL);
		exit (1);
	}
	if (data->bgm == -1)
		exit (1);
	waitpid(data->bgm, &val, 0);
	if (WEXITSTATUS(val) == 1)
	{
		print(2, "\033[33mWARNING : Failed to play music\033[0m", 1);
		data->music_switch = false;
	}
}

void	server(void)
{
	t_data	*data;

	data = data_hook(NULL);
	data->server = fork();
	if (data->server == 0)
	{
		if (catch_signals() == true)
			exit (1);
		sleep (1);
		while (true)
		{
			if (data->music_switch == true)
				play_music();
			if (data->music_switch == false)
				sleep (2);
		}
		exit (0);
	}
	if (data->server == -1)
		exit (1);
}
