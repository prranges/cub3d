/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:21:30 by prranges          #+#    #+#             */
/*   Updated: 2022/01/27 16:23:41 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	door_close(t_data *g, int x, int y)
{
	int	xx;
	int	yy;

	xx = x;
	yy = y;
	g->map.map_pars[xx][yy] = '2';
}

void	door_open(t_data *g, int x, int y)
{
	int	xx;
	int	yy;

	xx = x;
	yy = y;
	g->map.map_pars[xx][yy] = '3';
}

void	door(t_data *g)
{
	int	x;
	int	y;

	x = (int)g->p_pos_x;
	y = (int)g->p_pos_y;
	if (g->map.map_pars[x][y - 1] == '2' && g->key_open)
		door_open(g, x, y - 1);
	else if (g->map.map_pars[x][y + 1] == '2' && g->key_open)
		door_open(g, x, y + 1);
	else if (g->map.map_pars[x + 1][y] == '2' && g->key_open)
		door_open(g, x + 1, y);
	else if (g->map.map_pars[x - 1][y] == '2' && g->key_open)
		door_open(g, x - 1, y);
	else if (g->map.map_pars[x][y - 1] == '3' && g->key_open)
		door_close(g, x, y - 1);
	else if (g->map.map_pars[x][y + 1] == '3' && g->key_open)
		door_close(g, x, y + 1);
	else if (g->map.map_pars[x + 1][y] == '3' && g->key_open)
		door_close(g, x + 1, y);
	else if (g->map.map_pars[x - 1][y] == '3' && g->key_open)
		door_close(g, x - 1, y);
	g->key_open = 0;
}
