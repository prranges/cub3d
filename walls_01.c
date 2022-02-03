/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:08:45 by prranges          #+#    #+#             */
/*   Updated: 2022/02/03 16:59:22 by mbalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	perform_dda(t_data *g, t_wall *w)
{
	w->hit = 0;
	while (w->hit == 0)
	{
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
		if (g->map.map_pars[w->map_x][w->map_y] == '1')
			w->hit = 1;
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
	w->camera_x = 2 * w->x / (double)WIN_W - 1;
	w->ray_dir_x = g->p_dir_x + g->cam_plane_x * w->camera_x;
	w->ray_dir_y = g->p_dir_y + g->cam_plane_y * w->camera_x;
	w->map_x = (int)g->p_pos_x;
	w->map_y = (int)g->p_pos_y;
	w->delta_dist_x = fabs(1 / w->ray_dir_x);
	w->delta_dist_y = fabs(1 / w->ray_dir_y);
}

void	calc_size_of_wall_x(t_data *g, t_wall *w)
{
	if (w->side == 0)
		w->perp_wall_dist = (w->map_x - g->p_pos_x + \
			(1 - w->step_x) / 2) / w->ray_dir_x;
	else
		w->perp_wall_dist = (w->map_y - g->p_pos_y + \
			(1 - w->step_y) / 2) / w->ray_dir_y;
	w->line_height = (int)(WIN_H / w->perp_wall_dist);
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
		calc_step_and_side_dist(g, &w);
		perform_dda(g, &w);
		calc_size_of_wall_x(g, &w);
		choose_pixel(g, &w);
		pixels_to_screen_buf(g, &w);
		w.x++;
	}
}
