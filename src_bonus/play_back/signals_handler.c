/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:37:55 by aabouqas          #+#    #+#             */
/*   Updated: 2024/08/06 11:57:56 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	signal_handler(int signal)
{
	static bool	_switcher = false;

	if (signal == SIGUSR1)
	{
		(data_hook(NULL)->bgm) && kill (data_hook(NULL)->bgm, SIGKILL);
		safe_exit (0);
	}
	if (signal == SIGUSR2)
	{
		if (_switcher == false)
		{
			data_hook(NULL)->music_switch = false;
			(data_hook(NULL)->bgm) && kill (data_hook(NULL)->bgm, SIGKILL);
		}
		else
			data_hook(NULL)->music_switch = true;
		_switcher = _switcher == false;
	}
	if (signal == SIGHUP)
		play_effect();
	if (signal == SIGPROF)
	{
		data_hook(NULL)->music = data_hook(NULL)->music == 0;
		(data_hook(NULL)->bgm) && kill (data_hook(NULL)->bgm, SIGKILL);
	}
}

bool	catch_signals(void)
{
	bool	err;

	err = false;
	if (signal (SIGUSR1, signal_handler) == SIG_ERR)
		err = true;
	if (err == false && signal (SIGUSR2, signal_handler) == SIG_ERR)
		err = true;
	if (err == false && signal (SIGHUP, signal_handler) == SIG_ERR)
		err = true;
	if (err == false && signal (SIGPROF, signal_handler) == SIG_ERR)
		err = true;
	return (err);
}
