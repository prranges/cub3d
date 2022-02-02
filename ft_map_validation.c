/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <prranges@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:46:26 by mbalman           #+#    #+#             */
/*   Updated: 2022/02/02 09:56:53 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_chek_name_map(char **argv)
{
	int	l;

	l = (int)ft_strlen(argv[1]);
	if (argv[1][l - 1] == 'b' && argv[1][l - 2] == 'u' \
	&& argv[1][l - 3] == 'c' && argv[1][l - 4] == '.')
		return ;
	else
		ft_error("Error: Bad map name");
}

void	ft_chek_map_evalible(int fd)
{
	if (fd == -1)
		ft_error("Error: Map file not found");
}

void	ft_map_volidation(int argc, char **argv, t_data *g)
{
	int		fd;
	char	*line;

	(void)g;
	if (argc != 2)
		ft_error("Error arguments");
	ft_chek_name_map(argv);
	line = NULL;
	fd = open(argv[1], O_RDONLY);
	ft_chek_map_evalible(fd);
	close(fd);
}

void	ft_error(char *error_msg)
{
	printf("%s\n", error_msg);
	exit (1);
}
