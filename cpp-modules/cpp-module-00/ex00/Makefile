NAME = megaphone

CC = c++
CFLAGS = -Wall -Wextra -Werror
SRC = src/megaphone.cpp

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
