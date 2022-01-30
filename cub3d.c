/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:52:40 by prranges          #+#    #+#             */
/*   Updated: 2022/01/10 09:52:45 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_data *g)
{
	int	i;

	i = -1;
	while (g->map.map_pars[++i])
		free(g->map.map_pars[i]);
	if (g->mlx)
	{
		mlx_clear_window(g->mlx, g->win);
		mlx_destroy_window(g->mlx, g->win);
	}
	exit (0);
}

void	draw(t_data *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			g->img.data[y * WIN_W + x] = g->screen_buf[y][x];
			x++;
		}
		y++;
	}
	if (BONUS)
		minimap(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
}

int	game_loop(t_data *g)
{
	floor_and_ceiling(g);
	if (BONUS)
		door(g);
	wall_casting(g);
	draw(g);
	key_update(g);
	return (0);
}

int	txtrs_malloc(t_data *g)
{
	int		j;
	int		i;

	j = 0;
	g->txtrs = (int **)malloc(sizeof(int *) * 5); // 5 текструр
	if (!g->txtrs)
		return (-1);
	i = 0;
	while (i < 5)
	{
		g->txtrs[i] = (int *)malloc(sizeof(int) * (TXTR_H * TXTR_W));
		if (!g->txtrs[i])
			return (-1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*g;
	
	g = malloc(sizeof(t_data));

	data_init(g);
	ft_init(g);
	ft_map_volidation(argc, argv, g);
	ft_pars_params(argv, g);
	if (txtrs_malloc(g))
		exit(1);
	load_texture(g);
	mlx_loop_hook(g->mlx, &game_loop, g);
	mlx_hook(g->win, PRESS, 0, &key_press, g);
	mlx_hook(g->win, RELEASE, 0, &key_release, g);
	mlx_hook(g->win, 17, 0L, close_win, g);
	if (BONUS)
	{
		mlx_mouse_move(g->win, WIN_W / 2, WIN_H / 2);
		mlx_mouse_hide();
		mlx_hook(g->win, MOUSE, 0, mouse_move, g);
	}
	mlx_loop(g->mlx);
}
