/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:34:28 by mbalman           #+#    #+#             */
/*   Updated: 2022/01/29 19:41:03 by mbalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_param(t_data *g, char ***map)
{
	char	**lines;
	char	**line_split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	lines = *map;
	while (lines[i])
	{
		line_split = ft_split(lines[i], ' ');
		if (!line_split[0])
		{
			i++;
			continue ;
		}
		if (!ft_strncmp(line_split[0], "NO", ft_strlen(line_split[0])))
			ft_save_param(line_split[1], &g->map.path_north_texture, g);
		else if (!ft_strncmp(line_split[0], "SO", ft_strlen(line_split[0])))
			ft_save_param(line_split[1], &g->map.path_south_texture, g);
		else if (!ft_strncmp(line_split[0], "WE", ft_strlen(line_split[0])))
			ft_save_param(line_split[1], &g->map.path_west_texture, g);
		else if (!ft_strncmp(line_split[0], "EA", ft_strlen(line_split[0])))
			ft_save_param(line_split[1], &g->map.path_east_texture, g);
		else if (!ft_strncmp(line_split[0], "C", ft_strlen(line_split[0])))
			ft_save_color(line_split, &g->map.celing, g);
		else if (!ft_strncmp(line_split[0], "F", ft_strlen(line_split[0])))
			ft_save_color(line_split, &g->map.floor, g);
		else if (lines[i][0] == '\n')
		{
			i++;
			continue ;
		}
		else
		{
			if (g->map.param_count != 6)
				ft_error("Error: Malo parametrov");
			break ;
		}
		i++;
	}
	ft_map_lines_check(lines, i, g);
	printf("__________________________________________\n");
	ft_map_record(lines, i, g);
}

void	ft_pars_params(char **argv, t_data *g)
{
	int		i;
	char	**map;

	i = 0;
	map = NULL;
	ft_load_map(argv, &map);
	printf("\n \n ALL MAPA\n");
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	ft_check_param(g, &map);
}
