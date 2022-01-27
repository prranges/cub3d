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

int map_array[MAP_W][MAP_H] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1},
	{1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},
	{1,1,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1},
	{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,1},
	{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1},
	{1,1,1,1,2,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1},
	{1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,0,1,1,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,1,1},
	{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,0,1,0,1},
	{1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,0,1,0,1,0,0,0,1,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,0,1,0,1,0,1},
	{1,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,0,1,0,1,0,1},
	{1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,0,1,0,1,0,0,0,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	put_square(t_data *g, int x, int y, int color)
{
	int xx;
	int yy;
	int xxx;
	
	yy = 0;
	xxx = x;
	while (yy < MINIMAP)
	{
		xx = 0;
		x = xxx;
		while (xx < MINIMAP)
		{
			g->img.data[y * WIN_W + x] = color;
			xx++;
			x++;
		}
		yy++;
		y++;
	}
}

void	minimap(t_data *g)
{
    int x;
    int y;
	int xx;
    int yy;
    
	y = 0;
    yy = 0;
	while (y < MAP_H)
	{
        x = 0;
		xx = 0;
		while (x < MAP_W)
		{
			if (map_array[y][x] == 0)
				put_square(g, xx, yy, 13158600);
			if (map_array[y][x] == 1)
				put_square(g, xx, yy, 200);
			if (map_array[y][x] == 2 || map_array[y][x] == -1)
				put_square(g, xx, yy, 6605050);
			put_square(g, (int)g->player_pos_y * MINIMAP, (int)g->player_pos_x * MINIMAP, 16711680);
			xx += MINIMAP;
			x++;
		}
		yy += MINIMAP;
        y++;
	}
}

void	draw(t_data *g)
{
    int x;
    int y;
    
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
	minimap(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
}

void	floor_and_ceiling(t_data *g)
{
	int x;
	int y;

	y = WIN_H / 2 + 1;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			g->screen_buf[y][x] = g->f;
			g->screen_buf[WIN_H - y - 1][x] = g->c;
			x++;
		}
		y++;
	}
}

void	door_close(int x, int y)
{
	int xx = x;
	int yy = y;
	
	map_array[xx][yy] = 2;
}

void	door_open(int x, int y)
{
	int xx = x;
	int yy = y;
	
	map_array[xx][yy] = -1;
}

void	door(t_data *g)
{
	int x;
	int y;
	
	x = (int)g->player_pos_x;
	y = (int)g->player_pos_y;
	if (map_array[x][y - 1] == 2 && g->key_open)
		door_open(x, y - 1);
	else if (map_array[x][y + 1] == 2 && g->key_open)
		door_open(x, y + 1);
	else if (map_array[x + 1][y] == 2 && g->key_open)
		door_open(x + 1, y);
	else if (map_array[x - 1][y] == 2 && g->key_open)
		door_open(x - 1, y);
	else if (map_array[x][y - 1] == -1 && g->key_open)
		door_close(x, y - 1);
	else if (map_array[x][y + 1] == -1 && g->key_open)
		door_close(x, y + 1);
	else if (map_array[x + 1][y] == -1 && g->key_open)
		door_close(x + 1, y);
	else if (map_array[x - 1][y] == -1 && g->key_open)
		door_close(x - 1, y);
	g->key_open = 0;
//}

//	else
//		g->key_open = 0;
//	if (map_array[x][y] == 2)
//		door_open(x, y);
//	if (!j)
//	{
//		if (i++ == 60)
//		{
//			map_array[20][8] = 2;
//			map_array[12][4] = 2;
//			map_array[6][4] = 2;
//			map_array[3][9] = 2;
//			i = 0;
//			j = 0;
//		}
//	}
}

int	game_loop(t_data *g)
{
	floor_and_ceiling(g);
	door(g);
	wall_casting(g);
	draw(g);
	key_update(g);
	return (0);
}

void	load_image(t_data *g, int *texture, char *path, t_img *img)
{
	int x;
	int y;
	
	img->img = mlx_xpm_file_to_image(g->mlx, path, &img->img_w, &img->img_h);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	y = 0;
	while (y < img->img_h)
	{
		x = 0;
		while (x < img->img_w)
		{
			texture[img->img_w * y + x] = img->data[img->img_w * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(g->mlx, img->img);
}

void	load_texture(t_data *g)
{
	t_img	img;

	load_image(g, g->txtrs[0], "textures/eagle.xpm", &img);
	load_image(g, g->txtrs[1], "textures/redbrick.xpm", &img);
	load_image(g, g->txtrs[2], "textures/purplestone.xpm", &img);
	load_image(g, g->txtrs[3], "textures/greystone.xpm", &img);
	load_image(g, g->txtrs[4], "textures/bluestone.xpm", &img);
	load_image(g, g->txtrs[5], "textures/mossy.xpm", &img);
	load_image(g, g->txtrs[6], "textures/wood.xpm", &img);
	load_image(g, g->txtrs[7], "textures/colorstone.xpm", &img);
	load_image(g, g->txtrs[8], "textures/door0.xpm", &img);
	load_image(g, g->txtrs[9], "textures/door1.xpm", &img);
}

void data_init(t_data *g)
{
	g->f = 14443520;
	g->c = 10746347;
	g->mlx = mlx_init();
	g->player_pos_x = 22.0; // начальная позиция x и y
	g->player_pos_y = 11.0;
	g->player_dir_x = -1.0; //начальный вектор направления
	g->player_dir_y = 0.0;
	g->cam_plane_x = 0.0; //версия плоскости камеры для 2d raycaster
	g->cam_plane_y = 0.66;
	g->key_left = 0;
	g->key_up = 0;
	g->key_down = 0;
	g->key_right = 0;
	g->key_esc = 0;
	g->key_open = 0;
	g->move_speed = 0.04;
	g->rot_speed = 0.04;
	g->win = mlx_new_window(g->mlx, WIN_W, WIN_H, "mlx");
	g->img.img = mlx_new_image(g->mlx, WIN_W, WIN_H);
	g->img.data = (int *)mlx_get_data_addr(g->img.img, &g->img.bpp, \
											  &g->img.size_l, &g->img.endian);
}

int	main(void)
{
	t_data g;
	int j;
	int i;
	
	data_init(&g);
	j = 0;
//	while (j < WIN_H)
//	{
//		i = 0;
//		while (i < WIN_W)
//		{
//			data.screen_buf[j][i] = 0;
//			i++;
//		}
//		j++;
//	}
	if (!(g.txtrs = (int **)malloc(sizeof(int *) * 10))) // 10 текструр
		return (-1);
	i = 0;
	while (i < 10)
	{
		if (!(g.txtrs[i] = (int *)malloc(sizeof(int) * (TXTR_H * TXTR_W))))
			return (-1);
		i++;
	}
//	j = 0;
//	while (j < 10)
//	{
//		i = 0;
//		while (i < TXTR_H * TXTR_W)
//		{
//			data.txtrs[j][i] = 0;
//			i++;
//		}
//		j++;
//	}

	load_texture(&g);
	mlx_loop_hook(g.mlx, &game_loop, &g);
	mlx_hook(g.win, PRESS, 0, &key_press, &g);
	mlx_hook(g.win, RELEASE, 0, &key_release, &g);
	mlx_mouse_move(g.win, WIN_W/2, WIN_H/2);
	mlx_mouse_hide();
	mlx_hook(g.win, MOUSE, 0, mouse_move, &g);
	mlx_loop(g.mlx);
}
