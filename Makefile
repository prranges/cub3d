# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prranges <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 14:41:12 by prranges          #+#    #+#              #
#    Updated: 2021/10/06 14:41:19 by prranges         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= cub3d

LIBFT	= ./libft/libft.a
LFT_DIR = ./libft

SRCS	= cub3d.c \
		  load_and_init.c \
		  keys.c \
		  mouse.c \
		  minimap.c \
		  doors.c \
		  walls_01.c \
		  walls_02.c \
	  get_next_line/get_next_line.c \
	  get_next_line/get_next_line_utils.c

CC	= gcc
CFLAGS 	= -Wall -Wextra -Werror

MLX 	= -lmlx -L ./mlx -framework OpenGL -framework AppKit

RM	= rm -rf

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
	
fclean: clean
	$(RM) $(NAME)
	make -C ./libft fclean

re: fclean all

.PHONY:		all clean fclean re
