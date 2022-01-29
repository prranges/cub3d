/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 11:04:09 by mbalman           #+#    #+#             */
/*   Updated: 2022/01/29 11:11:54 by mbalman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strisnum(const char *str) // проверка на число
{
	int	i;
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int rgb_to_int(int r, int g, int b) // перевод rgb в int
{
  int c = r;
  c = (c << 8) | g;
  c = (c << 8) | b;
  return c;
}

void	ft_bchar(void *dest, size_t len, char c) // заполнение строки символами
{
	char	*tmp;
	size_t	i;

	tmp = dest;
	i = 0;
	while (i < len)
		*(tmp + i++) = c;
}

int    ft_check_rgb(char **split_color)
{
	int i;
	int rgb[3];
	i = 0;
	while (i < 3)
	{
		if(ft_strisnum(split_color[i]) && ft_atoi(split_color[i]) <= 255)
			rgb[i] = ft_atoi(split_color[i]);
		else
			ft_error("Error: This is not num or num > 255");          
		i++;
	}
	return (rgb_to_int(rgb[0], rgb[1], rgb[2]));
}