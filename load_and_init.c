/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_and_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:34:09 by prranges          #+#    #+#             */
/*   Updated: 2022/01/27 16:34:10 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_image(t_data *g, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->img = mlx_xpm_file_to_image(g->mlx, path, &img->img_w, &img->img_h);
	img->data = (int *)mlx_get_data_addr(img->img, \
		&img->bpp, &img->size_l, &img->endian);
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

	load_image(g, g->txtrs[0], g->map.path_north_texture, &img);
	load_image(g, g->txtrs[1], g->map.path_south_texture, &img);
	load_image(g, g->txtrs[2], g->map.path_east_texture, &img);
	load_image(g, g->txtrs[3], g->map.path_west_texture, &img);
	load_image(g, g->txtrs[4], "textures/door0.xpm", &img);
}

void	data_init(t_data *g)
{
	g->mlx = mlx_init();
	g->p_dir_x = -1.0; //начальный вектор направления
	g->p_dir_y = 0.0;
	g->cam_plane_x = 0.0; //версия плоскости камеры для 2d raycaster
	g->cam_plane_y = 0.66;
	g->k.key_left = 0;
	g->k.key_up = 0;
	g->k.key_down = 0;
	g->k.key_right = 0;
	g->k.key_esc = 0;
	g->k.key_open = 0;
	g->move_speed = 0.04;
	g->rot_speed = 0.04;
	g->win = mlx_new_window(g->mlx, WIN_W, WIN_H, "mlx");
	g->img.img = mlx_new_image(g->mlx, WIN_W, WIN_H);
	g->img.data = (int *)mlx_get_data_addr(g->img.img, &g->img.bpp, \
		&g->img.size_l, &g->img.endian);
}

void ft_init(t_data *g)
{
	    g->map.path_north_texture = NULL;
		g->map.path_south_texture = NULL;
		g->map.path_east_texture = NULL;
		g->map.path_west_texture = NULL;
		g->map.param_count = 0;
		g->map.size_h = 0;
		g->map.size_l = 0;
}
