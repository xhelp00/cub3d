# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbartosi <jbartosi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/19 21:33:05 by jbartosi          #+#    #+#              #
#    Updated: 2021/05/19 21:39:09 by jbartosi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cute_png.o
SRC		= cute_png.c
CFLAGS	= -Wall -Wextra -Ofast -march=native
HEADER	= cute_png.h

ifeq ($(OS),Windows_NT)
	CFLAGS += -D _WIN32
endif

all: $(NAME)
$(NAME): $(HEADER)
clean:
	@$(RM) $(NAME)
fclean: clean
re: fclean all
.PHONY: all clean fclean re
