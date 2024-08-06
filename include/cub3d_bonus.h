/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:07:40 by mait-elk          #+#    #+#             */
/*   Updated: 2024/08/06 12:27:21 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <libft.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <mlx.h>
# include <signal.h>
# include <pthread.h>

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
# define KEY_E		   14
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
	* ATTRIBUTES
*/
# define WIN_WIDTH 1440
# define WIN_HEIGHT 920
# define TILE_SIZE 32
# define P_SPEED 1.8
# define CAM_SENS 1.5
# define FOV 60
# define MPSIZE 0.15

typedef struct s_settings
{
	int		tile_size;
	double	player_speed;
	double	camera_sensibility;
	double	fov;
}	t_settings;

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
	bool	shift;
}	t_keys_status;

typedef struct s_vector
{
	int		x;
	int		y;
}	t_vector;

void		draw_mini_map(void);

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
	bool		hit_door_h;
	bool		hit_door_v;
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
	bool	new_game_1;
	bool	exit_selected;
	bool	cont_selected;
	bool	cont_2;
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
	float		real_head;
	float		head_angle;
	bool		is_walking;
	t_image		hand_frames[5];
}	t_player;

typedef struct s_mouse
{
	bool	to_left;
	bool	to_right;
	bool	to_up;
	bool	to_down;
	bool	center_mouse;
	double	cam_sens_h;
	double	cam_sens_v;
}	t_mouse;

typedef struct s_menu
{
	t_image		logo;
	t_image		bg;
	t_image		new_game_0;
	t_image		new_game_1;
	t_image		exit_0;
	t_image		exit_1;
	t_image		cont_0;
	t_image		cont_1;
	t_image		cont_2;
	t_image		music_0;
	t_image		music_1;
	t_image		hint;
}	t_menu;

typedef struct s_player_data
{
	t_vector	player_pos;
	float		player_angle;
}	t_player_data;

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
	int				ceiling;
	int				floor;
	t_image			texture_ea;
	t_image			texture_no;
	t_image			texture_so;
	t_image			texture_we;
	t_image			texture_door;
	t_size			screen;
	t_mouse			mouse;
	t_select		select_item;
	t_menu			menu;
	t_vector		mouse_pos_new;
	t_vector		mouse_pos;
	int				start;
	int				door_framemv;
	bool			player_looking_at_door;
	int				door_open;
	t_vector		door_pos;
	bool			looking_door;
	int				up_down;
	int				jump;
	bool			jumping;
	int				one_jump;
	t_player_data	p_data;
	t_image			north_icon;
	t_vector		north_icon_pos;
	bool			_switch;
	double			offset;
	pid_t			server;
	pid_t			tracker;
	pid_t			bgm;
	int				music;
	bool			music_switch;
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
t_data		*data_hook(t_data *data);

/*
	* 	INITIALIZATION
*/
void		data_init(t_data *data, int ac, char **av);
void		reset_doors(char **map);
/**
 * 	STRINGS
*/
char		*str_skip(char *str, char *chars_to_skip);
int			str_equal(char *s1, char *s2);
char		*str_skip_wsp(char *str);
int			strn_equal(char *s1, char *s2, int n);

/**
 * ERRORS HANDLING
*/
void		safe_exit(int status);
void		put_error_sys(char *reason);
void		put_error(char *error, char *reason);
void		eput_error_sys(char *reason, int exit_status);
void		eput_error(char *error, char *reason, int exit_status);

/*
	* map CHECK
*/
bool		check_file_ext(char *file_name, char *ext);
void		check_file(int ac, char **av);
void		init_lines(void);
void		check_map(void);
void		check_color(char type, char *value);
void		check_texture(char *varname, char *value);

/*
	* SAFE FUNCTIONS
*/
char		*safe_strjoin(char *str1, char *str2);
char		*safe_strrchr(char *s, char c);
char		*safe_strchr(char *s, char c);
void		*safe_calloc(size_t size);
char		*safe_strdup(char *s);
size_t		safe_strlen(char *str);
void		destroy_textures(void);

/*
	* FREE MEMORY
*/
void		free_tab(char **array);

/*
	* IO OPERATORS
*/

char		**append_2d(char **old_tab, char *to_append);
void		set_screen_size(void);
void		print(int fd, char *msg, int endl);
void		print_2d(char **arr);
float		normalize_angle(float angle);
void		normalize_sensibility(void);
void		put_2_window(void);
void		put_weapon(void);
void		player_effects(void);

/*
	* GAME
*/
void		init_player(t_data *data);
void		run_game(t_data	*data);
void		put_wall(t_data *data, int i, t_ray *ray);
int			check_hit(t_vector2 coords,
				t_ray *ray, t_vector2 *point, t_vector2 step);
void		send_ray(t_ray *ray);
float		get_distance(float angle, t_vector2 end);
t_vector2	get_step(t_ray ray, int type);
t_vector2	get_intercept_v(t_ray ray);
t_vector2	get_intercept_h(t_ray ray);
void		set_directions(t_ray *ray, int ray_type);
void		set_ray_side(t_ray *ray);
void		handle_selected_item(int key);
void		destroy_this(void **img_ptr);
void		show_menu(void);
void		handle_door(t_data *data, int keycode);
void		player_effects(void);
void		put_weapon(void);
int			is_door_minimap(t_vector2 pos, t_size sc, t_vector2 targ);

/*
	* IMAGES
*/
t_image		t_image_create(int sizex, int sizey, int default_color);
void		t_image_update_pixel(t_image *imgptr, int x, int y, int new_color);
void		t_image_clear_color(t_image *imgptr, int color);
t_image		t_image_load_xpm(char *filename);
void		load_menu_images(t_menu *menu);
void		destroy_menu(t_menu *menu);

/*
	* MATH
*/
float		deg_to_rad(float angle);
int			imin(int a, int b);
int			imax(int a, int b);
void		irange(int *v, int min, int max);
int			iinrange(int n, int min, int max);

/*
	* EVENTS
*/
int			ev_key_up(int keycode, t_data *data);
int			ev_key_down(int keycode, t_data *data);
int			ev_mouse_moved(int x, int y, void *data);
int			ev_destroy(t_data *data);

/**
	* DRAW
 */
void		draw_line(t_image *image, int color, t_vector2 from, t_vector2 to);
void		handle_input(t_data *data, float radi);
void		put_player_shape(double size);

/*
	* MENU
*/

void		hide_menu(void);
void		rest_player(void);
void		put_to_win(int posx, int pox_y, t_image image);
void		put_cub(t_data *data, t_vector2 offset, int size);

/*
	* PLAY BACK
*/

void		tracker(void);
void		server(void);
void		play_effect(void);
void		signal_handler(int signal);
bool		catch_signals(void);

#endif
