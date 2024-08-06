/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:06:57 by mait-elk          #+#    #+#             */
/*   Updated: 2024/08/06 11:05:55 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	sliding_against_wall(bool mv_x, bool mv_y, t_vector2 axis)
{
	t_data		*data;
	t_vector2	pp;
	char		**map;

	data = data_hook(NULL);
	map = data->map;
	pp = data->player.position;
	if (mv_y != mv_x && mv_x == true)
	{
		if (map[(int)(pp.y) / TILE_SIZE][(int)(pp.x + 10) / TILE_SIZE] == '1')
			data->player.position.x -= axis.x * P_SPEED;
		if (map[(int)(pp.y) / TILE_SIZE][(int)(pp.x - 10) / TILE_SIZE] == '1')
			data->player.position.x -= axis.x * P_SPEED;
	}
	if (mv_y != mv_x && mv_y == true)
	{
		if (map[(int)(pp.y + 10) / TILE_SIZE][(int)(pp.x) / TILE_SIZE] == '1')
			data->player.position.y -= axis.y * P_SPEED;
		if (map[(int)(pp.y - 10) / TILE_SIZE][(int)(pp.x) / TILE_SIZE] == '1')
			data->player.position.y -= axis.y * P_SPEED;
	}
}

void	mooove(bool *mv_x, bool *mv_y, t_vector2 axis)
{
	t_data		*data;
	char		**map;
	t_vector2	pp;
	float		speed;

	data = data_hook(NULL);
	map = data->map;
	pp = data->player.position;
	speed = (P_SPEED + (data->key_pressed.shift * 2));
	if (map[(int)(pp.y) / TILE_SIZE][
		(int)(pp.x + (axis.x * 10)) / TILE_SIZE] != '1'
		&& map[(int)(pp.y) / TILE_SIZE][
		(int)((pp.x + (axis.x * 10))) / TILE_SIZE] != 'D')
	{
		*mv_x = true;
		data->player.position.x += axis.x * speed;
	}
	if (map[(int)(pp.y + (axis.y * 10)) / TILE_SIZE][
		(int)(pp.x) / TILE_SIZE] != '1'
		&& map[(int)(pp.y + (axis.y * 10)) / TILE_SIZE][
		(int)(pp.x / TILE_SIZE)] != 'D')
	{
		*mv_y = true;
		data->player.position.y += axis.y * speed;
	}
}

void	try_move(t_data	*data, t_vector2 axis)
{
	bool		mv_x;
	bool		mv_y;
	char		**map;
	t_vector2	pp;

	pp = data->player.position;
	map = data->map;
	mv_x = false;
	mv_y = false;
	if (pp.x / TILE_SIZE <= 0 || (pp.x / TILE_SIZE) >= (int) data->screen.width)
		return ;
	if (pp.y / TILE_SIZE <= 0 || pp.y / TILE_SIZE >= (int) data->screen.height)
		return ;
	mooove(&mv_x, &mv_y, axis);
	sliding_against_wall(mv_x, mv_y, axis);
	if (map[(int)(pp.y + (axis.y * 5)) / TILE_SIZE][
(int)(pp.x + (axis.x * 5)) / TILE_SIZE] == '1')
	{
		data->player.position.x -= axis.x * P_SPEED;
		data->player.position.y -= axis.y * P_SPEED;
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
	char		**map;
	t_vector2	axis;

	map = data->map;
	axis = read_keys_axis(data->key_pressed, radi);
	data->player.is_walking = axis.x != 0 || axis.y != 0;
	try_move(data, axis);
	data->player.angle += (data->key_pressed.right) * CAM_SENS;
	data->player.angle -= (data->key_pressed.left) * CAM_SENS;
	if (data->mouse.to_right)
		data->player.angle += data->mouse.cam_sens_h;
	if (data->mouse.to_left)
		data->player.angle -= data->mouse.cam_sens_h;
	data->up_down += data->mouse.cam_sens_v * 10 * (data->mouse.to_up);
	data->up_down += CAM_SENS * 10 * (data->key_pressed.up);
	data->up_down -= data->mouse.cam_sens_v * 10 * (data->mouse.to_down);
	data->up_down -= CAM_SENS * 10 * (data->key_pressed.down);
	irange(&data->up_down, -500, 500);
	if (data->player.angle > 360)
		data->player.angle -= 360;
	if (data->player.angle < 0)
		data->player.angle += 360;
}
