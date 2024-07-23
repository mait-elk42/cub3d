# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/24 17:09:52 by mait-elk          #+#    #+#              #
#    Updated: 2024/07/23 10:47:38 by aabouqas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc
CFLAGS= -Wall -Werror -Wextra -I include -I libft #-fsanitize=address -g
SRC= src/utils.c src/print.c src/initialization.c \
	src/map_check/map_parse.c src/map_check/check_map.c src/map_check/check_colors.c \
	src/io_operators/append2d.c src/strings.c \
	src/errors_handling/errors_args.c src/errors_handling/put_error.c \
	src/io_operators/safe_str1.c src/io_operators/safe_str2.c \
	src/images/t_image_instractions.c \
	src/math/angle.c \
	src/game/init_player.c src/game/run_game.c src/game/events_game.c src/game/utils_game.c \
	src/walls_paint/texture_instractions.c \
	src/raycast/send_ray.c src/raycast/send_horizontal.c src/raycast/send_vertical.c src/raycast/utils.c 

OBJ= $(SRC:.c=.o)
NAME= cub3d
LIBFT = libft/libft.a
MLX_ADD= -lmlx -framework OpenGL -framework AppKit

all: $(NAME)
	@printf "\033[32m🎮 $(NAME) is Ready\033[0m\n"

$(NAME): $(LIBFT) $(OBJ) $(NAME).c include/$(NAME).h
	@printf "🔄\033[32m Compiling Executable File...\033[0m"
	@if $(CC) $(CFLAGS) $(NAME).c $(OBJ) $(LIBFT) $(MLX_ADD) -o $(NAME) 2> /tmp/errcub3d; then \
		printf "\r✅\n"; \
	else \
		printf "\r❌\n\033[31mCannot Compile [$(NAME).c] Because: \n\033[0m"; \
		cat /tmp/errcub3d; rm -rf /tmp/errcub3d; \
		exit 1; \
	fi

%.o: %.c include/$(NAME).h
	@printf "🔄\033[32m Compiling Script $<\033[0m"
	@if $(CC) $(CFLAGS) -c $< -o $@ 2> /tmp/errcub3d; then \
		printf "\r✅\n"; \
	else \
		printf "\r❌\n\033[31mCannot Compile [$<] Because: \n\033[0m"; \
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
	@rm -rf $(OBJ)
	@make clean -C libft
	@printf "\r✅\n";

fclean: clean
	@printf "🔄\033[32m Removing Exec file And Library...\033[0m"
	@rm -rf $(NAME)
	@make fclean -C libft
	@printf "\r✅\n";

re: fclean all

push : fclean
	@git add .
	@read -p "Enter commit message: " msg_push; \
	git commit -m "$$msg_push";
	@git push origin ${USER}

.PHONY: clean
