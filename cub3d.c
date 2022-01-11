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

	int	map[24][24] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

int	close_win(t_data *data)
{
	int	i;

	i = -1;
//	while (data->map.map[++i])
//		free(data->map.map[i]);
	if (data->mlx)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_window(data->mlx, data->win);
	}
	exit (0);
}

void	read_xpm(t_data *data)
{
	int		w;
	int		h;

	data->txtr->t_brick = mlx_xpm_file_to_image(data->mlx, BRICK, &w, &h);
	data->txtr->t_blue = mlx_xpm_file_to_image(data->mlx, BLUE, &w, &h);
	data->txtr->t_wood = mlx_xpm_file_to_image(data->mlx, WOOD, &w, &h);
	data->txtr->t_gray = mlx_xpm_file_to_image(data->mlx, GRAY, &w, &h);
}

void	put_line(t_data *data, int x, int y_start, int y_end, int color)
{
	int	y;

	y = y_start;
	while (y <= y_end)
	{
		mlx_pixel_put(data->mlx, data->win, x, y, color);
		y++;
	}
}

int	game_loop(t_data *data)
{
	int	x;
	
	x = -1;
//	while (++x < W)
//	{
//		put_line(data, x, 180, 300, 0xFFF000);
//	}
	
	while (++x < W)
		{
//			put_line(data, x, 180, 300, 0xFFF000);
			mlx_put_image_to_window(data->mlx, data->win, data->txtr->t_brick, x*64, 200);
		}
	return (0);
}

char	key_move(t_data *data, char c)
{
	(void)data;
	if (c == 'L')
		;
	if (c == 'D')
		;
	if (c == 'U')
		;
	if (c == 'R')
		;
	return (c);
}

int	key_handler(int key, t_data *data)
{
	if (key == ESC)
		close_win(data);
	
	if (key == LEFT)
		key_move(data, 'L');
	if (key == DOWN)
		key_move(data, 'D');
	if (key == UP)
		key_move(data, 'U');
	if (key == RIGHT)
		key_move(data, 'R');
	return (key);
}

int	main()
{
	t_data	data;
	
	data.mlx = mlx_init();
	data.pos_x = 22.0;
	data.pos_y = 11.5;
	data.dir_x = -1.0;
	data.dir_y = 0.0;
	data.plane_x = 0.0;
	data.plane_y = 0.66;
	data.move_speed = 0.05;
	data.rotation_speed = 0.05;
	data.win = mlx_new_window(data.mlx, W, H, "cub3d");
	
	read_xpm(&data);
	
	mlx_loop_hook(data.mlx, &game_loop, (void *)&data);
	mlx_hook(data.win, 2, 0, &key_handler, (void *)&data);
	mlx_hook(data.win, 17, 0L, close_win, (void *)&data);
	mlx_loop(data.mlx);
	
//	printf("Hello world!\n");
	return (0);
}
