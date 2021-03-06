/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_record.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 12:05:40 by mbalman           #+#    #+#             */
/*   Updated: 2022/02/03 16:40:34 by mbalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_map_record(char **lines, int i, t_data *g)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	g->map.map_pars = malloc(sizeof(char *) * g->map.size_h);
	while (j < g->map.size_h)
	{
		g->map.map_pars[j] = malloc(sizeof(char) * g->map.size_l);
		ft_bchar(g->map.map_pars[j], g->map.size_l, ' ');
		j++;
	}
	j = 0;
	while (j < g->map.size_h)
	{
		k = 0;
		while (lines[i][k])
		{
			g->map.map_pars[j][k] = lines[i][k];
			k++;
		}
		j++;
		i++;
	}
}

void	ft_save_texture(char **line_split, char **path_texture, t_data *g)
{
	if (line_split[2])
		ft_error("Error: Bad parameters!");
	ft_texture_validation(line_split[1]);
	if (!*path_texture)
	{
		*path_texture = line_split[1];
		free(line_split[0]);
		g->map.param_count++;
	}
	else
		ft_error("Error: Texture is doublicated!");
}

void	ft_save_color(char **line_split, char **color, t_data *g)
{
	char	**split_color;

	if (line_split[2])
		ft_error("Error: Bad parameters!");
	if (*color)
		ft_error("Error: Color parameter is doublicated!!!");
	*color = line_split[1];
	g->map.param_count++;
	split_color = ft_split(*color, ',');
	if (!ft_strncmp(line_split[0], "C", 1))
	{
		g->map.celing_color = ft_check_rgb(split_color);
		free(line_split[0]);
	}
	if (!ft_strncmp(line_split[0], "F", 1))
	{
		g->map.floor_color = ft_check_rgb(split_color);
		free(line_split[0]);
	}
	ft_free_array(split_color);
}	
