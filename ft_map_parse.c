/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:34:28 by mbalman           #+#    #+#             */
/*   Updated: 2022/02/03 16:51:43 by mbalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_find_id(char *line)
{
	if (!ft_strcmp(line, "NO") || !ft_strcmp(line, "SO")
		|| !ft_strcmp(line, "WE") || !ft_strcmp(line, "EA")
		|| !ft_strcmp(line, "C") || !ft_strcmp(line, "F"))
		return (1);
	return (0);
}

void	ft_save_param(t_data *g, char **line_split)
{
	if (!ft_strcmp(line_split[0], "NO"))
		ft_save_texture(line_split, &g->map.path_north_texture, g);
	else if (!ft_strcmp(line_split[0], "SO"))
		ft_save_texture(line_split, &g->map.path_south_texture, g);
	else if (!ft_strcmp(line_split[0], "WE"))
		ft_save_texture(line_split, &g->map.path_west_texture, g);
	else if (!ft_strcmp(line_split[0], "EA"))
		ft_save_texture(line_split, &g->map.path_east_texture, g);
	else if (!ft_strcmp(line_split[0], "C"))
		ft_save_color(line_split, &g->map.celing, g);
	else if (!ft_strcmp(line_split[0], "F"))
		ft_save_color(line_split, &g->map.floor, g);
}

int	ft_is_newline(char **lines, int *i, char **line_split)
{
	if (!line_split[0])
	{
		ft_free_array(line_split);
		(*i)++;
		return (1);
	}
	if (lines[*i][0] == '\n')
	{
		ft_free_array(line_split);
		(*i)++;
		return (1);
	}
	return (0);
}

int	ft_find_params(char ***map, t_data *g, int i)
{
	char	**lines;
	char	**line_split;

	line_split = NULL;
	lines = *map;
	while (lines[i])
	{
		line_split = ft_split(lines[i], ' ');
		if (ft_is_newline(lines, &i, line_split))
			continue ;
		if (ft_find_id(line_split[0]))
			ft_save_param(g, line_split);
		else if (ft_is_newline(lines, &i, line_split))
			continue ;
		else
		{
			if (g->map.param_count != 6)
				ft_error("Error: Map doesn't contain all parameters");
			break ;
		}
		i++;
		free(line_split);
	}
	ft_free_array(line_split);
	return (i);
}

void	ft_pars_params(char **argv, t_data *g)
{
	int		i;
	char	**map;

	i = 0;
	map = NULL;
	ft_load_map(argv, &map, 0);
	i = ft_find_params(&map, g, 0);
	ft_map_lines_check(map, i, g);
	ft_map_record(map, i, g);
	ft_check_border_map_l(g->map.map_pars, g);
	ft_check_border_map_h(g->map.map_pars, g);
	ft_check_map_inside_l(g->map.map_pars, g);
	ft_check_map_inside_h(g->map.map_pars, g);
	ft_free_array(map);
}
