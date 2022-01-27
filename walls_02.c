/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:09:34 by prranges          #+#    #+#             */
/*   Updated: 2022/01/24 10:09:57 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	choose_txtr(t_wall *w)
{
	if (w->hit == 2)
		w->txtr_num = 8;
	else if (w->side == 1 && w->ray_dir_y < 0)
		w->txtr_num = 6;
	else if (w->side == 1 && w->ray_dir_y >= 0)
		w->txtr_num = 1;
	else if (w->side == 0 && w->ray_dir_x < 0)
		w->txtr_num = 4;
	else if (w->side == 0 && w->ray_dir_x >= 0)
		w->txtr_num = 3;
}

void	choose_pixel(t_data *g, t_wall *w)
{
	choose_txtr(w);
	//вычисляем значение wall_x
	if (w->side == 0)
		w->wall_x = g->p_pos_y + w->perp_wall_dist * w->ray_dir_y;
	else
		w->wall_x = g->p_pos_x + w->perp_wall_dist * w->ray_dir_x;
	w->wall_x -= floor((w->wall_x));
	//координата x на текстуре
	w->txtr_x = (int)(w->wall_x * (double)TXTR_W);
	if (w->side == 0 && w->ray_dir_x > 0)
		w->txtr_x = TXTR_W - w->txtr_x - 1;
	if (w->side == 1 && w->ray_dir_y < 0)
		w->txtr_x = TXTR_W - w->txtr_x - 1;
	// На сколько нужно увеличить координату текстуры на пиксель экрана
	w->step = 1.0 * TXTR_H / w->line_height;
	// Начальная координата текстуры
	w->txtr_pos = (w->draw_start - WIN_H / 2 + w->line_height / 2) * w->step;
	w->y = w->draw_start;
}

void	pixels_to_screen_buf(t_data *g, t_wall *w)
{
	while (w->y < w->draw_end)
	{
		// Приведите координату текстуры к целому числу
		//и замаскируйте (TXTR_H - 1) в случае переполнения
		w->txtr_y = (int)w->txtr_pos & (TXTR_H - 1);
		w->txtr_pos += w->step;
		w->color = g->txtrs[w->txtr_num][TXTR_H * w->txtr_y + w->txtr_x];
		//делаем цвет темнее для y-стороны: R, G и B байт,
		//каждый из которых делится на два с помощью "shift" и "and".
		if (w->side == 1)
			w->color = (w->color >> 1) & 8355711;
		g->screen_buf[w->y][w->x] = w->color;
		w->y++;
	}
}
