NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -pthread
SANITIZE = -fsanitize=thread

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

SRCS = main.c \
	   init.c \
	   init_utils.c \
	   routine.c \
	   monitor.c \
	   actions.c \
	   utils.c \
	   cleanup.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INC = -I$(INC_DIR)

all: $(NAME)

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

.PHONY: all clean fclean re
