# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 16:55:23 by jbartosi          #+#    #+#              #
#    Updated: 2023/10/16 16:05:07 by phelebra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d
CFLAGS = -Wall -Wextra -Werror -g #fsanitize=address
LIBFT = Libft
MLX = minilibx
UNAME_S := $(shell uname -s)

SRC = action.c baby_nerve_leech.c cast_door.c cast_enemy.c cast_floor.c \
		cast_init.c cast_item.c cast_obj.c cast_sprite.c cast_stripe.c \
		cast_util.c cast_wall.c collision.c dda.c draw_image.c enemy_dir.c \
		enemy_move.c extract_color.c find_seg.c graphics.c handle_dir.c hit.c \
		hook_handle.c hud.c init_general.c init_sprite.c init_texture.c \
		item_move.c \
		items_a.c items_n.c keyhook.c main.c map_file.c menu.c minimap.c \
		movement.c parser.c process_map.c redraw.c remove_seg.c reset_vals.c \
		sort.c sound.c sprite_move.c tear_larry_isaac.c free_stuff.c
OBJ = $(SRC:.c=.o)

ifeq ($(UNAME_S),Linux)
MLX_FLAGS = -lft -lmlx -lXext -lX11 -lm
CFLAGS += -fPIE
LDFLAGS += -pie
endif
ifeq ($(UNAME_S),Darwin)
MLX_FLAGS = -lm -lglfw -Iinclude -lft -lmlx -L/usr/X11/lib \
			-L/Users/helebrant/.brew/Cellar/libx11/1.8.6/lib \
			-L/Users/helebrant/.brew/Cellar/libxext/1.3.5/lib \
			-lX11 -lXext -lstdc++  -framework OpenGL -framework AppKit
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
