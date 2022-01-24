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
	{8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
	{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
	{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
	{8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
	{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
	{8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
	{7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
	{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
	{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
	{7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
	{2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
	{2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
	{2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
	{1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
	{2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
	{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
	{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
	{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
	{2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
};

void	draw(t_data *data)
{
    int x;
    int y;
    
    y = 0;
	while (y < WIN_H)
	{
        x = 0;
		while (x < WIN_W)
		{
			data->img.data[y * WIN_W + x] = data->screen_buf[y][x];
            x++;
		}
        y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

int	game_loop(t_data *data)
{
	floor_casting(data);
	wall_casting(data);
	draw(data);
	key_update(data);
	return (0);
}

void	load_image(t_data *data, int *texture, char *path, t_img *img)
{
	int x;
	int y;
	
	img->img = mlx_xpm_file_to_image(data->mlx, path, &img->img_w, &img->img_h);
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
	mlx_destroy_image(data->mlx, img->img);
}

void	load_texture(t_data *data)
{
	t_img	img;

	load_image(data, data->txtrs[0], "textures/eagle.xpm", &img);
	load_image(data, data->txtrs[1], "textures/redbrick.xpm", &img);
	load_image(data, data->txtrs[2], "textures/purplestone.xpm", &img);
	load_image(data, data->txtrs[3], "textures/greystone.xpm", &img);
	load_image(data, data->txtrs[4], "textures/bluestone.xpm", &img);
	load_image(data, data->txtrs[5], "textures/mossy.xpm", &img);
	load_image(data, data->txtrs[6], "textures/wood.xpm", &img);
	load_image(data, data->txtrs[7], "textures/colorstone.xpm", &img);
	load_image(data, data->txtrs[8], "textures/barrel.xpm", &img);
	load_image(data, data->txtrs[9], "textures/pillar.xpm", &img);
	load_image(data, data->txtrs[10], "textures/greenlight.xpm", &img);
}

void data_init(t_data *data)
{
	data->mlx = mlx_init();
	data->player_pos_x = 22.0; // начальная позиция x и y
	data->player_pos_y = 11.5;
	data->player_dir_x = -1.0; //начальный вектор направления
	data->player_dir_y = 0.0;
	data->cam_plane_x = 0.0; //версия плоскости камеры для 2d raycaster
	data->cam_plane_y = 0.66;
	data->key_left = 0;
	data->key_up = 0;
	data->key_down = 0;
	data->key_right = 0;
	data->key_esc = 0;
	data->move_speed = 0.05;
	data->rot_speed = 0.05;
	data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, "mlx");
	data->img.img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	data->img.data = (int *)mlx_get_data_addr(data->img.img, &data->img.bpp, \
											  &data->img.size_l, &data->img.endian);
}

int	main(void)
{
	t_data data;
	int j;
	int i;
	
	data_init(&data);
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
	if (!(data.txtrs = (int **)malloc(sizeof(int *) * 11))) // 11 текструр
		return (-1);
	i = 0;
	while (i < 11)
	{
		if (!(data.txtrs[i] = (int *)malloc(sizeof(int) * (TXTR_H * TXTR_W))))
			return (-1);
		i++;
	}
//	j = 0;
//	while (j < 11)
//	{
//		i = 0;
//		while (i < TXTR_H * TXTR_W)
//		{
//			data.txtrs[j][i] = 0;
//			i++;
//		}
//		j++;
//	}

	load_texture(&data);
	mlx_loop_hook(data.mlx, &game_loop, &data);
	mlx_hook(data.win, PRESS, 0, &key_press, &data);
	mlx_hook(data.win, RELEASE, 0, &key_release, &data);
	mlx_loop(data.mlx);
}
