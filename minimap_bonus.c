/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:27:48 by prranges          #+#    #+#             */
/*   Updated: 2022/01/27 16:27:52 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_square(t_data *g, int x, int y, int color)
{
	int	xx;
	int	yy;
	int	xxx;

	yy = 0;
	xxx = x;
	while (yy < MINIMAP)
	{
		xx = 0;
		x = xxx;
		while (xx < MINIMAP)
		{
			g->img.data[y * WIN_W + x] = color;
			xx++;
			x++;
		}
		yy++;
		y++;
	}
}

void	draw_minimap(t_data *g, t_minimap *m)
{
	if (map_array[m->y][m->x] == 0)
		put_square(g, m->xx, m->yy, 13158600);
	if (map_array[m->y][m->x] == 1)
		put_square(g, m->xx, m->yy, 200);
	if (map_array[m->y][m->x] == 2 || map_array[m->y][m->x] == -1)
		put_square(g, m->xx, m->yy, 6605050);
	put_square(g, (int)g->p_pos_y * MINIMAP, \
		(int)g->p_pos_x * MINIMAP, 16711680);
}

void	minimap(t_data *g)
{
	t_minimap	m;

	m.y = 0;
	m.yy = 0;
	while (m.y < MAP_H)
	{
		m.x = 0;
		m.xx = 0;
		while (m.x < MAP_W)
		{
			draw_minimap(g, &m);
			m.xx += MINIMAP;
			m.x++;
		}
		m.yy += MINIMAP;
		m.y++;
	}
}
