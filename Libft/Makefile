# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nroth <nroth@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/10 10:00:32 by nroth             #+#    #+#              #
#    Updated: 2023/03/02 16:35:39 by nroth            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



SRCS =	ft_arrappend.c ft_arrfree.c ft_lstadd_front.c ft_putchar_fd.c ft_strmapi.c \
		ft_arrcpy.c ft_lstclear.c ft_putendl_fd.c ft_strncmp.c \
		ft_arrlen.c ft_lstdelone.c ft_putnbr_fd.c ft_strnstr.c \
		ft_atoi.c ft_lstiter.c ft_putstr_fd.c ft_strrchr.c \
		ft_bzero.c ft_lstlast.c ft_split.c ft_strtrim.c \
		ft_calloc.c ft_lstmap.c ft_strappend.c ft_substr.c \
		ft_isalnum.c ft_lstnew.c ft_strchr.c ft_tolower.c \
		ft_isalpha.c ft_lstsize.c ft_strdup.c ft_toupper.c \
		ft_isascii.c ft_memchr.c ft_striteri.c get_next_line.c \
		ft_isdigit.c ft_memcmp.c ft_strjoin.c \
		ft_isprint.c ft_memcpy.c ft_strlcat.c \
		ft_itoa.c ft_memmove.c ft_strlcpy.c \
		ft_lstadd_back.c ft_memset.c ft_strlen.c ft_arrappend_void.c\

FT_PRINTF_FOL = ft_printf/
FT_PRINTF = ${addprefix ${FT_PRINTF_FOL}, libftprintf.a}

NAME = libft.a

HEADER = ${NAME:.a=.h}

OBJS_DIR = objs/
OBJS = ${SRCS:.c=.o}
OBJS_PREFIXED = ${addprefix ${OBJS_DIR}, ${OBJS}}

CC_FLAGS = -Wall -Wextra -Werror
CC = cc

# Colors

NRM_COLOR = \033[0;39m

GREEN = \033[0;92m
YELLOW = \033[0;93m



all: ${NAME}

${OBJS_DIR}%.o : %.c
	@ mkdir -p ${OBJS_DIR}
	@ ${CC} ${CC_FLAGS} -c $< -o $@

${NAME}:	${OBJS_PREFIXED} ${FT_PRINTF}
	@ ar -crs ${NAME} ${OBJS_PREFIXED}
	@ ar -rs ${NAME} ${addprefix ${addprefix  ${FT_PRINTF_FOL}, ${OBJS_DIR}}, *}
	@ echo "${GREEN}${NAME} created!${NRM_COLOR}" 

${FT_PRINTF}:
	@ make -C ${FT_PRINTF_FOL} --no-print-directory

clean:
	rm -rf ${FT_PRINTF_FOL}${OBJS_DIR}
	rm -rf ${OBJS_DIR}

fclean: clean
	rm -rf ${FT_PRINTF}
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
