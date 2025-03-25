NAME = phonebook
CC = c++
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src
OBJ_DIR = obj
INC = -I./include
SRC = $(SRC_DIR)/main.cpp \
      $(SRC_DIR)/PhoneBook.cpp \
      $(SRC_DIR)/Contact.cpp \
	  $(SRC_DIR)/utils.cpp
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[0;32m"Phonebook compiled successfully!"\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;33m"Object files cleaned successfully!"\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31m"Phonebook cleaned successfully!"\033[0m"

re: fclean all

.PHONY: all clean fclean re
