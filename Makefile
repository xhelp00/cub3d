# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 16:55:23 by jbartosi          #+#    #+#              #
#    Updated: 2023/09/12 14:28:40 by jbartosi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CFLAGS = -Wall -Wextra -Werror
LIBFT = Libft
MLX = minilibx

SRC = main.c hook.c parser.c draw_image.c values.c casting.c movement.c
OBJ = $(SRC:.c=.o)

all: lib $(NAME)

lib:
	@make -C $(LIBFT)
	@make -C $(MLX)
	@echo "Finished making libraries :D"

$(NAME): $(OBJ)
	@cc $(CFLAGS) -g -L $(LIBFT) -L $(MLX) -o $@ $^ -lft -lmlx -lXext -lX11 -lm

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
