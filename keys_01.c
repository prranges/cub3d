/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 12:32:18 by prranges          #+#    #+#             */
/*   Updated: 2022/02/03 17:01:09 by mbalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_data *g)
{
	if (key == ESC)
		exit(0);
	else if (key == UP)
		g->k.key_up = 1;
	else if (key == LEFT)
		g->k.key_left = 1;
	else if (key == DOWN)
		g->k.key_down = 1;
	else if (key == RIGHT)
		g->k.key_right = 1;
	else if (key == OPEN)
		g->k.key_open = 1;
	return (0);
}

int	key_release(int key, t_data *g)
{
	if (key == ESC)
		exit(0);
	else if (key == UP)
		g->k.key_up = 0;
	else if (key == LEFT)
		g->k.key_left = 0;
	else if (key == DOWN)
		g->k.key_down = 0;
	else if (key == RIGHT)
		g->k.key_right = 0;
	return (0);
}

void	player_rotate_right(t_data *g)
{
	double	old_dir_x;
	double	old_plane_x;

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
	if (BONUS)
	{
		if (g->k.key_up)
			player_move_up_bonus(g);
		if (g->k.key_down)
			player_move_down_bonus(g);
	}
	else
	{
		if (g->k.key_up)
			player_move_up(g);
		if (g->k.key_down)
			player_move_down(g);
	}
	if (g->k.key_right)
		player_rotate_right(g);
	if (g->k.key_left)
		player_rotate_left(g);
	if (g->k.key_esc)
		exit(0);
}
