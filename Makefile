NAME = cub3d
#BONUS = bonus
UNAME_S := $(shell uname -s)
CC = cc
FLAGS = -g -Wall -Werror -Wextra
BOLD	:= \033[1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
RESET	:= \033[0m

OBJ = obj/main.o
MLX = lib/MLX42/libmlx42.a
MLX_DIR = lib/MLX42/
LIBFT = obj/libft/libft.o
LIBFT_DIR = src/libft
NAME_H = include/so_long.h

ifeq ($(UNAME_S),Linux)
MLX_FLAGS = -ldl -lglfw -pthread -lm
endif
ifeq ($(UNAME_S),Darwin)
MLX_FLAGS = -Iinclude -lglfw
endif

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(NAME_H) $(MLX)
	$(CC) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "$(RED)$(BOLD)Runable cub3d created. ✅$(RESET)"

obj/%.o: src/%.c
	$(CC) -g -Wall -Wextra -Werror -c $< -o $@

$(LIBFT): $(LIBFT_DIR)/*.c
	@if  [ ! -d obj/libft ]; then \
		mkdir -p obj/libft; \
	fi
	@make -C $(LIBFT_DIR)
	@echo "$(RED)$(BOLD)Libft compiled. ✅$(RESET)"
	@cp $(LIBFT_DIR)/libft.a $(LIBFT)
	@echo "$(RED)$(BOLD)Library created. ✅$(RESET)"
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)$(BOLD)Library objects cleanup. ✅$(RESET)"

$(MLX): $(MLX_DIR)
	@make -C $(MLX_DIR)
	@echo "$(RED)$(BOLD)MLX42 compiled. ✅$(RESET)"

	@echo "$(RED)$(BOLD)Eudald Approves ✅$(RESET)"


clean:
	@echo "$(RED)Cleaning object files... ✅$(RESET)"
	@$(RM) $(OBJ) $(LIBFT) $(MLX)

fclean: clean
	@echo "$(RED)Cleaning... ✅$(RESET)"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⡛⠛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⢷⣄⣸⡇⠈⠉⠙⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠁⠀⠀⠉⠉⠀⠀⠀⠀⠀⠀⣹⣿⣿⣿⣿⣿⣿⣿⣿⣿"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⢀⣀⣠⣤⣴⠶⠛⠋⠉⢿⣿⣿⣿⣿⣿⣿⣿"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⡷⠾⠟⠛⠛⠋⠉⠀⠀⣀⣀⣤⣴⠾⢿⣿⣿⣿⣿⣿⣿"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣤⣤⣤⣴⠶⠶⠟⠛⠋⠉⠁⠀⠀⠈⢿⣿⣿⣿⣿⣿"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣿⣿⣿⣿"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡙⠻⣿"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣽⣿"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠀⢰⠀⠀⠀⠀⢀⠀⠀⡀⠀⢀⡀⠀⣄⢀⣤⣾⣿⣿"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⠟⠀⢀⣿⢠⡆⠀⢀⣼⣇⣀⣿⣦⣼⣿⣾⣿⣿⣿⣿⣿⣿"
	@echo "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿"
	@$(RM) $(NAME)
	@make fclean -C $(MLX_DIR)

re: clean all

.PHONY: all clean fclean re 