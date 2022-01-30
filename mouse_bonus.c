/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:43:47 by prranges          #+#    #+#             */
/*   Updated: 2022/01/26 09:46:52 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouse_move_right(t_data *g, int diff, int x, int y)
{
	g->k.mouse_x = x;
	while (diff-- != 0)
		player_rotate_right(g);
	if (x > (int)(WIN_W * 0.7))
	{
		mlx_mouse_move(g->win, (int)(WIN_W / 2), y);
		g->k.mouse_x = (int)(WIN_W / 2);
	}
}

void	mouse_move_left(t_data *g, int diff, int x, int y)
{
	g->k.mouse_x = x;
	while (diff-- != 0)
		player_rotate_left(g);
	if (x < (int)(WIN_W * 0.3))
	{
		mlx_mouse_move(g->win, (int)(WIN_W / 2), y);
		g->k.mouse_x = (int)(WIN_W / 2);
	}
}

int	mouse_move(int x, int y, t_data *g)
{
	int	diff;

	diff = abs(g->k.mouse_x - x) / 2;
	if (diff > 3)
		diff = 3;
	if (y < (int)(WIN_H * 0.3) || y > (int)(WIN_H * 0.7))
		mlx_mouse_move(g->win, x, (int)(WIN_H / 2));
	if (x > g->k.mouse_x)
		mouse_move_right(g, diff, x, y);
	else if (x < g->k.mouse_x)
		mouse_move_left(g, diff, x, y);
	return (0);
}
