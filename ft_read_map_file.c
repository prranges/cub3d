/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 11:54:06 by mbalman           #+#    #+#             */
/*   Updated: 2022/01/30 18:32:43 by mbalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_size_map(char **argv)
{
	int		size;
	int		end_file;
	int		fd;
	char	*str;

	size = 0;
	str = NULL;
	end_file = 1;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		perror("Error");
	while (end_file)
	{
		end_file = get_next_line(fd, &str);
		free(str);
		size++;
	}
	close(fd);
	return (size);
}

void	ft_load_map(char **argv, char ***map)
{
	int		fd;
	int		end_file;
	int		i;
	int		size;
	char	*str;
	char	**temp;

	temp = NULL;
	i = 0;
	end_file = 1;
	size = ft_size_map(argv);
	temp = (char **)malloc(sizeof(char *) * (size + 1));
	fd = open(argv[1], O_RDONLY);
	while (end_file)
	{
		end_file = get_next_line(fd, &str);
		temp[i] = str;
		i++;
	}
	temp[i] = NULL;
	i = 0;
	*map = temp;
	close(fd);
}
