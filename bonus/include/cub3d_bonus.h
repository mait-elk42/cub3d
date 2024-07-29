/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:07:40 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/29 18:05:14 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <signal.h>
# include <sys/time.h>
# include <mlx.h>
# include <unistd.h>
# include <signal.h>


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

# define VERTICAL 0
# define HORIZONTAL 1

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
# define KEY_RETURN    36

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
# define WIN_WIDTH (1280)
# define WIN_HEIGHT (920)

/*
	* ATTRIBUTES
*/

typedef struct s_settings
{
	int		tile_size;
	double	player_speed;
	double	camera_sensibility;
	double	fov;
}	t_settings;


# define TILE_SIZE 32
# define PLAYER_SPEED 1.8
# define CAM_SENS 2
# define FOV 60
# define MPSIZE 0.15

/*
	* ENUMS
*/

typedef enum e_side
{
	LEFT,
	RIGHT,
	UP,
	DOWN
}	t_side;

typedef enum e_direction
{
	UNKNOWN,
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_direction;

/*
	* STRUCTS
*/

typedef struct s_keys_status
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	bool	space;
}	t_keys_status;

typedef struct s_vector
{
	int		x;
	int		y;
}	t_vector;

void	draw_mini_map();

typedef struct s_vector2
{
	float	x;
	float	y;
}	t_vector2;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_ray
{
	t_vector2	intercept;
	t_direction	direction;
	float		distance;
	float		angle;
	bool		face_up;
	bool		face_down;
	bool		face_left;
	bool		face_right;
	short		side;
	bool		hit_wall;
	bool		hit_door;
}	t_ray;

typedef struct s_size
{
	size_t	width;
	size_t	height;
}	t_size;

typedef struct s_select
{
	int		item;
	bool	new_game_selected;
	bool	exit_selected;
	bool	cont_selected;
	bool	cont_ignored;
	bool	music;
}	t_select;


typedef struct s_image
{
	void		*img_ptr;
	int			*buffer;
	int			width;
	int			height;
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
	int			map_width;
	int			map_height;
}	t_scene_info;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*window_ptr;
}	t_mlx;

typedef struct s_player
{
	t_vector2	position;
	t_image		texture;
	float		angle;
	t_vector2	walking_dir;
	float		real_head;
	float		head_angle;
	bool		is_walking;
	t_image		hand_frames[5];
}	t_player;

typedef struct s_mouse
{
	bool	to_left;
	bool	to_right;
	// bool	to_top;
	// bool	to_down;
	bool	center_mouse;
	double	cam_sens;
}	t_mouse;

typedef struct s_menu
{
	t_image		logo;
	t_image		s_new_game;
	t_image		us_new_game;
	t_image		s_exit;
	t_image		us_exit;
	t_image		s_cont;
	t_image		ig_cont;
	t_image		us_cont;
	t_image		s_music;
	t_image		us_music;
	t_image		hint;
}	t_menu;

typedef struct s_data
{
	bool			game_started;
	t_mlx			mlx;
	t_player		player;
	t_keys_status	key_pressed;
	t_settings		settings;
	char			**lines;
	char			**map;
	int				fd_file_input;
	t_scene_info	scene_info;
	t_image			scene_layer;
	t_image			minimap_layer;
	int				background_music;
	int				ceiling;
	int				floor;
	t_image			logo;
	t_image			texture_ea;
	t_image			texture_no;
	t_image			texture_so;
	t_image			texture_we;
	t_image			texture_door;
	t_size			screen;
	t_mouse			mouse;
	t_select		select_item;
	t_menu			menu;
	pid_t			child;
	t_vector		mouse_pos_new;
	t_vector		mouse_pos;
	bool			music;
}	t_data;

typedef struct s_wall_text
{
	t_image		t;
	int			wallheight;
	int			top;
	int			btm;
	float		yunit;
	float		xunit;
	int			color;
	int			y;
	t_vector	t_offset;
	t_vector2	step;
}	t_wall_text;

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
	* map CHECK
*/
bool	check_file_ext(char *file_name, char *ext);
void	check_file(int ac, char **av);
void	init_lines(void);
void	check_map(void);
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
void	set_screen_size(void);
void	print(int fd, char *msg, int endl);
void	print_2d(char **arr);
float	normalize_angle(float angle);
void	logger(char *msg);

/*
	* GAME
*/
void	init_player(t_data *data);
void	run_game(t_data	*data);
void	put_wall(t_data *data, int i, t_ray *ray);
int		check_hit(t_vector2 coords, t_ray *ray, t_vector2 *point, t_vector2 step);
void	put_bgd(t_image *image, int ceil_color, int floor_color);
void	send_ray(t_ray *ray, double ray_angle);
t_ray	send_horizontal_ray(float ray_angle, t_size screen_size);
t_ray	send_virtical_ray(float ray_angle, t_size screen_size);
float	get_distence(float angle, t_vector2 end);
void	set_distence(t_ray *ray);
void	set_directions(t_ray *ray, int ray_type);
void	set_ray_side(t_ray *ray, float angle);
void	handle_selected_item(int key);
void	destroy_this(void *img_ptr);
int		show_menu();

/*
	* IMAGES
*/
t_image	t_image_create(int sizex, int sizey, int default_color);
void	t_image_update_pixel(t_image *imgptr, int x, int y, int new_color);
void	t_image_clear_color(t_image *imgptr, int color);
t_image	t_image_loadfromxpm(char *filename);
void	load_menu_images(t_menu *menu);
void	destroy_images(t_menu *menu);


/*
	* PLAY_BACK
*/
void	play_music(void);

/*
	* MATH
*/
float	deg_to_rad(float angle);
long	get_time(void);
int		imin(int a, int b);
int		imax(int a, int b);
void	irange(int *v, int min, int max);

/*
	* EVENTS
*/
int		ev_key_up(int keycode, t_data *data);
int		ev_key_down(int keycode, t_data *data);

/**
	* DRAW
 */
void	draw_line(t_image *image, int color, t_vector2 from, t_vector2 to);
void	put_map(char **map, t_image *img_layer);
void	handle_input(t_data *data, float radi);
void	put_player_shape(double size);

/*
	* SPLASH SCREEN
*/
void	splash_screen(t_data *data);

#endif
