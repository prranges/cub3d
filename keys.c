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

int	key_press(int key, t_data *g)
{
	if (key == ESC)
		exit(0);
	else if (key == UP)
		g->key_up = 1;
	else if (key == LEFT)
		g->key_left = 1;
	else if (key == DOWN)
		g->key_down = 1;
	else if (key == RIGHT)
		g->key_right = 1;
	else if (key == OPEN)
		g->key_open = 1;
	return (0);
}

int	key_release(int key, t_data *g)
{
	if (key == ESC)
		exit(0);
	else if (key == UP)
		g->key_up = 0;
	else if (key == LEFT)
		g->key_left = 0;
	else if (key == DOWN)
		g->key_down = 0;
	else if (key == RIGHT)
		g->key_right = 0;
	return (0);
}

void	player_rotate_right(t_data *g)
{
	double	old_dir_x;
	double	old_plane_x;
	//both camera direction and camera plane must be rotated
	old_dir_x = g->p_dir_x;
	g->p_dir_x = g->p_dir_x * cos(-g->rot_speed) - \
		g->p_dir_y * sin(-g->rot_speed);
	g->p_dir_y = old_dir_x * sin(-g->rot_speed) + \
		g->p_dir_y * cos(-g->rot_speed);
	old_plane_x = g->cam_plane_x;
	g->cam_plane_x = g->cam_plane_x * cos(-g->rot_speed) - \
		g->cam_plane_y * sin(-g->rot_speed);
	g->cam_plane_y = old_plane_x * sin(-g->rot_speed) + \
		g->cam_plane_y * cos(-g->rot_speed);
}

void	player_rotate_left(t_data *g)
{
	double	old_dir_x;
	double	old_plane_x;
	//both camera direction and camera plane must be rotated
	old_dir_x = g->p_dir_x;
	g->p_dir_x = g->p_dir_x * cos(g->rot_speed) - \
		g->p_dir_y * sin(g->rot_speed);
	g->p_dir_y = old_dir_x * sin(g->rot_speed) + \
		g->p_dir_y * cos(g->rot_speed);
	old_plane_x = g->cam_plane_x;
	g->cam_plane_x = g->cam_plane_x * cos(g->rot_speed) - \
		g->cam_plane_y * sin(g->rot_speed);
	g->cam_plane_y = old_plane_x * sin(g->rot_speed) + \
		g->cam_plane_y * cos(g->rot_speed);
}

void	key_update(t_data *g)
{
	if (g->key_up)
	{
		if (map_array[(int)(g->p_pos_x + g->p_dir_x * \
				g->move_speed)][(int)(g->p_pos_y)] < 1)
			g->p_pos_x += g->p_dir_x * g->move_speed;
		if (map_array[(int)(g->p_pos_x)][(int)(g->p_pos_y + \
				g->p_dir_y * g->move_speed)] < 1)
			g->p_pos_y += g->p_dir_y * g->move_speed;
	}
	//move backwards if no wall behind you
	if (g->key_down)
	{
		if (map_array[(int)(g->p_pos_x - g->p_dir_x * \
				g->move_speed)][(int)(g->p_pos_y)] < 1)
			g->p_pos_x -= g->p_dir_x * g->move_speed;
		if (map_array[(int)(g->p_pos_x)][(int)(g->p_pos_y - \
				g->p_dir_y * g->move_speed)] < 1)
			g->p_pos_y -= g->p_dir_y * g->move_speed;
	}
	if (g->key_right)
		player_rotate_right(g);
	if (g->key_left)
		player_rotate_left(g);
	if (g->key_esc)
		exit(0);
}
