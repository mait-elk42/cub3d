/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:06:57 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/15 13:09:18 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	is_collided_wall(t_data	*data, t_vector2 axis)
{
	bool		mv_x;
	bool		mv_y;
	char		**map;
	t_vector2	g_player;

	g_player = data->player.position;
	map = data->maps;
	bool	is_collided_wall(t_data	*data, t_vector2 axis);
	draw_line(&data->minimaps_layer, 0x00ff00, data->player.position, (t_vector2){data->player.position.x + (axis.x * 20), data->player.position.y + (axis.y * 20)});
	if (map[(int)(g_player.y) / TILE_SIZE][(int)(g_player.x + (axis.x * 5)) / TILE_SIZE] != '1')
	mv_x = false;
	mv_y = false;
	if (map[(int)(g_player.y) / TILE_SIZE][(int)(g_player.x + (axis.x * 10)) / TILE_SIZE] != '1')
	{
		mv_x = true;
		data->player.position.x += axis.x * PLAYER_SPEED;
	}
	if (map[(int)(g_player.y + (axis.y * 10)) / TILE_SIZE][(int)(g_player.x) / TILE_SIZE] != '1')
	{
		mv_y = true;
		data->player.position.y += axis.y * PLAYER_SPEED;
	}
	if (mv_y != mv_x)
	{
		if (mv_x == true)
		{
			if (map[(int)(g_player.y) / TILE_SIZE][(int)(g_player.x + 10) / TILE_SIZE] == '1')
				data->player.position.x -= axis.x * PLAYER_SPEED;
			if (map[(int)(g_player.y) / TILE_SIZE][(int)(g_player.x - 10) / TILE_SIZE] == '1')
				data->player.position.x -= axis.x * PLAYER_SPEED;
		}
		if (mv_y == true)
		{
			if (map[(int)(g_player.y + 10) / TILE_SIZE][(int)(g_player.x) / TILE_SIZE] == '1')
				data->player.position.y -= axis.y * PLAYER_SPEED;
			if (map[(int)(g_player.y - 10) / TILE_SIZE][(int)(g_player.x) / TILE_SIZE] == '1')
				data->player.position.y -= axis.y * PLAYER_SPEED;
		}
	}
	if (map[(int)(g_player.y + (axis.y * 5)) / TILE_SIZE][(int)(g_player.x + (axis.x * 5)) / TILE_SIZE] == '1')
	{
		data->player.position.x -= axis.x * PLAYER_SPEED;
		data->player.position.y -= axis.y * PLAYER_SPEED;
	}
	return (false);
}

void	handle_input(t_data *data, float radi)
{
	char		**maps;
	t_vector2	axis;
	bool		press = false;

	axis = (t_vector2){0,0};
	maps = data->maps;
	if (data->key_pressed.w == true)
	{
		axis.x += cos(radi);
		axis.y += sin(radi);
		press = true;
	}
	if (data->key_pressed.s == true)
	{
		axis.x -= cos(radi);
		axis.y -= sin(radi);
		press = true;
	}
	if (data->key_pressed.d == true)
	{
		axis.x -= sin(radi);
		axis.y += cos(radi);
		press = true;
	}
	if (data->key_pressed.a == true)
	{
		axis.x += sin(radi);
		axis.y -= cos(radi);
		press = true;
	}

	if (press && is_collided_wall(data, axis) == false)
	{
		// data->player.position.x += axis.x * PLAYER_SPEED;
		// data->player.position.y += axis.y * PLAYER_SPEED;
	}
	data->player.angle -= (data->key_pressed.left == true) * CAM_SENS;
	data->player.angle += (data->key_pressed.right == true) * CAM_SENS;

	if (data->player.angle > 360)
		data->player.angle -= 360;
	if (data->player.angle < 0)
		data->player.angle += 360;
}
