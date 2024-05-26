# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/24 17:09:52 by mait-elk          #+#    #+#              #
#    Updated: 2024/05/26 09:40:12 by mait-elk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc
CFLAGS= -Wall -Werror -Wextra # -fsanitize=address -g
SRC= utils/utils.c utils/print.c utils/initialization.c \
	utils/maps_check/maps_check.c utils/maps_check/maps_extension.c \
	utils/errors_handling/errors_args.c utils/errors_handling/put_error.c \
	utils/io_operators/str.c \
	utils/io_operators/append2d.c
OBJ= $(SRC:.c=.o)
NAME= cub3d
LIBFT = libft/libft.a

all: $(NAME)
	@echo "\033[32m$(NAME) is Ready\033[0m"

$(NAME): $(LIBFT) $(OBJ) $(NAME).c include/$(NAME).h
	@echo "\033[32mCompiling Executable File...\033[0m"
	@$(CC) $(CFLAGS) $(NAME).c $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c include/$(NAME).h
	@echo "🔄\033[32mCompiling Script $<\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "🔄\033[32mCompiling Libft...\033[0m"
	@make -C libft

clean:
	@rm -rf $(OBJ)
	@make clean -C libft

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft

re: fclean all

push : fclean
	@git add .
	@read -p "Enter commit message: " msg_push; \
	git commit -m "$$msg_push";
	@git push origin ${USER}

.PHONY: clean