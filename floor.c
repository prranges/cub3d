/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:08:56 by prranges          #+#    #+#             */
/*   Updated: 2022/01/24 10:08:59 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	floor_casting(t_data *data)
{
	t_floor	f;

	f.y = WIN_H / 2 + 1;
	while (f.y < WIN_H)
	{
		// ray_dir для крайнего левого луча (x = 0) и крайнего правого луча (x = w)
		f.ray_dir_x_0 = data->player_dir_x - data->cam_plane_x;
		f.ray_dir_y_0 = data->player_dir_y - data->cam_plane_y;
		f.ray_dir_x_1 = data->player_dir_x + data->cam_plane_x;
		f.ray_dir_y_1 = data->player_dir_y + data->cam_plane_y;
		// Текущее положение по оси y относительно центра экрана (горизонт)
		f.p = f.y - WIN_H / 2;
		// Вертикальное положение камеры.
		f.pos_z = 0.5 * WIN_H;
		// Горизонтальное расстояние от камеры до пола для текущего ряда.
		// 0.5 - это положение z точно посередине между полом и потолком.
		f.row_distance = f.pos_z / f.p;
		// вычисляем вектор шага в реальном мире, который мы должны добавить для каждого x (параллельно плоскости камеры)
		// пошаговое сложение позволяет избежать умножения с весом во внутреннем цикле
		f.floor_step_x = f.row_distance * (f.ray_dir_x_1 - f.ray_dir_x_0) / WIN_W;
		f.floor_step_y = f.row_distance * (f.ray_dir_y_1 - f.ray_dir_y_0) / WIN_W;
		// реальные координаты крайнего левого столбца. Они будут обновляться по мере продвижения вправо.
		f.floor_x = data->player_pos_x + f.row_distance * f.ray_dir_x_0;
		f.floor_y = data->player_pos_y + f.row_distance * f.ray_dir_y_0;
		f.x = 0;
		while (f.x < WIN_W)
		{
			// координата ячейки просто получается из целочисленных частей floorX и floorY
			f.cell_x = (int)(f.floor_x);
			f.cell_y = (int)(f.floor_y);
			// получаем координату текстуры из дробной части
			f.t_x = (int)(TXTR_W * (f.floor_x - f.cell_x)) & (TXTR_W - 1);
			f.t_y = (int)(TXTR_H * (f.floor_y - f.cell_y)) & (TXTR_H - 1);
			f.floor_x += f.floor_step_x;
			f.floor_y += f.floor_step_y;
			// выбираем текстуру и рисуем пиксель
			f.checker_board_pattern = (int)(f.cell_x + f.cell_y) & 1;
			if (f.checker_board_pattern == 0)
				f.floor_texture = 3;
			else
				f.floor_texture = 4;
			f.ceiling_texture = 6;
			// пол
			f.color = data->txtrs[f.floor_texture][TXTR_W * f.t_y + f.t_x];
			f.color = (f.color >> 1) & 8355711; // make a bit darker
			data->screen_buf[f.y][f.x] = f.color;
			//потолок (симметрично, при WIN_H - y - 1 вместо y)
			f.color = data->txtrs[f.ceiling_texture][TXTR_W * f.t_y + f.t_x];
			f.color = (f.color >> 1) & 8355711; // сделать немного темнее
			data->screen_buf[WIN_H - f.y - 1][f.x] = f.color;
			f.x++;
		}
		f.y++;
	}
}
