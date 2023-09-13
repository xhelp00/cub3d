
NAME		=	libftprintf.a

OBJ_DIR		=	objs/
CFLAGS		=	-Wall -Werror -Wextra 

#Sources
SRC_FILES	=	ft_printf ft_utilities ft_utilities2 len_functions\
				printing_funcs print_hex print_ptr formatify\
				format_applier flagifier_functions


# Colors

NRM_COLOR = \033[0;39m

GREEN = \033[0;92m
YELLOW = \033[0;93m

B_FILES		=	$(addsuffix  _bonus, $(SRC_FILES))

SRC 		=	$(addsuffix .c, $(SRC_FILES))
OBJ 		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

SRC_B 		=	$(addsuffix .c, $(B_FILES))
OBJ_B 		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(B_FILES)))

###

all:		$(NAME)

$(NAME):	$(OBJ)
			@ ar crs $(NAME) $(OBJ)
			@ echo "$(GREEN)ft_printf compiled!$(NRM_COLOR)"

$(OBJ_DIR)%.o:	%.c
			@mkdir -p $(OBJ_DIR)
			@cc $(CFLAGS) -c $< -o $@

clean:
			rm -rf $(OBJ_DIR)

fclean:		clean
			rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re bonus