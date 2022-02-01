/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:52:52 by prranges          #+#    #+#             */
/*   Updated: 2022/01/30 18:01:52 by mbalman          ###   ########.fr       */
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

# define WIN_W 640
# define WIN_H 480
# define MINIMAP 6

# define ESC 53
# define LEFT 0
# define DOWN 1
# define UP 13
# define RIGHT 2
# define OPEN 49

# ifndef BONUS
#  define BONUS 0
# endif

typedef struct s_color // mbalman
{
	int	red;
	int	green;
	int	blue;
}				t_color;

typedef struct s_map // mbalman
{
	char	**map_pars;
	int		size_l;
	int		size_h;
	char	*path_north_texture;
	char	*path_south_texture;
	char	*path_east_texture;
	char	*path_west_texture;
	int		param_count;
	char	*celing;
	char	*floor;
	int		celing_color;
	int		floor_color;
	int		flag_error;
}				t_map;

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

typedef struct s_keys
{
	int		key_left;
	int		key_up;
	int		key_down;
	int		key_right;
	int		key_esc;
	int		mouse_x;
	int		key_open;
}				t_keys;

typedef struct s_iterators
{
	int		i;
	int		j;
	int		k;
}				t_iterators;

typedef struct s_data
{
	double		p_pos_x; // вектор положения игрока
	double		p_pos_y; //
	double		p_dir_x; // направление игрока
	double		p_dir_y; // плоскость камеры игрока
	double		cam_plane_x;
	double		cam_plane_y;
	void		*mlx;
	void		*win;
	t_keys		k;
	t_img		img;
	int			screen_buf[WIN_H][WIN_W]; // буфер по размеру экрана
	int			**txtrs;
	double		move_speed;
	double		rot_speed;
	t_map		map;
	int			position_flag;
	t_iterators	itr;
}				t_data;

void	data_init(t_data *g);
void	load_texture(t_data *g);
int		key_press(int key, t_data *g);
int		key_release(int key, t_data *g);
void	key_update(t_data *g);
void	wall_casting(t_data *g);
void	floor_and_ceiling(t_data *g);
void	draw(t_data *g);
void	choose_pixel(t_data *g, t_wall *w);
void	pixels_to_screen_buf(t_data *g, t_wall *w);
void	player_rotate_left(t_data *g);
void	player_rotate_right(t_data *g);
void	player_move_up(t_data *g);
void	player_move_up_bonus(t_data *g);
void	player_move_down(t_data *g);
void	player_move_down_bonus(t_data *g);
int		mouse_move(int x, int y, t_data *g);
void	minimap(t_data *g);
void	door(t_data *g);

void	ft_map_volidation(int argc, char **argv, t_data *data); //mbalman
void	ft_pars_map(char **argv, t_data *data);
void	ft_pars_params(char **argv, t_data *data);
void	ft_error(char *error_msg);
void	ft_init(t_data *data);
int		ft_strisnum(const char *str);
int		rgb_to_int(int r, int g, int b);
void	ft_bchar(void *dest, size_t len, char c);
int		ft_check_rgb(char **split_color);
void	ft_param_validation(t_data *data);
void	ft_check_border_map_l(char **map, t_data *g);
void	ft_check_border_map_h(char **map, t_data *g);
void	ft_check_map_inside_l(char **map, t_data *g);
void	ft_check_map_inside_h(char **map, t_data *g);
void	ft_load_map(char **argv, char ***map);
void	ft_map_lines_check(char **lines, int i, t_data *g);
void	ft_map_record(char **lines, int i, t_data *g);
void	ft_save_param(char **line_split, char **path_texture, t_data *g);
void	ft_save_color(char **line_split, char **color, t_data *g);
void	ft_map_error(char *error_msg, char error_symbol);
void	ft_map_error_symbol(char *error_msg, char symbol, int i, int j);
void	ft_free_array(char **array);

#endif
