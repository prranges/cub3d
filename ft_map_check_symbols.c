/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check_symbols.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 11:57:34 by mbalman           #+#    #+#             */
/*   Updated: 2022/01/29 19:50:16 by mbalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_map_error(char *error_msg, char error_symbol)
{
	printf("Error: %s - '%c'!\n", error_msg, error_symbol);
	exit (1);
}

void	ft_save_player_position(t_data *g, char direction, int i, int j)
{
	g->p_pos_x = (double)i + 0.5;
	g->p_pos_y = (double)j + 0.5;
	if (direction == 'S')
	{
		g->cam_plane_x = 0;
		g->cam_plane_y = -0.66;
		g->p_dir_x = 1;
		g->p_dir_y = 0;
	}
	if (direction == 'W')
	{
		g->cam_plane_x = -0.66;
		g->cam_plane_y = 0;
		g->p_dir_x = 0;
		g->p_dir_y = -1;
	}
	if (direction == 'E')
	{
		g->cam_plane_x = 0.66;
		g->cam_plane_y = 0;
		g->p_dir_x = 0;
		g->p_dir_y = 1;
	}
}

void	ft_map_symbol_check(t_data *g, char c, int *p_flag)
{
	(void)g;
	if (BONUS && (c != '1' && c != '2' && c != '0' && c != 'N'
			&& c != 'S' && c != 'W' && c != 'E' && c != ' '))
		ft_map_error("Map contains invalid symbol", c);
	if (!BONUS && (c != '1' && c != '0' && c != 'N' && c != 'S'
			&& c != 'W' && c != 'E' && c != ' '))
		ft_map_error("Map contains invalid symbol", c);
	if ((c == 'N' || c == 'S' || c == 'W' || c == 'E') && *p_flag < 1)
		(*p_flag)++;
	else if ((c == 'N' || c == 'S' || c == 'W' || c == 'E') && *p_flag == 1)
		ft_map_error("Map contains more then 1 player position", c);
}

void	ft_map_lines_check(char **lines, int i, t_data *g)
{
	g->itr.j = 0;
	g->itr.k = i;
	g->position_flag = 0;
	while (lines[i])
	{
		g->itr.j = -1;
		while (lines[i][++g->itr.j])
		{
			ft_map_symbol_check(g, lines[i][g->itr.j], &g->position_flag);
			if (lines[i][g->itr.j] == 'N' || lines[i][g->itr.j] == 'S'
				|| lines[i][g->itr.j] == 'W' || lines[i][g->itr.j] == 'E')
			{
				ft_save_player_position(g, lines[i][g->itr.j], i - g->itr.k, g->itr.j);
				lines[i][g->itr.j] = '0';
			}
		}
		if ((int)ft_strlen(lines[i]) > g->map.size_l)
			g->map.size_l = (int)ft_strlen(lines[i]);
		if (ft_strcmp (lines[i], ""))
			g->map.size_h++;
		else
			ft_error("Error: Map contains new lines!");
		i++;
	}
	if (!g->position_flag)
		ft_error("Error: Map doesn't contain player position!");
}
