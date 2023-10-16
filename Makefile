# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antess <antess@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 16:55:23 by jbartosi          #+#    #+#              #
#    Updated: 2023/10/11 15:48:53 by phelebra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d
CFLAGS = -Wall -Wextra -Werror -g #fsanitize=address
LIBFT = Libft
MLX = minilibx
UNAME_S := $(shell uname -s)

SRC = main.c hook.c parser.c draw_image.c values.c casting.c minimap.c graphics.c movement.c sound.c items.c
OBJ = $(SRC:.c=.o)

ifeq ($(UNAME_S),Linux)
MLX_FLAGS = -lft -lmlx -lXext -lX11 -lm
CFLAGS += -fPIE
LDFLAGS += -pie
endif
ifeq ($(UNAME_S),Darwin)
MLX_FLAGS = -lm -lglfw -Iinclude -lft -lmlx -L/usr/X11/lib -L/Users/helebrant/.brew/Cellar/libx11/1.8.6/lib -L/Users/helebrant/.brew/Cellar/libxext/1.3.5/lib -lX11 -lXext -lstdc++  -framework OpenGL -framework AppKit
CFLAGS +=
LDFLAGS +=
endif

all: lib $(NAME)

lib:
	@make -C $(LIBFT)
	@make -C $(MLX)
	@echo "Finished making libraries :D"

$(NAME): $(OBJ)
	@cc $(CFLAGS) -L $(LIBFT) -L $(MLX) -o $@ $^ $(MLX_FLAGS)

clean:
	@make clean -C $(LIBFT)
	@rm -f $(OBJ)

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re:	fclean
	@make all

.PHONY: re, fclean, clean
