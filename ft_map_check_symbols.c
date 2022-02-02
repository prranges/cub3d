/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check_symbols.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <prranges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 11:57:34 by mbalman           #+#    #+#             */
/*   Updated: 2022/02/02 10:29:12 by prranges         ###   ########.fr       */
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

void	ft_save_map_size(t_data *g, char *line)
{
	if ((int)ft_strlen(line) > g->map.size_l)
		g->map.size_l = (int)ft_strlen(line);
	if (ft_strcmp (line, ""))
		g->map.size_h++;
	else
		ft_error("Error: Map contains new lines!");
}

void	ft_map_lines_check(char **lines, int i, t_data *g)
{
	int	j;
	int	k;

	j = 0;
	k = i;
	g->position_flag = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			ft_map_symbol_check(g, lines[i][j], &g->position_flag);
			if (lines[i][j] == 'N' || lines[i][j] == 'S'
			|| lines[i][j] == 'W' || lines[i][j] == 'E')
			{
				ft_save_player_position(g, lines[i][j], i - k, j);
				lines[i][j] = '0';
			}
			j++;
		}
		ft_save_map_size(g, lines[i]);
		i++;
	}
	if (!g->position_flag)
		ft_error("Error: Map doesn't contain player position!");
}
