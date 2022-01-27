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

void	data_init(t_data *g)
{
	g->f = 14443520;
	g->c = 10746347;
	g->mlx = mlx_init();
	g->p_pos_x = 22.0; // начальная позиция x и y
	g->p_pos_y = 11.0;
	g->p_dir_x = -1.0; //начальный вектор направления
	g->p_dir_y = 0.0;
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
