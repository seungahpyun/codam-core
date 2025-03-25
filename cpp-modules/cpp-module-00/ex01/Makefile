NAME = phonebook

CC = c++
CFLAGS = -Wall -Wextra -Werror
SRC = src/*.cpp
INC = -I./include

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(INC) $(SRC) -o $(NAME)
	echo "Phonebook compiled successfully!"

clean:
	rm -f $(NAME)
	echo "Phonebook cleaned successfully!"

fclean: clean

re: fclean all

.PHONY: all clean fclean re
