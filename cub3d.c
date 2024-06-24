/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:09:17 by mait-elk          #+#    #+#             */
/*   Updated: 2024/06/11 16:10:22 by mait-elk         ###   ########.fr       */
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
	printf("mapx %d\n", data.scene_info.maps_xsize);
	printf("mapy %d\n", data.scene_info.maps_ysize);
	//
	// data.background_music = fork();
	// if (data.background_music == 0)
	// {
	// 	while (system("afplay audios/background_music.mp3") == 0);
	// 	exit (0);
	// }
	
	data.game_started = false;
	run_game(&data);
	safe_exit(0);
}
