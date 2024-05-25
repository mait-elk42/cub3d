/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:07:40 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/25 12:19:52 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>


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
 * 	STRINGS
*/
char	*_strchr(char *s, char c);
size_t	_strlen(char *str);
int		str_equal(char *s1, char *s2);
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
