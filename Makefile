# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbalman <mbalman@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 14:41:12 by prranges          #+#    #+#              #
#    Updated: 2022/01/30 17:26:44 by mbalman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= cub3d

LIBFT	= ./libft/libft.a
LFT_DIR = ./libft

SRCS	= cub3d.c \
		  ft_map_validation.c \
		  ft_map_parse.c \
		  ft_map_check_border.c \
		  ft_map_check_inside.c \
		  ft_parsing_utils.c \
		  ft_read_map_file.c \
		  ft_map_check_symbols.c \
		  ft_map_record.c \
		  load_and_init.c \
		  keys_01.c \
		  keys_02.c \
		  mouse_bonus.c \
		  minimap_bonus.c \
		  doors_bonus.c \
		  walls_01.c \
		  walls_02.c \
		  get_next_line/get_next_line.c \
		  get_next_line/get_next_line_utils.c

CC	= gcc
CFLAGS 	= -Wall -Wextra -Werror

MLX 	= -lmlx -L ./mlx -framework OpenGL -framework AppKit

RM	= rm -rf

bonus … : CFLAGS += -D BONUS=1

OBJS_DIR 	= temp

OBJS	= $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

HDR	= -I./
LFT_HDR = -I$(LFT_DIR)
LFT_BIN = -L$(LFT_DIR) -lft

all: $(LIBFT) $(NAME)

FORCE:	;

$(LIBFT): FORCE
	make -C $(LFT_DIR)

$(OBJS_DIR):
	mkdir $@
	mkdir $@/get_next_line

$(OBJS_DIR)/%.o: %.c Makefile $(OBJS_DIR)
	gcc -g $(CFLAGS) $(HDR) $(LFT_HDR) -c $< -o $@

$(NAME): $(OBJS) ./cub3d.h
	gcc -g $(MLX) $(OBJS) $(LFT_BIN) -o $@
clean:
	$(RM) $(OBJS_DIR)
	make -C ./libft clean
	
bonus:	re

fclean: clean
	$(RM) $(NAME)
	make -C ./libft fclean

re: fclean all

.PHONY:		all clean fclean re
