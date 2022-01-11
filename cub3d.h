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

# define W 640
# define H 480

# define ESC 53
# define LEFT 0
# define DOWN 1
# define UP 13
# define RIGHT 2

typedef struct	s_data
{
	double 				pos_x;
	double 				pos_y;
	double 				dir_x;
	double 				dir_y;
	double 				plane_x;
	double 				plane_y;
	void				*mlx;
	void				*win;
	int					**map;
	double				move_speed;
	double				rotation_speed;
	struct s_textures	*txtr;
}				t_data;

typedef struct s_textures
{
	void	*t_brick;
	void	*t_blue;
	void	*t_wood;
	void	*t_gray;
}				t_textures;

# define BRICK	"./textures/brick.xpm"
# define BLUE	"./textures/blue.xpm"
# define WOOD	"./textures/wood.xpm"
# define GRAY	"./textures/gray.xpm"

#endif
