/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:08:45 by prranges          #+#    #+#             */
/*   Updated: 2022/01/24 10:08:47 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	perform_dda(t_data *g, t_wall *w)
{
	w->hit = 0; //был ли удар о стену?
	while (w->hit == 0)
	{
		//переход к следующему квадрату карты,
		//ИЛИ в направлении x, ИЛИ в направлении y
		if (w->side_dist_x < w->side_dist_y)
		{
			w->side_dist_x += w->delta_dist_x;
			w->map_x += w->step_x;
			w->side = 0;
		}
		else
		{
			w->side_dist_y += w->delta_dist_y;
			w->map_y += w->step_y;
			w->side = 1;
		}
		//Проверьте, ударился ли луч о стену
		if (g->map.map_pars[w->map_x][w->map_y] == '1')
		{
//			printf("6\n");
			w->hit = 1;
		}
		if (g->map.map_pars[w->map_x][w->map_y] == '2' && BONUS)
			w->hit = 2;
	}
}

void	calc_step_and_side_dist(t_data *g, t_wall *w)
{
	if (w->ray_dir_x < 0)
	{
		w->step_x = -1;
		w->side_dist_x = (g->p_pos_x - w->map_x) * w->delta_dist_x;
	}
	else
	{
		w->step_x = 1;
		w->side_dist_x = (w->map_x + 1.0 - g->p_pos_x) * w->delta_dist_x;
	}
	if (w->ray_dir_y < 0)
	{
		w->step_y = -1;
		w->side_dist_y = (g->p_pos_y - w->map_y) * w->delta_dist_y;
	}
	else
	{
		w->step_y = 1;
		w->side_dist_y = (w->map_y + 1.0 - g->p_pos_y) * w->delta_dist_y;
	}
}

void	check_position(t_data *g, t_wall *w)
{
	//рассчитать положение и направление луча
	w->camera_x = 2 * w->x / (double)WIN_W - 1; //x в пространстве камеры
	w->ray_dir_x = g->p_dir_x + g->cam_plane_x * w->camera_x;
	w->ray_dir_y = g->p_dir_y + g->cam_plane_y * w->camera_x;
	//в какой части карты мы находимся
	w->map_x = (int)g->p_pos_x;
	w->map_y = (int)g->p_pos_y;
	//длина луча от одной стороны x или y до следующей стороны x или y
	w->delta_dist_x = fabs(1 / w->ray_dir_x); //fabs - модуль
	w->delta_dist_y = fabs(1 / w->ray_dir_y);
}

void	calc_size_of_wall_x(t_data *g, t_wall *w)
{
	//Вычислите расстояние перпендикулярного луча
	//(евклидово расстояние даст эффект рыбьего глаза!).
	if (w->side == 0)
		w->perp_wall_dist = (w->map_x - g->p_pos_x + \
			(1 - w->step_x) / 2) / w->ray_dir_x;
	else
		w->perp_wall_dist = (w->map_y - g->p_pos_y + \
			(1 - w->step_y) / 2) / w->ray_dir_y;
	//Вычислить WIN_H линии для рисования на экране
	w->line_height = (int)(WIN_H / w->perp_wall_dist);
	//вычислить самый низкий и самый высокий пиксель
	//для заполнения в текущей полосе
	w->draw_start = -w->line_height / 2 + WIN_H / 2;
	if (w->draw_start < 0)
		w->draw_start = 0;
	w->draw_end = w->line_height / 2 + WIN_H / 2;
	if (w->draw_end >= WIN_H)
		w->draw_end = WIN_H - 1;
}

void	wall_casting(t_data *g)
{
	t_wall	w;

	w.x = 0;
	while (w.x < WIN_W)
	{
		check_position(g, &w);
		//в каком направлении делать шаг в x или y-направлении
		//(либо +1, либо -1)
		//вычислите шаг и начальное боковое расстояние
		calc_step_and_side_dist(g, &w);
		//выполнять DDA. Это цикл, каждый раз увеличивающий луч на 1 квадрат,
		//пока не будет достигнута стена
		perform_dda(g, &w);
		// рассчитываем какой столбец текс туры и какого размера будем рисовать
		calc_size_of_wall_x(g, &w);
		// выбираем текстуру и находим нужный пиксель
		choose_pixel(g, &w);
		// цикл в котором
		pixels_to_screen_buf(g, &w);
		w.x++;
	}
}
