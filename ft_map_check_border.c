/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check_border.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 10:51:49 by mbalman           #+#    #+#             */
/*   Updated: 2022/01/29 18:58:14 by mbalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_border_map_l(char **map, t_data *g)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < g->map.size_h)
	{
		j = -1;
		while (map[i][++j] == ' ')
			;
		if (map[i][j] != '1')
			ft_map_error("Map contains unclosed contour", map[i][j]);
		j = g->map.size_l;
		while (map[i][--j] == ' ')
			;
		if (map[i][j] != '1')
			ft_map_error("Map contains unclosed contour", map[i][j]);
		i++;
	}
}

void	ft_check_border_map_h(char **map, t_data *g)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < g->map.size_l)
	{
		j = -1;
		while (map[++j][i] == ' ')
			;
		if (map[j][i] != '1')
			ft_map_error("Map contains unclosed contour", map[j][i]);
		j = g->map.size_h;
		while (map[--j][i] == ' ')
			;
		if (map[j][i] != '1')
			ft_map_error("Map contains unclosed contour", map[j][i]);
		i++;
	}
}
