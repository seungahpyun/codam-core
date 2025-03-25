NAME = megaphone

CC = c++
CFLAGS = -Wall -Wextra -Werror
SRC = src/megaphone.cpp
OBJ_DIR = obj
OBJ = $(SRC:src/%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "\033[0;32m"megaphone compiled successfully!"\033[0m"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;33m"Object files cleaned successfully!"\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31m"megaphone cleaned successfully!"\033[0m"

re: fclean all

.PHONY: all clean fclean re
