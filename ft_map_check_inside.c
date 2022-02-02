/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check_inside.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <prranges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 10:55:21 by mbalman           #+#    #+#             */
/*   Updated: 2022/02/02 09:34:40 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_map_error_symbol(char error, char symbol, int i, int j)
{
	char	*error_msg;

	if (error == 'h')
		error_msg = "Map horizontal contour is unclosed";
	if (error == 'v')
		error_msg = "Map vertical contour is unclosed";
	printf("Error: %s '%c' h - %d, w - %d\n", error_msg, symbol, i, j);
	exit (1);
}

void	ft_check_map_inside_l(char **map, t_data *g)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < g->map.size_h)
	{
		j = 0;
		while (j < g->map.size_l - 1)
		{
			while (j < g->map.size_l - 1 && map[i][j] != ' ')
				j++;
			if (j > 0 && j < g->map.size_l - 1 && map[i][j - 1] != '1')
				ft_map_error_symbol('h', map[i][j], i, j);
			while (j < g->map.size_l - 1 && map[i][j] == ' ')
				j++;
			if (j < g->map.size_l - 1 && map[i][j] != '1')
				ft_map_error_symbol('h', map[i][j], i, j);
		}
		i++;
	}
}

void	ft_check_map_inside_h(char **map, t_data *g)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < g->map.size_l)
	{
		j = 0;
		while (j < g->map.size_h - 1)
		{
			while (j < g->map.size_h - 1 && map[j][i] != ' ')
				j++;
			if (j > 0 && j < g->map.size_h - 1 && map[j - 1][i] != '1')
				ft_map_error_symbol('v', map[j][i], j, i);
			while (j < g->map.size_h - 1 && map[j][i] == ' ')
				j++;
			if (j < g->map.size_h - 1 && map[j][i] != '1')
				ft_map_error_symbol('v', map[j][i], j, i);
		}
		i++;
	}
}
