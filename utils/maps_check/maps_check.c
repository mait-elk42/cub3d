/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 09:57:01 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/25 11:33:15 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_maps_validation(char *file_name)
{
	int	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("\033[31merror-> check_maps_validation\033[0m");
		exit(1);
	}
	close(fd);
}
