# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 15:22:43 by mait-elk          #+#    #+#              #
#    Updated: 2024/08/01 17:57:12 by aabouqas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS= -Wall -Werror -Wextra -I include -I libft #-fsanitize=address -g
EXEC=cub3d
EXEC_BONUS=cub3d_bonus

SRC = src/utils.c src/print.c src/initialization.c \
	src/map_check/map_parse.c src/map_check/check_map.c src/map_check/check_colors.c \
	src/io_operators/append2d.c src/strings.c \
	src/errors_handling/errors_args.c src/errors_handling/put_error.c \
	src/io_operators/safe_str1.c src/io_operators/safe_str2.c \
	src/images/t_image_instractions.c \
	src/math/angle.c \
	src/game/init_player.c src/game/run_game.c src/game/events_game.c src/game/utils_game.c \
	src/walls_paint/texture_instractions.c \
	src/raycast/send_ray.c src/raycast/ray_utils_1.c src/raycast/ray_utils_2.c

SRC_BONUS = src_bonus/utils.c src_bonus/print.c src_bonus/initialization.c src_bonus/door.c \
	src_bonus/map_check/map_parse.c src_bonus/map_check/check_map.c src_bonus/map_check/check_colors.c \
	src_bonus/io_operators/append2d.c src_bonus/strings.c \
	src_bonus/errors_handling/errors_args.c src_bonus/errors_handling/put_error.c \
	src_bonus/io_operators/safe_str1.c src_bonus/io_operators/safe_str2.c \
	src_bonus/images/t_image_instractions.c \
	src_bonus/math/angle.c src_bonus/math/utils.c \
	src_bonus/game/init_player.c src_bonus/game/run_game.c src_bonus/game/events_game.c src_bonus/game/utils_game.c src_bonus/game/player_env.c \
	src_bonus/map_utils/draw_map.c \
	src_bonus/walls_paint/texture_instractions.c \
	src_bonus/menu/menu.c src_bonus/menu/menu_events.c src_bonus/menu/menu_utils.c \
	src_bonus/raycast/send_ray.c src_bonus/raycast/ray_utils_1.c src_bonus/raycast/ray_utils_2.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
LIBFT = libft/libft.a
MLX = -Llib -lmlx -framework OpenGL -framework AppKit

all: $(EXEC)
	@printf "\033[32m🎮 $(EXEC) is Ready\033[0m\n"

bonus: $(EXEC_BONUS)
	@printf "\033[32m🎮 $(EXEC_BONUS) is Ready\033[0m\n"

src/%.o: src/%.c include/$(EXEC).h
	@printf "🔄\033[32m Compiling Script $<\033[0m"
	@if $(CC) $(CFLAGS) -c $< -o $@ 2> /tmp/errcub3d; then \
		printf "\r✅\n"; \
	else \
		printf "\r❌\n\033[31m Cannot Compile [$<] Because: \n\033[0m"; \
		cat /tmp/errcub3d; rm -rf /tmp/errcub3d; \
		exit 1; \
	fi

src_bonus/%.o: src_bonus/%.c include/$(EXEC_BONUS).h
	@printf "🔄\033[32m ⭐ Compiling Bonus Script $< \033[0m"
	@if $(CC) $(CFLAGS) -c $< -o $@ 2> /tmp/errcub3d; then \
		printf "\r✅\n"; \
	else \
		printf "\r❌\n\033[31m Cannot Compile [$<] Because: \n\033[0m"; \
		cat /tmp/errcub3d; rm -rf /tmp/errcub3d; \
		exit 1; \
	fi

$(EXEC): $(LIBFT) $(OBJ) $(EXEC).c include/$(EXEC).h
	@printf "🔄\033[32m Compiling Executable File...\033[0m"
	@if $(CC) $(CFLAGS) $(EXEC).c $(OBJ) $(LIBFT) $(MLX) -o $(EXEC) 2> /tmp/errcub3d; then \
		printf "\r✅\n"; \
	else \
		printf "\r❌\n\033[31mCannot Compile [$(NAME).c] Because: \n\033[0m"; \
		cat /tmp/errcub3d; rm -rf /tmp/errcub3d; \
		exit 1; \
	fi

$(EXEC_BONUS): $(LIBFT) $(OBJ_BONUS) $(EXEC_BONUS).c include/$(EXEC_BONUS).h
	@printf "🔄\033[32m Compiling Executable File...\033[0m"
	@if $(CC) $(CFLAGS) $(EXEC_BONUS).c $(OBJ_BONUS) $(LIBFT) $(MLX) -o $(EXEC_BONUS) 2> /tmp/errcub3d; then \
		printf "\r✅\n"; \
	else \
		printf "\r❌\n\033[31mCannot Compile [$(NAME).c] Because: \n\033[0m"; \
		cat /tmp/errcub3d; rm -rf /tmp/errcub3d; \
		exit 1; \
	fi

$(LIBFT):
	@printf "🔄\033[32m Compiling Libft...\033[0m"
	@if make -C libft 2> /tmp/errcub3d; then \
		printf "\r✅\n"; \
	else \
		printf "\r❌\n\033[31mCannot Compile [$(LIBFT)] Because: \n\033[0m"; \
		cat /tmp/errcub3d; rm -rf /tmp/errcub3d; \
		exit 1; \
	fi

clean:
	@printf "🔄\033[32m Cleaning Objects...\033[0m"
	@rm -rf $(OBJ) $(OBJ_BONUS)
	@make clean -C libft
	@printf "\r✅\n";

fclean: clean
	@printf "🔄\033[32m Removing Exec file And Library...\033[0m"
	@rm -rf $(EXEC) $(EXEC_BONUS)
	@make fclean -C libft
	@printf "\r✅\n";

.PHONY: clean

re: fclean all
