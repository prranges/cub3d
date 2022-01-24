/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:08:45 by prranges          #+#    #+#             */
/*   Updated: 2022/01/24 10:08:47 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	perform_DDA(t_wall *w)
{
	w->hit = 0; //был ли удар о стену?
	
	while (w->hit == 0)
	{
		//переход к следующему квадрату карты, ИЛИ в направлении x, ИЛИ в направлении y
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
		if (map_array[w->map_x][w->map_y] > 0)
			w->hit = 1;
	}
}

void	calc_step_and_side_dist(t_data *data, t_wall *w)
{
	if (w->ray_dir_x < 0)
	{
		w->step_x = -1;
		w->side_dist_x = (data->player_pos_x - w->map_x) * w->delta_dist_x;
	}
	else
	{
		w->step_x = 1;
		w->side_dist_x = (w->map_x + 1.0 - data->player_pos_x) * w->delta_dist_x;
	}
	if (w->ray_dir_y < 0)
	{
		w->step_y = -1;
		w->side_dist_y = (data->player_pos_y - w->map_y) * w->delta_dist_y;
	}
	else
	{
		w->step_y = 1;
		w->side_dist_y = (w->map_y + 1.0 - data->player_pos_y) * w->delta_dist_y;
	}
}

void	check_position(t_data *data, t_wall *w)
{
	//рассчитать положение и направление луча
	w->camera_x = 2 * w->x / (double)WIN_W - 1; //x-координата в пространстве камеры
	w->ray_dir_x = data->player_dir_x + data->cam_plane_x * w->camera_x;
	w->ray_dir_y = data->player_dir_y + data->cam_plane_y * w->camera_x;
	//в какой части карты мы находимся
	w->map_x = (int)data->player_pos_x;
	w->map_y = (int)data->player_pos_y;
	//длина луча от одной стороны x или y до следующей стороны x или y
	w->delta_dist_x = fabs(1 / w->ray_dir_x); //fabs - модуль
	w->delta_dist_y = fabs(1 / w->ray_dir_y);
}

void	wall_casting(t_data *data)
{
	t_wall w;
		
	w.x = 0;
	while (w.x < WIN_W)
	{
		
		check_position(data, &w);
		//в каком направлении делать шаг в x или y-направлении (либо +1, либо -1)
		//вычислите шаг и начальное боковое расстояние
		calc_step_and_side_dist(data, &w);
		
		//выполнять DDA. Это цикл, каждый раз увеличивающий луч на 1 квадрат, пока не будет достигнута стена
		perform_DDA(&w);
		
		//Вычислите расстояние перпендикулярного луча (евклидово расстояние даст эффект рыбьего глаза!).
		if (w.side == 0)
			w.perp_wall_dist = (w.map_x - data->player_pos_x + (1 - w.step_x) / 2) / w.ray_dir_x;
		else
			w.perp_wall_dist = (w.map_y - data->player_pos_y + (1 - w.step_y) / 2) / w.ray_dir_y;
		//Вычислить WIN_H линии для рисования на экране
		w.line_height = (int)(WIN_H / w.perp_wall_dist);
		//вычислить самый низкий и самый высокий пиксель для заполнения в текущей полосе
		w.draw_start = -w.line_height / 2 + WIN_H / 2;
		if (w.draw_start < 0)
			w.draw_start = 0;
		w.draw_end = w.line_height / 2 + WIN_H / 2;
		if (w.draw_end >= WIN_H)
			w.draw_end = WIN_H - 1;
		
		//расчеты текстурирования
		w.txtr_num = map_array[w.map_x][w.map_y] - 1; //1 вычитается из него, чтобы можно было использовать текстуру 0!
		//вычисляем значение wall_x
		if (w.side == 0)
			w.wall_x = data->player_pos_y + w.perp_wall_dist * w.ray_dir_y;
		else
			w.wall_x = data->player_pos_x + w.perp_wall_dist * w.ray_dir_x;
		w.wall_x -= floor((w.wall_x));
		//координата x на текстуре
		w.txtr_x = (int)(w.wall_x * (double)TXTR_W);
		if (w.side == 0 && w.ray_dir_x > 0)
			w.txtr_x = TXTR_W - w.txtr_x - 1;
		if (w.side == 1 && w.ray_dir_y < 0)
			w.txtr_x = TXTR_W - w.txtr_x - 1;
		// На сколько нужно увеличить координату текстуры на пиксель экрана
		w.step = 1.0 * TXTR_H / w.line_height;
		// Начальная координата текстуры
		w.txtr_pos = (w.draw_start - WIN_H / 2 + w.line_height / 2) * w.step;
		w.y = w.draw_start;
		while (w.y < w.draw_end)
		{
			// Приведите координату текстуры к целому числу и замаскируйте (TXTR_H - 1) в случае переполнения
			w.txtr_y = (int)w.txtr_pos & (TXTR_H - 1);
			w.txtr_pos += w.step;
			w.color = data->txtrs[w.txtr_num][TXTR_H * w.txtr_y + w.txtr_x];
			//делаем цвет темнее для y-стороны: R, G и B байт, каждый из которых делится на два с помощью "shift" и "and".
			if (w.side == 1)
				w.color = (w.color >> 1) & 8355711;
			data->screen_buf[w.y][w.x] = w.color;
			w.y++;
		}
		w.x++;
	}
}
