/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 12:32:18 by prranges          #+#    #+#             */
/*   Updated: 2022/01/23 12:32:20 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int key, t_data *data)
{
	if (key == ESC)
		exit(0);
	else if (key == UP)
		data->key_up = 1;
	else if (key == LEFT)
		data->key_left = 1;
	else if (key == DOWN)
		data->key_down = 1;
	else if (key == RIGHT)
		data->key_right = 1;
	return (0);
}

int		key_release(int key, t_data *data)
{
	if (key == ESC)
		exit(0);
	else if (key == UP)
		data->key_up = 0;
	else if (key == LEFT)
		data->key_left = 0;
	else if (key == DOWN)
		data->key_down = 0;
	else if (key == RIGHT)
		data->key_right = 0;
	return (0);
}

void	key_update(t_data *data)
{
	if (data->key_up)
	{
		if (!map_array[(int)(data->player_pos_x + data->player_dir_x * data->move_speed)][(int)(data->player_pos_y)])
			data->player_pos_x += data->player_dir_x * data->move_speed;
		if (!map_array[(int)(data->player_pos_x)][(int)(data->player_pos_y + data->player_dir_y * data->move_speed)])
			data->player_pos_y += data->player_dir_y * data->move_speed;
	}
	//move backwards if no wall behind you
	if (data->key_down)
	{
		if (!map_array[(int)(data->player_pos_x - data->player_dir_x * data->move_speed)][(int)(data->player_pos_y)])
			data->player_pos_x -= data->player_dir_x * data->move_speed;
		if (!map_array[(int)(data->player_pos_x)][(int)(data->player_pos_y - data->player_dir_y * data->move_speed)])
			data->player_pos_y -= data->player_dir_y * data->move_speed;
	}
	//rotate to the right
	if (data->key_right)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = data->player_dir_x;
		data->player_dir_x = data->player_dir_x * cos(-data->rot_speed) - data->player_dir_y * sin(-data->rot_speed);
		data->player_dir_y = oldDirX * sin(-data->rot_speed) + data->player_dir_y * cos(-data->rot_speed);
		double oldPlaneX = data->cam_plane_x;
		data->cam_plane_x = data->cam_plane_x * cos(-data->rot_speed) - data->cam_plane_y * sin(-data->rot_speed);
		data->cam_plane_y = oldPlaneX * sin(-data->rot_speed) + data->cam_plane_y * cos(-data->rot_speed);
	}
	//rotate to the left
	if (data->key_left)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = data->player_dir_x;
		data->player_dir_x = data->player_dir_x * cos(data->rot_speed) - data->player_dir_y * sin(data->rot_speed);
		data->player_dir_y = oldDirX * sin(data->rot_speed) + data->player_dir_y * cos(data->rot_speed);
		double oldPlaneX = data->cam_plane_x;
		data->cam_plane_x = data->cam_plane_x * cos(data->rot_speed) - data->cam_plane_y * sin(data->rot_speed);
		data->cam_plane_y = oldPlaneX * sin(data->rot_speed) + data->cam_plane_y * cos(data->rot_speed);
	}
	if (data->key_esc)
		exit(0);
}
