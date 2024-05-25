# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/24 17:09:52 by mait-elk          #+#    #+#              #
#    Updated: 2024/05/25 10:41:51 by aabouqas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc
CFLAGS= -Wall -Werror -Wextra
SRC= utils/print.c \
	utils/errors_handling/errors_args.c
OBJ= $(SRC:.c=.o)
NAME= cub3d
LIBFT = libft/libft.a

all: $(NAME)
	@echo "$(NAME) is Ready Enjoy"

$(NAME): $(LIBFT) $(OBJ) $(NAME).c include/$(NAME).h
	@$(CC) $(CFLAGS) $(NAME).c $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c include/$(NAME).h
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "Please wait..."
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