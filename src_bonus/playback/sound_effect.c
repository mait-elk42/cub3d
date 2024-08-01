/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_effect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:29:57 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/31 13:46:01 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	*play_effectt(void *ptr)
{
	int	child;

	(void)ptr;
	child = fork();
	if (child == 0)
	{
		execvp("afplay", (char *[]){"afplay",
			"assets/sounds/navigation_effect1.mp3", NULL});
		exit(1);
	}
	waitpid(child, NULL, 0);
	return (NULL);
}

void	make_effect(char *file_name)
{
	pthread_t	thread;

	(void)file_name;
	pthread_create(&thread, NULL, play_effectt, NULL);
	pthread_detach(thread);
}
