/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check_symbols.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 11:57:34 by mbalman           #+#    #+#             */
/*   Updated: 2022/01/29 11:58:29 by mbalman          ###   ########.fr       */
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
//	(void)lines;
//	(void)j;
//	(void)i;
	printf("i - %d j - %d\n", i, j);
	g->p_pos_x = (double)i;
	g->p_pos_y = (double)j;
	printf("map[] - %c\n", direction);
	if (direction == 'N')
	{
		g->p_dir_x = -1.0;
		g->p_dir_y = 0.0;
	}
	if (direction == 'S')
	{
		g->p_dir_x = 1.0;
		g->p_dir_y = 0.0;
	}
//	if (lines[i][j] == 'W')
//	{
//		g->p_dir_x = -1;
//		g->p_dir_y = -1;
//	}
//	if (direction == 'E')
//	{
//		g->p_dir_x = 0.0;
//		g->p_dir_y = 1.0;
//	}
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
	int	j;
	int	i_save;
	int	position_flag;

	j = 0;
	i_save = i;
	position_flag = 0;
	while (lines[i])
	{
		j = -1;
		while (lines[i][++j])
		{
			ft_map_symbol_check(g, lines[i][j], &position_flag);
			if (lines[i][j] == 'N' || lines[i][j] == 'S' || lines[i][j] == 'W' || lines[i][j] == 'E')
			{
				ft_save_player_position(g, lines[i][j], i - i_save, j);
				lines[i][j] = '0';
			}
		}
		if ((int)ft_strlen(lines[i]) > g->map.map_size_l)
			g->map.map_size_l = (int)ft_strlen(lines[i]);
		if (ft_strcmp (lines[i], ""))
			g->map.map_size_h++;
		else
			ft_error("Error: Map contains new lines!");
		i++;
	}
	if (!position_flag)
		ft_error("Error: Map doesn't contain player position!");
}
