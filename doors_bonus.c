/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:21:30 by prranges          #+#    #+#             */
/*   Updated: 2022/01/27 16:23:41 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	door_close(int x, int y)
{
	int	xx;
	int	yy;

	xx = x;
	yy = y;
	map_array[xx][yy] = 2;
}

void	door_open(int x, int y)
{
	int	xx;
	int	yy;

	xx = x;
	yy = y;
	map_array[xx][yy] = -1;
}

void	door(t_data *g)
{
	int	x;
	int	y;

	x = (int)g->p_pos_x;
	y = (int)g->p_pos_y;
	if (map_array[x][y - 1] == 2 && g->key_open)
		door_open(x, y - 1);
	else if (map_array[x][y + 1] == 2 && g->key_open)
		door_open(x, y + 1);
	else if (map_array[x + 1][y] == 2 && g->key_open)
		door_open(x + 1, y);
	else if (map_array[x - 1][y] == 2 && g->key_open)
		door_open(x - 1, y);
	else if (map_array[x][y - 1] == -1 && g->key_open)
		door_close(x, y - 1);
	else if (map_array[x][y + 1] == -1 && g->key_open)
		door_close(x, y + 1);
	else if (map_array[x + 1][y] == -1 && g->key_open)
		door_close(x + 1, y);
	else if (map_array[x - 1][y] == -1 && g->key_open)
		door_close(x - 1, y);
	g->key_open = 0;
}
