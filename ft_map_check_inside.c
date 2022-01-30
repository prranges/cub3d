/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check_inside.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 10:55:21 by mbalman           #+#    #+#             */
/*   Updated: 2022/01/29 19:50:52 by mbalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_map_error_symbol(char *error_msg, char symbol, int i, int j)
{
	printf("Error: %s '%c' h - %d, w - %d\n", error_msg, symbol, i, j);
	exit (1);
}

//void	ft_check_map_inside_l(char **map, t_data *g, int i, int j)
//{
//	i = 0;
//	j = 0;
//	while (i < g->map.size_h)
//	{
//		j = 0;
//		while (j < g->map.size_l)
//		{
//			while (j < g->map.size_l && map[i][j] != ' ')
//				j++;
//			if (j > 0 && map[i][j - 1] != '1')
//				ft_map_error_symbol("1", map[i][j], i, j);
//			while (j < g->map.size_l && map[i][j] == ' ')
//				j++;
//			if (j < g->map.size_l && map[i][j] != '1')
//				ft_map_error_symbol("2", map[i][j], i, j);
//		}
//		i++;
//	}
//}
//
//void	ft_check_map_inside_h(char **map, t_data *g, int i, int j)
//{
//	i = 0;
//	j = 0;
//	while (i < g->map.size_l)
//	{
//		j = 0;
//		while (j < g->map.size_h)
//		{
//			printf("1: j - %d, i - %d, c - %c\n", j, i, map[j][i]);
//			while (j < g->map.size_h && map[j][i] != ' ')
//				j++;
//			printf("2: j - %d, i - %d, c - %c\n", j, i, map[j][i]);
//			if (i > 0 && map[j][i - 1] != '1')
//				ft_map_error_symbol("1", map[j][i], j, i);
//			printf("3: j - %d, i - %d, c - %c\n", j, i, map[j][i]);
//			while (j < g->map.size_h && map[j][i] == ' ')
//				j++;
//			printf("4: j - %d, i - %d, c - %c\n", j, i, map[j][i]);
//			if (j < g->map.size_h && map[j][i] != '1')
//				ft_map_error_symbol("2", map[j][i], j, i);
//			printf("5: j - %d, i - %d, c - %c\n", j, i, map[j][i]);
//		}
//		i++;
//	}
//}

//void	ft_check_map_inside_l(char **map, t_data *g, int i, int j)
//{
//	i = 0;
//	j = 0;
//	while (i < g->map.size_h)
//	{
//		while ((map[i][j] != '0' && map[i][j] != 'N' && map[i][j] != 'S' && \
//			map[i][j] != 'W' && map[i][j] != 'E') && j < g->map.size_l - 1)
//			j++;
//		if (j == g->map.size_l - 1)
//		{
//			i++;
//			j = 0;
//			continue ;
//		}
//		while ((map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || \
//			map[i][j] == 'W' || map[i][j] == 'E') && j < g->map.size_l - 1)
//			j++;
//		if (map[i][j] == '1' && j < g->map.size_l - 1)
//		{
//			j++;
//			continue ;
//		}
//		else if (map[i][j] != '1')
//			ft_map_error_symbol("Map horizontal contour is unclosed", map[i][j], i, j);
//		j = 0;
//		i++;
//	}
//}
//
//void	ft_check_map_inside_h(char **map, t_data *g, int i, int j)
//{
//	i = 0;
//	j = 0;
//	while (i < g->map.size_l)
//	{
//		while ((map[j][i] != '0' && map[j][i] != 'N' && map[j][i] != 'S' && \
//			map[j][i] != 'W' && map[j][i] != 'E') && j < g->map.size_h - 1)
//			j++;
//		if (j == g->map.size_h - 1)
//		{
//			i++;
//			j = 0;
//			continue ;
//		}
//		while ((map[j][i] == '0' || map[j][i] == '2' || map[j][i] == 'N' || \
//				map[j][i] == 'S' || map[j][i] == 'W' || map[j][i] == 'E') && j < g->map.size_h - 1)
//				j++;
//		if (map[j][i] == '1' && j < g->map.size_h - 1)
//		{
//			j++;
//			continue ;
//		}
//		else if (map[j][i] != '1')
//			ft_map_error_symbol("Map vertical contour is unclosed", map[i][j], i, j);
//		j = 0;
//		i++;
//	}
//}
