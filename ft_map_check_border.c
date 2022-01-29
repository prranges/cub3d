/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_border.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 10:51:49 by mbalman           #+#    #+#             */
/*   Updated: 2022/01/29 10:52:04 by mbalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_check_border_map_l(char **map, t_data *g)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < g->map.map_size_h)
	{
		j = -1;
		while(map[i][++j] == ' ')
			;
		if (map[i][j] != '1')
		{
			printf("Error1 '%c' %d %d", map[i][j], i, j);
			exit (1); 
		}
		j = g->map.map_size_l;
		while(map[i][--j] == ' ')
			;
		if (map[i][j] != '1')
		{
			printf("Error2 '%c' %d %d", map[i][j], i, j);
			exit (1);
		}       
		i++;
	}
}

void    ft_check_border_map_h(char **map, t_data *g)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < g->map.map_size_l)
	{
		j = -1;
		while(map[++j][i] == ' ')
			;
		if (map[j][i] != '1')
		{
			printf("Error3 '%c' %d %d", map[j][i], j, i);
			exit (1); 
		}
		j = g->map.map_size_h;
		while(map[--j][i] == ' ')
			;
		if (map[j][i] != '1')
		{
			printf("Error4 '%c' %d %d", map[j][i], j, i);
			exit (1);
		}       
		i++;
	}
}