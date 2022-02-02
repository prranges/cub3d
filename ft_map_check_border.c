/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check_border.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <prranges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 10:51:49 by mbalman           #+#    #+#             */
/*   Updated: 2022/02/02 09:35:17 by prranges         ###   ########.fr       */
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
		j = 0;
		while (map[i][j] == ' ' && j < g->map.size_l - 1)
			j++;
		if (map[i][j] != '1' && j < g->map.size_l - 1)
			ft_map_error_symbol('h', map[i][j], i, j);
		j = g->map.size_l;
		while (map[i][--j] == ' ' && j > 0)
			;
		if (map[i][j] != '1' && j > 0)
			ft_map_error_symbol('h', map[i][j], i, j);
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
		j = 0;
		while (map[j][i] == ' ' && j < g->map.size_h - 1)
			j++;
		if (map[j][i] != '1' && j < g->map.size_h - 1)
			ft_map_error_symbol('v', map[j][i], j, i);
		j = g->map.size_h - 1;
		while (map[j][i] == ' ' && j > 0)
			j--;
		if (map[j][i] != '1' && j > 0)
			ft_map_error_symbol('v', map[j][i], j, i);
		i++;
	}
}
