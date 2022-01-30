/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check_inside_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 21:38:45 by prranges          #+#    #+#             */
/*   Updated: 2022/01/29 21:38:49 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_map_inside_l_bonus(char **map, t_data *g, int i, int j)
{
	i = 0;
	j = 0;
	while (i < g->map.size_h)
	{
		while ((map[i][j] == ' ' || map[i][j] == '1') && j < g->map.size_l - 1)
			j++;
		if (j == g->map.size_l - 1)
		{
			i++;
			j = 0;
			continue ;
		}
		while ((map[i][j] == '0' || map[i][j] == '2' || map[i][j] == 'N' || map[i][j] == 'S' || \
			map[i][j] == 'W' || map[i][j] == 'E') && j < g->map.size_l - 1)
			j++;
		if (map[i][j] == '1' && j < g->map.size_l - 1)
		{
			j++;
			continue ;
		}
		else if (map[i][j] != '1')
			ft_map_error("Map horizontal contour is unclosed", map[i][j]);
		j = 0;
		i++;
	}
}

void	ft_check_map_inside_h_bonus(char **map, t_data *g, int i, int j)
{
	i = 0;
	j = 0;
	while (i < g->map.size_l)
	{
		while ((map[j][i] == ' ' || map[j][i] == '1') && j < g->map.size_h - 1)
			j++;
		if (j == g->map.size_h - 1)
		{
			i++;
			j = 0;
			continue ;
		}
		while ((map[j][i] == '0' || map[j][i] == 'N' || map[j][i] == 'S' || \
				map[j][i] == 'W' || map[j][i] == 'E') && j < g->map.size_h - 1)
				j++;
		if (map[j][i] == '1' && j < g->map.size_h - 1)
		{
			j++;
			continue ;
		}
		else if (map[j][i] != '1')
			ft_map_error("Map vertical contour is unclosed", map[j][i]);
		j = 0;
		i++;
	}
}
