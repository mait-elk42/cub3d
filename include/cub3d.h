/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:07:40 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/31 16:34:08 by aabouqas         ###   ########.fr       */
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
# include <stdbool.h>

/*
	* Text Colors
*/
# define COLOR_BLACK             "\033[30m"
# define COLOR_RED               "\033[31m"
# define COLOR_GREEN             "\033[32m"
# define COLOR_YELLOW            "\033[33m"
# define COLOR_BLUE              "\033[34m"
# define COLOR_MAGENTA           "\033[35m"
# define COLOR_CYAN              "\033[36m"
# define COLOR_WHITE             "\033[37m"
# define COLOR_UNDERLINE_BLACK   "\033[4;30m"
# define COLOR_UNDERLINE_RED     "\033[4;31m"
# define COLOR_UNDERLINE_GREEN   "\033[4;32m"
# define COLOR_UNDERLINE_YELLOW  "\033[4;33m"
# define COLOR_UNDERLINE_BLUE    "\033[4;34m"
# define COLOR_UNDERLINE_MAGENTA "\033[4;35m"
# define COLOR_UNDERLINE_CYAN    "\033[4;36m"
# define COLOR_UNDERLINE_WHITE   "\033[4;37m"
# define COLOR_RESET             "\033[0m"

/*
	* 	MLX KEYS AND EVENTS
*/
# define KEY_ESC       53
# define KEY_W         13
# define KEY_A         0
# define KEY_S         1
# define KEY_D         2
# define KEY_SHIFT     257
# define KEY_SPACE     49

# define ON_KEYDOWN    2
# define ON_KEYUP      3
# define ON_MOUSEDOWN  4
# define ON_MOUSEUP    5
# define ON_MOUSEMOVE  6
# define ON_EXPOSE     12
# define ON_DESTROY    17

# define GREEN 0x09EA57
# define DARK 0x0B0B0B
# define PINK 0xED0F87
# define DARK_GREEN 0x115852
# define BLUE 0x0111CD
# define BROWN 0x564F4D

/*
	* STRUCTS
*/

typedef struct s_key
{
	int		keycode;
	bool	pressed;
}	t_key;

typedef struct s_keys_status
{
	t_key	w;
	t_key	a;
	t_key	s;
	t_key	d;
}	t_keys_status;

typedef struct s_vector
{
	int		x;
	int		y;
}	t_vector;

typedef struct s_vector2
{
	double		x;
	double		y;
}	t_vector2;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_image
{
	void		*img_ptr;
	char		*buffer;
	int			pixel_add;
	int			sizex;
	int			sizey;
	int			bits_per_pixel;
	int			line_bytes;
	int			endian;
}	t_image;

typedef struct s_scene_info
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	t_color		floor_color;
	t_color		ceiling_color;
	int			maps_xsize;
	int			maps_ysize;
}	t_scene_info;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*window_ptr;
}	t_mlx;

typedef struct s_player
{
	t_image		*texture;
	t_vector	pos;
	t_vector2	global_pos;
	t_vector	dir;
}	t_player;

typedef struct s_data
{
	t_mlx				mlx;
	t_player			player;
	t_vector			pp;
	t_keys_status		keys;
	char				**lines;
	char				**maps;
	int					fd_file_input;
	t_scene_info		scene_info;
	t_image				*maps_image;
}	t_data;

/*
	* GARBAGE COLLECTOR
*/
t_data	*data_hook(t_data *data);

/*
	* 	INITIALIZATION
*/
void	data_init(t_data *data, int ac, char **av);

/**
 * 	STRINGS
*/
char	*str_skip(char *str, char *chars_to_skip);
int		str_equal(char *s1, char *s2);
char	*str_skip_wsp(char *str);

/**
 * ERRORS HANDLING
*/
void	safe_exit(int status);
void	put_error_sys(char *reason);
void	put_error(char *error, char *reason);
void	eput_error_sys(char *reason, int exit_status);
void	eput_error(char *error, char *reason, int exit_status);

/*
	* MAPS CHECK
*/
bool	check_file_ext(char *file_name, char *ext);
void	check_file(int ac, char **av);
void	init_lines(void);
void	check_maps(void);
void	check_color(char type, char *value);

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
	* FREE MEMORY
*/
void	free_tab(char **array);

/*
	* IO OPERATORS
*/
char	**append_2d(char **old_tab, char *to_append);
void	print(int fd, char *msg, int endl);
void	print_2d(char **arr);
void	logger(char *msg);

/*
	* GAME
*/
void	run_game(t_data	*data);

/*
	* IMAGES
*/
t_image	*t_image_create(int sizex, int sizey, int default_color);
void	t_image_update_pixel(t_image *imgptr, int x, int y, int new_color);

#endif
