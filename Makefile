# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/24 17:09:52 by mait-elk          #+#    #+#              #
#    Updated: 2024/05/25 11:00:04 by mait-elk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc
CFLAGS= -Wall -Werror -Wextra
SRC= utils/utils.c utils/print.c utils/initialization.c \
	utils/maps_check/maps_check.c utils/maps_check/maps_extension.c \
	utils/errors_handling/errors_args.c \
	utils/io_operators/append2d.c
OBJ= $(SRC:.c=.o)
NAME= cub3d

all: $(NAME)

$(NAME): $(OBJ) $(NAME).c include/$(NAME).h
	$(CC) $(CFLAGS) $(NAME).c $(OBJ) -o $(NAME)

%.o: %.c include/$(NAME).h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)

re: fclean all

push : fclean
	@git add .
	@read -p "Enter commit message: " msg_push; \
	git commit -m "$$msg_push";
	@git push origin ${USER}

.PHONY: clean