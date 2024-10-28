CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
INCLUDES = ft_printf.h
LIBFT = libft
LIBFT_LIB = libft.a
SRC = ft_printf.c ft_printf_str.c ft_printf_nbr.c ft_printf_hex.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	@cp $(LIBFT)/$(LIBFT_LIB) $(NAME)
	@ar rcs $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME) $(LIBFT_LIB)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
