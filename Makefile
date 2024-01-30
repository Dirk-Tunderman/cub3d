# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aolde-mo <aolde-mo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/21 14:37:39 by aolde-mo          #+#    #+#              #
#    Updated: 2024/01/30 08:38:18 by aolde-mo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
LIBMLX = ./MLX42
LIBFT = libft/libft.a
SRC = main.c error.c input_check.c utils.c init.c raycasting.c draw.c hooks.c texture_parsing.c
# SRC = test.c
VPATH = src
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_DIR = obj
CFLAGS = -Ofast
# CFLAGS = -Ofast -fsanitize=address -g
# CFLAGS =
LIBS = $(LIBMLX)/build/libmlx42.a -L/Users/aolde-mo/.brew/opt/glfw/lib -lglfw -ldl -pthread -lm -framework Cocoa -framework OpenGL -framework IOKit

CC = gcc

all: libmlx $(NAME)

libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME) : $(OBJ) $(LIBFT) inc/cub3d.h
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(LIBFT) -o $(NAME)
	@printf "$(NAME) compiled\n"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(LIBFT):
	@make -C libft

clean:
	@rm -rf $(OBJ_DIR)
	@make -C libft clean

fclean:
	@rm -rf $(OBJ_DIR) $(NAME)
	@make -C libft fclean

re: fclean all

PHONY: all clean fclean re