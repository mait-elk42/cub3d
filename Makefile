# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 15:22:43 by mait-elk          #+#    #+#              #
#    Updated: 2024/08/01 15:26:44 by mait-elk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a
MLX = -lmlx -framework OpenGL -framework AppKit

all: $(EXEC)
	@printf "\033[32m🎮 $(EXEC) is Ready\033[0m\n"

mondatory/%.o: %.c mondatory/include/$(NAME).h
	@printf "🔄\033[32m Compiling Script $<\033[0m"
	@if $(CC) $(CFLAGS) -c $< -o $@ 2> /tmp/errcub3d; then \
		printf "\r✅\n"; \
	else \
		printf "\r❌\n\033[31mCannot Compile [$<] Because: \n\033[0m"; \
		cat /tmp/errcub3d; rm -rf /tmp/errcub3d; \
		exit 1; \
	fi

$(EXEC): $(LIBFT) $(OBJ) $(EXEC).c include/$(EXEC).h
	@printf "🔄\033[32m Compiling Executable File...\033[0m"
	@if $(CC) $(CFLAGS) $(EXEC).c $(OBJ) $(LIBFT) $(MLX_ADD) -o $(EXEC) 2> /tmp/errcub3d; then \
		printf "\r✅\n"; \
	else \
		printf "\r❌\n\033[31mCannot Compile [$(NAME).c] Because: \n\033[0m"; \
		cat /tmp/errcub3d; rm -rf /tmp/errcub3d; \
		exit 1; \
	fi

