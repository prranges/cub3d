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
# define EXIT 17
# define TXTR_W 64
# define TXTR_H 64
# define MAP_W 24
# define MAP_H 24
# define WIN_W 640
# define WIN_H 480

# define ESC 53
# define LEFT 0
# define DOWN 1
# define UP 13
# define RIGHT 2

int	map_array[MAP_W][MAP_H];

typedef struct	s_wall
{
	double camera_x; //координата x на плоскости камеры, которую представляет текущая координата x экрана, сделанная таким образом, что правая сторона экрана получает координату 1, центр экрана получает координату 0, а левая сторона экрана получает координату -1. Из этого можно вычислить направление луча, как было объяснено ранее: как сумму вектора направления и части плоского вектора. Это необходимо сделать как для координат x, так и для y вектора (поскольку добавление двух векторов — это добавление их координат x и добавление их координат y).
	double ray_dir_x;
	double ray_dir_y;
	int map_x; //mapX и mapY представляют текущую клетку карты, в которой находится луч
	int map_y;
	//длина луча от текущей позиции до следующей x или y-стороны
	double side_dist_x; //sideDistX и sideDistY изначально представляют собой расстояние, которое луч должен пройти от своей начальной позиции до первой стороны x и первой стороны y. Позже в коде они будут увеличиваться по мере выполнения шагов.
	double side_dist_y; //deltaDistX и deltaDistY — это расстояние, которое должен пройти луч, чтобы пройти от 1 стороны x до следующей стороны x или от 1 стороны y до следующей стороны y.
	double delta_dist_x;
	double delta_dist_y;
	double perp_wall_dist; // перпендикулярное экрану расстояние до стены.
	int step_x;
	int step_y;
	int hit; //hit используется для определения того, может ли быть завершен предстоящий цикл, а side будет содержать, была ли ударена сторона x или сторона y стены. Если была поражена сторона x, сторона устанавливается равной 0, если была поражена сторона y, сторона будет равна 1. Под стороной x и стороной y я имею в виду линии сетки, которые являются границами между двумя квадратами. .

	int side; //был ли удар о стену NS или EW?
	int line_height; //высота вертикальной линии, которая должна быть нарисована
	int draw_start;
	int draw_end;
	int txtr_num;
	double wall_x; //где именно была пробита стена. Значение wall_ч представляет собой точное значение места удара по стене, а не просто целочисленные координаты стены. Это необходимо, чтобы знать, какую x-координату текстуры мы должны использовать. Это вычисляется, сначала вычисляя точную координату x или y в мире, а затем вычитая из нее целочисленное значение стены. Обратите внимание, что даже если она называется wallX, на самом деле это y-координата стены, если side==1, но это всегда x-координата текстуры.
	int txtr_x;
	double step;
	double txtr_pos;
	int txtr_y;
	int color;
	int x;
	int y;
}				t_wall;

typedef struct	s_floor
{
	float ray_dir_x_0;
	float ray_dir_y_0;
	float ray_dir_x_1;
	float ray_dir_y_1;
	int p;
	float pos_z;
	float row_distance;
	float floor_step_x;
	float floor_step_y;
	float floor_x;
	float floor_y;
	int cell_x;
	int cell_y;
	int t_x;
	int t_y;
	int checker_board_pattern;
	int floor_texture;
	int ceiling_texture;
	int color;
	int x;
	int y;
}				t_floor;

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_w;
	int		img_h;
}				t_img;

typedef struct	s_data
{
	double player_pos_x; // вектор положения игрока
	double player_pos_y; //
	double player_dir_x; // направление игрока
	double player_dir_y; // плоскость камеры игрока
	double cam_plane_x;
	double cam_plane_y;
	void	*mlx;
	void	*win;
	int		key_left;
	int		key_up;
	int		key_down;
	int		key_right;
	int		key_esc;
	t_img	img;
	int		screen_buf[WIN_H][WIN_W]; // буфер по размеру экрана
	double	zBuffer[WIN_W]; // буфер по ширине экрана
	int		**txtrs;
	double	move_speed;
	double	rot_speed;
}				t_data;

int		key_press(int key, t_data *data);
int		key_release(int key, t_data *data);
void	key_update(t_data *data);
void	wall_casting(t_data *data);
void	floor_casting(t_data *data);

#endif
