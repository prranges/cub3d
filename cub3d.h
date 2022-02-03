/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:52:52 by prranges          #+#    #+#             */
/*   Updated: 2022/02/03 16:48:00 by mbalman          ###   ########.fr       */
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
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;	
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		txtr_num;
	double	wall_x;
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

typedef struct s_data
{
	double		p_pos_x;
	double		p_pos_y;
	double		p_dir_x;
	double		p_dir_y;
	double		cam_plane_x;
	double		cam_plane_y;
	void		*mlx;
	void		*win;
	t_keys		k;
	t_img		img;
	int			screen_buf[WIN_H][WIN_W];
	int			**txtrs;
	double		move_speed;
	double		rot_speed;
	t_map		map;
	int			position_flag;
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
void	ft_load_map(char **argv, char ***map, int i);
void	ft_map_lines_check(char **lines, int i, t_data *g);
void	ft_map_record(char **lines, int i, t_data *g);
void	ft_save_param(t_data *g, char **line_split);
void	ft_save_texture(char **line_split, char **path_texture, t_data *g);
void	ft_save_color(char **line_split, char **color, t_data *g);
void	ft_map_error(char *error_msg, char error_symbol);
void	ft_map_error_symbol(char error, char symbol, int i, int j);
void	ft_free_array(char **array);
void	ft_texture_validation(char *path);

#endif
