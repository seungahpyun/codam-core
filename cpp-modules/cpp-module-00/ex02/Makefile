NAME = account
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SRC_DIR = src
OBJ_DIR = obj
INC = -I./include
SRC = Account.cpp \
      tests.cpp
OBJ = $(SRC:/%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[0;32m"Account compiled successfully!"\033[0m"

$(OBJ_DIR)/%.o: /%.cpp | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;33m"Object files cleaned successfully!"\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31m"Account cleaned successfully!"\033[0m"

re: fclean all

.PHONY: all clean fclean re
