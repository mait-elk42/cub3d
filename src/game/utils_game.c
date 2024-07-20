/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:06:57 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/20 13:52:32 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	sliding_against_wall(bool mv_x, bool mv_y, t_vector2 axis)
{
	t_data		*data;
	t_vector2	pp;
	char		**map;
	int			tile_size;
	int			player_speed;

	data = data_hook(NULL);
	tile_size = data->settings.tile_size;
	player_speed = data->settings.player_speed;
	map = data->maps;
	pp = data->player.position;
	if (mv_y != mv_x && mv_x == true)
	{
		if (map[(int)(pp.y) / tile_size][(int)(pp.x + 10) / tile_size] == '1')
			data->player.position.x -= axis.x * player_speed;
		if (map[(int)(pp.y) / tile_size][(int)(pp.x - 10) / tile_size] == '1')
			data->player.position.x -= axis.x * player_speed;
	}
	if (mv_y != mv_x && mv_y == true)
	{
		if (map[(int)(pp.y + 10) / tile_size][(int)(pp.x) / tile_size] == '1')
			data->player.position.y -= axis.y * player_speed;
		if (map[(int)(pp.y - 10) / tile_size][(int)(pp.x) / tile_size] == '1')
			data->player.position.y -= axis.y * player_speed;
	}
}

void	mooove(bool *mv_x, bool *mv_y, t_vector2 axis)
{
	t_data		*data;
	char		**map;
	int			tile_size;
	int			player_speed;
	t_vector2	pp;

	data = data_hook(NULL);
	tile_size = data->settings.tile_size;
	player_speed = data->settings.player_speed;
	map = data->maps;
	pp = data->player.position;
	if (map[(int)(pp.y) / tile_size][(int)(pp.x +
(axis.x * 10)) / tile_size] != '1')
	{
		*mv_x = true;
		data->player.position.x += axis.x * player_speed;
	}
	if (map[(int)(pp.y + (axis.y * 10)) / tile_size][
(int)(pp.x) / tile_size] != '1')
	{
		*mv_y = true;
		data->player.position.y += axis.y * player_speed;
	}
}

void	try_move(t_data	*data, t_vector2 axis)
{
	char		**map;
	t_vector2	pp;
	int			tile_size;
	int			player_speed;
	int			cam_sens;
	bool		mv_x;
	bool		mv_y;

	pp = data->player.position;
	map = data->maps;
	mv_x = false;
	mv_y = false;
	tile_size = data->settings.tile_size;
	cam_sens = data->settings.camera_sensibility;
	player_speed = data->settings.camera_sensibility;
	mooove(&mv_x, &mv_y, axis);
	sliding_against_wall(mv_x, mv_y, axis);
	if (map[(int)(pp.y + (axis.y * 5)) / cam_sens][
(int)(pp.x + (axis.x * 5)) / cam_sens] == '1')
	{
		data->player.position.x -= axis.x * player_speed;
		data->player.position.y -= axis.y * player_speed;
	}
}

t_vector2	read_keys_axis(t_keys_status key_pressed, float radi)
{
	t_vector2	axis;

	axis = (t_vector2){0, 0};
	if (key_pressed.w == true)
	{
		axis.x += cos(radi);
		axis.y += sin(radi);
	}
	if (key_pressed.s == true)
	{
		axis.x -= cos(radi);
		axis.y -= sin(radi);
	}
	if (key_pressed.d == true)
	{
		axis.x -= sin(radi);
		axis.y += cos(radi);
	}
	if (key_pressed.a == true)
	{
		axis.x += sin(radi);
		axis.y -= cos(radi);
	}
	return (axis);
}

void	handle_input(t_data *data, float radi)
{
	char		**maps;
	t_vector2	axis;
	int			cam_sens;

	maps = data->maps;
	cam_sens = data->settings.camera_sensibility;
	axis = read_keys_axis(data->key_pressed, radi);
	data->player.walking_dir = axis;
	try_move(data, axis);
	data->player.angle -= (data->key_pressed.left == true) * cam_sens;
	data->player.angle += (data->key_pressed.right == true) * cam_sens;
	if (data->player.angle > 360)
		data->player.angle -= 360;
	if (data->player.angle < 0)
		data->player.angle += 360;
}
