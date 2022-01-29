/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:46:26 by mbalman           #+#    #+#             */
/*   Updated: 2022/01/28 13:07:49 by mbalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_chek_name_map(char **argv)
{
	int	l;

	l = (int)ft_strlen(argv[1]);
	if (argv[1][l - 1 ] == 'b' && argv[1][l - 2] == 'u' \
	&& argv[1][l - 3] == 'c' && argv[1][l - 4] == '.')
		return ;
	else
	{
		printf("Error Bad map name\n");
		exit (0);
	}
}

void	ft_chek_map_evalible(int fd)
{
	if (fd == -1)
	{
		printf("Error\nMap file not found\n");
		exit (0);
	}
}

void	ft_map_volidation(int argc, char **argv, t_data *g)
{
	int		fd;
	char	*line;
	
	(void)g;
	if (argc != 2)
	{	
		printf("Error arguments\n");
		exit(0);
	}
	ft_chek_name_map(argv);
	line = NULL;
	fd = open(argv[1], O_RDONLY);
	ft_chek_map_evalible(fd);
}

char *ft_clean_tab(char *str)
{
	int i = 0;
	int count = 0;
	char *str1;
	int t = 0;
	int j = 0;
	
	while (str[i])
	{
		if (str[i] == '\t')
			count++;
		i++;
	}
	str1 = calloc(sizeof(char), (ft_strlen(str) + 1 + (count * 3)));
	i = 0;
	while (str[i])
	{
		if (str[i] != '\t')
		{
			str1[j] = str[i];
			i++;
			j++;
		}
		else
		{	
			while (t < 4)
			{
				str1[j] = ' ';
				j++;
				t++;
			}
			i++;
		}	
	}
	return (str1);
}

void ft_error(void)
{
	printf("Error: bad map parametr\n");
	exit (1);
}
