/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_record.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 12:05:40 by mbalman           #+#    #+#             */
/*   Updated: 2022/01/29 12:15:25 by mbalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_map_record(char **lines, int i, t_data *g)
{
	int     j;
	int     k;

	(void)i;
	(void)lines;
	j = 0;
	k = 0;
	g->map.map_pars = malloc(sizeof(char*) * g->map.map_size_h);
	while (j < g->map.map_size_h)
	{
		g->map.map_pars[j] = malloc(sizeof(char) * g->map.map_size_l);
		ft_bchar(g->map.map_pars[j], g->map.map_size_l, ' ');
		j++;
	}
	j =0;
	while(j < g->map.map_size_h)
	{
		k = 0;
		while(lines[i][k])
		{
			g->map.map_pars[j][k] = lines[i][k];
			printf("%c", g->map.map_pars[j][k]);
			k++;
		}
		printf("\n");
		j++;
		i++;
	}
	ft_check_border_map_l(g->map.map_pars, g);
	ft_check_border_map_h(g->map.map_pars, g);
	ft_check_map_inside_l(g->map.map_pars, g);
	ft_check_map_inside_h(g->map.map_pars, g);
}

void    ft_save_param(char *line_split, char **path_texture, t_data *g)  // запись текстур
{
	if (!*path_texture)
	{
		*path_texture = line_split;
		g->map.param_count++;
	}
	else
		ft_error("Error: Params dublicate!");
}

void    ft_save_color(char **line_split, char **color, t_data *g) //запись цвета для пола и потолка
{
	char    **split_color;
	
	if (*color)
		ft_error("Error: Params dublicate!!!"); 
	*color = line_split[1];
	g->map.param_count++;
	split_color = ft_split(*color, ',');

	if (!ft_strncmp(line_split[0], "C", 1))
		g->map.celing_color =ft_check_rgb(split_color);
	if (!ft_strncmp(line_split[0], "F", 1))
		g->map.floor_color =ft_check_rgb(split_color);
}