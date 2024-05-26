/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:07:40 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/26 16:29:33 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include <stdio.h>
# include <mlx.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

/*
	* Regular Text Colors
*/
# define COLOR_BLACK   "\033[30m"
# define COLOR_RED     "\033[31m"
# define COLOR_GREEN   "\033[32m"
# define COLOR_YELLOW  "\033[33m"
# define COLOR_BLUE    "\033[34m"
# define COLOR_MAGENTA "\033[35m"
# define COLOR_CYAN    "\033[36m"
# define COLOR_WHITE   "\033[37m"

/*
	* Underline Text Colors
*/
# define COLOR_UNDERLINE_BLACK   "\033[4;30m"
# define COLOR_UNDERLINE_RED     "\033[4;31m"
# define COLOR_UNDERLINE_GREEN   "\033[4;32m"
# define COLOR_UNDERLINE_YELLOW  "\033[4;33m"
# define COLOR_UNDERLINE_BLUE    "\033[4;34m"
# define COLOR_UNDERLINE_MAGENTA "\033[4;35m"
# define COLOR_UNDERLINE_CYAN    "\033[4;36m"
# define COLOR_UNDERLINE_WHITE   "\033[4;37m"

/*
	* Reset Color
*/
# define COLOR_RESET "\033[0m"

/*
	* STRUCTS
*/

typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;


typedef struct s_scene_textures {
	char	*NORTH_texture;
	char	*SOUTH_texture;
	char	*WEST_texture;
	char	*EAST_texture;
	t_color	FLOOR_color;
	t_color	CEILING_color;
}	t_scene_textures;

typedef struct s_data
{
	t_scene_textures	scene_info;
	char				**lines;
	char				**maps;
}	t_data;

/*
	* GARBAGE COLLECTOR
*/
t_data	*data_hook(t_data *data);

/*
	* 	INITIALIZATION
*/
void	data_init(t_data *data_ptr, int ac, char **av);

/**
 * 	STRINGS
*/
char	*str_skip(char *str, char *chars_to_skip);
int		str_equal(char *s1, char *s2);

/**
 * ERRORS HANDLING
*/
void	safe_exit(int status);
void	put_error_syscall(char *reason);
void	put_error_custom(char *error, char *reason);

/*
	* MAPS CHECK
*/
int		check_file(int ac, char **av);
void	init_lines(int fd);
void	check_lines();

/*
	* SAFE FUNCTIONS
*/
char	*safe_strjoin(char *str1, char *str2);
char	*safe_strrchr(char *s, char c);
char	*safe_strchr(char *s, char c);
void	*safe_calloc(size_t size);
char	*safe_strdup(char *s);
size_t	safe_strlen(char *str);

/*
	* IO OPERATORS
*/
char	**append_2d(char **old_tab, char *to_append);
void	print(int fd, char *msg, int endl);
void	logger(char *msg);

#endif
