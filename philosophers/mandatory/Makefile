NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -pthread
SANITIZE = -fsanitize=thread

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Source files
SRCS = main.c \
	   init.c \
	   parsing.c \
	   routine.c \
	   monitor.c \
	   actions.c \
	   utils.c \
	   cleanup.c

# Add source directory prefix
SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Include flags
INC = -I$(INC_DIR)

# Mandatory part
all: $(NAME)

# Create object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(SANITIZE) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(SANITIZE) $(INC) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
