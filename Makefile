# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaille <abaille@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 00:22:44 by abaille           #+#    #+#              #
#    Updated: 2019/05/28 15:21:27 by abaille          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LIBFT = ./libft
MLX = ./minilibx
FRK = -framework
OPEN = OpenGL
APPK = AppKit

SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./includes/ \
			./minilibx/ \
			./libft/

SRC_NAME = fdf.c \
		   calc_coord.c \
		   draw_fdf.c \
		   fdf_checkerror.c \
		   keycode_fdf.c \
		   maths.c \
		   random_color.c \
		   read_fdf.c \
		   utils.c 

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I, $(INC_PATH))

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT)
	make -C $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(FRK) $(OPEN) $(FRK) $(APPK) -o $(NAME) \
	-L$(LIBFT) -lft -L$(MLX) -lmlx 

$(OBJ) : | $(OBJ_PATH)

$(OBJ_PATH) :
		@mkdir objs

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	make -C $(LIBFT) clean
	make -C $(MLX) clean
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all
