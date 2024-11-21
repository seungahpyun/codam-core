CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = push_swap
INCLUDES = 
LIBFT = libft
LIBFT_LIB = libft.a
SRC =
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
