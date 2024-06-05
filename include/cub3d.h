/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:07:40 by mait-elk          #+#    #+#             */
/*   Updated: 2024/06/05 11:06:25 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <stdio.h>
# include <mlx.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include <colors.h>

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
# define KEY_UP        126
# define KEY_DOWN      125
# define KEY_LEFT      123
# define KEY_RIGHT     124

# define ON_KEYDOWN    2
# define ON_KEYUP      3
# define ON_MOUSEDOWN  4
# define ON_MOUSEUP    5
# define ON_MOUSEMOVE  6
# define ON_EXPOSE     12
# define ON_DESTROY    17


/*
	* 	WIN SIZE
*/
# define WIN_WIDTH 1924  // x
# define WIN_HEIGHT 1092 // y

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
	t_key	up;
	t_key	down;
	t_key	left;
	t_key	right;
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
	t_vector2	pos;
	t_vector	cam_pos;
	t_image		texture;
	double		angle;
}	t_player;

typedef struct s_data
{
	t_mlx				mlx;
	t_player			player;
	t_keys_status		keys;
	char				**lines;
	char				**maps;
	int					fd_file_input;
	t_scene_info		scene_info;
	t_image				scene_layer;
	t_image				minimaps_layer;
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
void	init_keys(t_data *data);
void	init_player(t_data *data);
void	run_game(t_data	*data);

/*
	* IMAGES
*/
t_image	t_image_create(int sizex, int sizey, int default_color);
void	t_image_update_pixel(t_image *imgptr, int x, int y, int new_color);
void	t_image_clear_color(t_image *imgptr, int color);
t_image	t_image_loadfromxpm(char *filename);
void	t_image_set_angle(t_image *imgptr, double angle);

/*
	* MATH
*/
double	mth_degtorad(double angle);

/*
	* EVENTS
*/
int		ev_key_up(int keycode, t_data *data);
int		ev_key_down(int keycode, t_data *data);


#endif
