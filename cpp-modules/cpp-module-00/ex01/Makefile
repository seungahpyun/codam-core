NAME = phonebook

CC = c++
CFLAGS = -Wall -Wextra -Werror
SRC = src/*.cpp
INC = -I./include

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(INC) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
