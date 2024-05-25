CFLAGS= -Wextra -Werror -Wall
SRC= ft_atoi.c ft_memcmp.c ft_strjoin.c ft_bzero.c ft_memcpy.c ft_strlcat.c ft_calloc.c ft_memmove.c ft_strlcpy.c ft_isalnum.c ft_memset.c ft_strlen.c ft_isalpha.c ft_putchar_fd.c ft_strmapi.c\
     ft_isascii.c ft_putendl_fd.c ft_strncmp.c ft_isdigit.c ft_putnbr_fd.c ft_strnstr.c ft_isprint.c ft_putstr_fd.c ft_strrchr.c ft_itoa.c ft_split.c ft_strtrim.c ft_strchr.c\
     ft_substr.c ft_strdup.c ft_tolower.c ft_memchr.c ft_striteri.c ft_toupper.c

SRCBONUS = ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstmap_bonus.c ft_lstadd_front_bonus.c ft_lstiter_bonus.c ft_lstnew_bonus.c ft_lstclear_bonus.c ft_lstlast_bonus.c ft_lstsize_bonus.c
NAME = libft.a
OBJ = $(SRC:.c=.o)
BONUSOBJ = $(SRCBONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar crs $(NAME) $(OBJ)

%.o: %.c libft.h
	@cc -c $(CFLAGS) $<

bonus: $(BONUSOBJ)
	@ar crs $(NAME) $(BONUSOBJ)

re: fclean all

fclean: clean
	@rm -f $(NAME)

clean:
	@rm -f $(OBJ) $(BONUSOBJ)

.PHONY : clean fclean
