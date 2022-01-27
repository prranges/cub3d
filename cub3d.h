/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prranges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:52:52 by prranges          #+#    #+#             */
/*   Updated: 2022/01/10 09:52:54 by prranges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"

# include "./mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# define PRESS 2
# define RELEASE 3
# define MOUSE 6
# define EXIT 17

# define TXTR_W 64
# define TXTR_H 64
# define MAP_W 24
# define MAP_H 24
# define MINIMAP 6
# define WIN_W 640
# define WIN_H 480

# define ESC 53
# define LEFT 0
# define DOWN 1
# define UP 13
# define RIGHT 2
# define OPEN 49

int	map_array[MAP_W][MAP_H];

typedef struct s_wall
{
	double	camera_x; //координата x на плоскости камеры, которую представляет текущая координата x экрана, сделанная таким образом, что правая сторона экрана получает координату 1, центр экрана получает координату 0, а левая сторона экрана получает координату -1. Из этого можно вычислить направление луча, как было объяснено ранее: как сумму вектора направления и части плоского вектора. Это необходимо сделать как для координат x, так и для y вектора (поскольку добавление двух векторов — это добавление их координат x и добавление их координат y).
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x; //mapX и mapY представляют текущую клетку карты, в которой находится луч
	int		map_y;
	//длина луча от текущей позиции до следующей x или y-стороны
	double	side_dist_x; //sideDistX и sideDistY изначально представляют собой расстояние, которое луч должен пройти от своей начальной позиции до первой стороны x и первой стороны y. Позже в коде они будут увеличиваться по мере выполнения шагов.
	double	side_dist_y; //deltaDistX и deltaDistY — это расстояние, которое должен пройти луч, чтобы пройти от 1 стороны x до следующей стороны x или от 1 стороны y до следующей стороны y.
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist; // перпендикулярное экрану расстояние до стены.
	int		step_x;
	int		step_y;
	int		hit; //hit используется для определения того, может ли быть завершен предстоящий цикл, а side будет содержать, была ли ударена сторона x или сторона y стены. Если была поражена сторона x, сторона устанавливается равной 0, если была поражена сторона y, сторона будет равна 1. Под стороной x и стороной y я имею в виду линии сетки, которые являются границами между двумя квадратами. .
	int		side; //был ли удар о стену NS или EW?
	int		line_height; //высота вертикальной линии, которая должна быть нарисована
	int		draw_start;
	int		draw_end;
	int		txtr_num;
	double	wall_x; //где именно была пробита стена. Значение wall_ч представляет собой точное значение места удара по стене, а не просто целочисленные координаты стены. Это необходимо, чтобы знать, какую x-координату текстуры мы должны использовать. Это вычисляется, сначала вычисляя точную координату x или y в мире, а затем вычитая из нее целочисленное значение стены. Обратите внимание, что даже если она называется wallX, на самом деле это y-координата стены, если side==1, но это всегда x-координата текстуры.
	int		txtr_x;
	double	step;
	double	txtr_pos;
	int		txtr_y;
	int		color;
	int		x;
	int		y;
}				t_wall;

typedef struct s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_w;
	int		img_h;
}				t_img;

typedef struct s_minimap
{
	int	x;
	int	y;
	int	xx;
	int	yy;
}				t_minimap;

typedef struct s_data
{
	double	p_pos_x; // вектор положения игрока
	double	p_pos_y; //
	double	p_dir_x; // направление игрока
	double	p_dir_y; // плоскость камеры игрока
	double	cam_plane_x;
	double	cam_plane_y;
	void	*mlx;
	void	*win;
	int		key_left;
	int		key_up;
	int		key_down;
	int		key_right;
	int		key_esc;
	int		mouse_x;
	int		key_open;
	t_img	img;
	int		screen_buf[WIN_H][WIN_W]; // буфер по размеру экрана
	double	z_buffer[WIN_W]; // буфер по ширине экрана
	int		**txtrs;
	void	*p;
	void	*m0;
	void	*m1;
	double	move_speed;
	double	rot_speed;
	int		f;
	int		c;
}				t_data;

void	data_init(t_data *g);
void	load_texture(t_data *g);
int		key_press(int key, t_data *g);
int		key_release(int key, t_data *g);
void	key_update(t_data *g);
void	wall_casting(t_data *g);
void	draw(t_data *g);
void	choose_pixel(t_data *g, t_wall *w);
void	pixels_to_screen_buf(t_data *g, t_wall *w);
void	player_rotate_left(t_data *g);
void	player_rotate_right(t_data *g);
int		mouse_move(int x, int y, t_data *g);
void	minimap(t_data *g);
void	door(t_data *g);

#endif
