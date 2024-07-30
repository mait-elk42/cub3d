/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_effect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:29:57 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/30 18:16:19 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	play_effect(char *file_name)
{
	int child = fork();
	if (child == 0)
	{
		execvp("afplay", (char *[]){"afplay", "assets/sounds/navigation_effect1.mp3", NULL});
		exit(1);
	}
	waitpid(child, NULL, 0);
	return ;
}

void	make_effect(char *file_name)
{
	int		child;
	// char	*prog_path;
	pthread_t	thread;

	pthread_create(&thread, NULL, play_effect, NULL);
	pthread_detach(thread);
	// child = fork();
	// if (child == 0)
	// {
	// 	prog_path = "afplay";
	// 	execvp(prog_path, (char *[]){"afplay", file_name, NULL});
	// 	exit(1);
	// }
}
