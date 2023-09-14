# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phelebra <phelebra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 16:55:23 by jbartosi          #+#    #+#              #
#    Updated: 2023/09/14 17:54:40 by phelebra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CFLAGS = -Wall -Wextra -Werror
LIBFT = Libft
MLX = minilibx
UNAME_S := $(shell uname -s)

SRC = main.c hook.c parser.c draw_image.c values.c casting.c minimap.c
OBJ = $(SRC:.c=.o)

ifeq ($(UNAME_S),Linux)
MLX_FLAGS = -lft -lmlx -lXext -lX11 -lm
endif
ifeq ($(UNAME_S),Darwin)
MLX_FLAGS = -lm -lglfw -Iinclude -lft -lmlx -lX11 -lXext -lstdc++ -L/usr/X11/lib -framework OpenGL -framework AppKit
endif

all: lib $(NAME)

lib:
	@make -C $(LIBFT)
	@make -C $(MLX)
	@echo "Finished making libraries :D"

$(NAME): $(OBJ)
	@g++ $(CFLAGS) -g -o $@ $^ -L $(LIBFT) -L $(MLX) $(MLX_FLAGS)

clean:
	@make clean -C $(LIBFT)
	@make clean -C $(MLX)
	@rm -f $(OBJ)

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@make clean -C $(MLX)

re:	fclean
	@make all

.PHONY: re, fclean, clean
