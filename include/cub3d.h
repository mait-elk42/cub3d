/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:07:40 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/25 11:25:47 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>


typedef struct s_data
{
	char	**maps;
}	t_data;

/**
 * GARBAGE COLLECTOR
*/
t_data	*data_hook(t_data *data);

/**
 * 	INITIALIZATION
*/
void	data_init(t_data *data_ptr, int ac, char **av);

/**
 * ERRORS HANDLING
*/
void	check_args(int ac, char **av);
void	safe_exit(int status);

/*
 * MAPS CHECK
*/
void	check_extension(char *file_name);
void	check_maps_validation(char *file_name);

/**
 * IO OPERATORS
*/
void	*safe_calloc(size_t size);
void	print(int fd, char *msg, int endl);
char	**append_2d(char **old_tab, char *to_append);

#endif
