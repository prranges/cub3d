/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_inside.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 10:55:21 by mbalman           #+#    #+#             */
/*   Updated: 2022/01/29 10:55:42 by mbalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_check_map_inside_l(char **map, t_data *g) // горизонтальна проверка внутренностей карты
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < g->map.map_size_h)
	{        
	   
		while ((map[i][j] != '0' &&  map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E') && j < g->map.map_size_l - 1)
			j++;
		if (j == g->map.map_size_l - 1)
		{
			i++;
			j = 0;
			continue;
		}
		while ((map[i][j] == '0' ||  map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E') && j < g->map.map_size_l - 1)
			j++;
		if (map[i][j] == '1' && j < g->map.map_size_l - 1)
		{
			j++;
			continue;            
		}
		else if (map[i][j] != '1')
		{
			printf("Error5 '%c' %d %d", map[i][j], i, j);
			exit (1);
		}
		j = 0;
		i++;
	}
}

void    ft_check_map_inside_h(char **map, t_data *g) // вертикальная проверка внутренностей карты
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < g->map.map_size_l)
	{	   
		while ((map[j][i] != '0' &&  map[j][i] != 'N' && map[j][i] != 'S' && map[j][i] != 'W' && map[j][i] != 'E') && j < g->map.map_size_h-1)
			j++;
		if (j == g->map.map_size_h - 1)
		{
			i++;
			j = 0;
			continue;
		}
		while ((map[j][i] == '0' ||  map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'W' || map[j][i] == 'E') && j < g->map.map_size_h-1)
			j++;
		if (map[j][i] == '1' && j < g->map.map_size_h - 1)
		{
			j++;
			continue;            
		}
		else if (map[j][i] != '1')
		{
			printf("Error6 '%c' %d %d", map[j][i], j, i);
			exit (1);
		}
		j = 0;
		i++;
	}
}