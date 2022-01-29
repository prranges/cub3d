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

void ft_map_lines_check(char **lines, int i, t_data *g)
{
	int j;
	int position_flag;
	
	j = 0;
	position_flag = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] != '1' && lines[i][j] != '0' && lines[i][j] != 'N' && lines[i][j] != 'S' && lines[i][j] != 'W' && lines[i][j] != 'E' && lines[i][j] != ' ')
			{
				printf("Error: Map use invalid symbol! %c", lines[i][j]);
				exit (1);
			}
			if ((lines[i][j] == 'N' || lines[i][j] == 'S' || lines[i][j] == 'W' || lines[i][j] == 'E') && position_flag < 1)
			{
				position_flag++;
				g->map.plaer_orient = lines[i][j];
			}
			else if ((lines[i][j] == 'N' || lines[i][j] == 'S' || lines[i][j] == 'W' || lines[i][j] == 'E') && position_flag == 1)
			{
				printf("Error: Double position! %c\n", lines[i][j]);
				exit (1);
			}
			j++;
		}
		if ((int)ft_strlen(lines[i]) > g->map.map_size_l)
			g->map.map_size_l = (int)ft_strlen(lines[i]);
		if (ft_strcmp (lines[i], ""))
			g->map.map_size_h++;
		else
			ft_error("Error: Map is invalid new lines!");
		i++;

	}    
}