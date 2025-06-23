NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
# SANITIZE = -fsanitize=address

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

SRCS = main_bonus.c \
	   init_bonus.c \
	   init_utils_bonus.c \
	   routine_bonus.c \
	   routine_utils_bonus.c \
	   utils_bonus.c \
	   cleanup_bonus.c \
	   error_bonus.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INC = -I$(INC_DIR)

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(SANITIZE) $(OBJS) -o $(NAME)
	@echo "Philo_bonus compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(SANITIZE) $(INC) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "Object files cleaned!"

fclean: clean
	@$(RM) $(NAME)
	@echo "Everything cleaned!"

re: fclean all

.PHONY: all clean fclean re
