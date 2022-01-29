/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 10:31:45 by prranges          #+#    #+#             */
/*   Updated: 2022/01/29 10:31:47 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move_up(t_data *g)
{
	if (g->map.map_pars[(int)(g->p_pos_x + g->p_dir_x * \
			g->move_speed)][(int)(g->p_pos_y)] == '0')
		g->p_pos_x += g->p_dir_x * g->move_speed;
	if (g->map.map_pars[(int)(g->p_pos_x)][(int)(g->p_pos_y + \
			g->p_dir_y * g->move_speed)] == '0')
		g->p_pos_y += g->p_dir_y * g->move_speed;
}

void	player_move_down(t_data *g)
{
	if (g->map.map_pars[(int)(g->p_pos_x - g->p_dir_x * \
			g->move_speed)][(int)(g->p_pos_y)] == '0')
		g->p_pos_x -= g->p_dir_x * g->move_speed;
	if (g->map.map_pars[(int)(g->p_pos_x)][(int)(g->p_pos_y - \
			g->p_dir_y * g->move_speed)] == '0')
		g->p_pos_y -= g->p_dir_y * g->move_speed;
}

void	player_move_up_bonus(t_data *g)
{
	if (g->map.map_pars[(int)(g->p_pos_x + g->p_dir_x * \
			g->move_speed)][(int)(g->p_pos_y)] == '0'
		|| g->map.map_pars[(int)(g->p_pos_x + g->p_dir_x * \
			g->move_speed)][(int)(g->p_pos_y)] == '3')
		g->p_pos_x += g->p_dir_x * g->move_speed;
	if (g->map.map_pars[(int)(g->p_pos_x)][(int)(g->p_pos_y + \
			g->p_dir_y * g->move_speed)] == '0'
		|| g->map.map_pars[(int)(g->p_pos_x)][(int)(g->p_pos_y + \
			g->p_dir_y * g->move_speed)] == '3')
		g->p_pos_y += g->p_dir_y * g->move_speed;
}

void	player_move_down_bonus(t_data *g)
{
	if (g->map.map_pars[(int)(g->p_pos_x - g->p_dir_x * \
			g->move_speed)][(int)(g->p_pos_y)] == '0'
		|| g->map.map_pars[(int)(g->p_pos_x - g->p_dir_x * \
			g->move_speed)][(int)(g->p_pos_y)] == '3')
		g->p_pos_x -= g->p_dir_x * g->move_speed;
	if (g->map.map_pars[(int)(g->p_pos_x)][(int)(g->p_pos_y - \
			g->p_dir_y * g->move_speed)] == '0'
		|| g->map.map_pars[(int)(g->p_pos_x)][(int)(g->p_pos_y - \
			g->p_dir_y * g->move_speed)] == '3')
		g->p_pos_y -= g->p_dir_y * g->move_speed;
}
