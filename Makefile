# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Project Name
NAME = push_swap
BONUS = checker

# Directories
SRC_DIR = srcs
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft

# Library
LIBFT = $(LIBFT_DIR)/libft.a

# Source and Object Files
SRC = cost_calculator_a.c \
	cost_calculator_b.c \
	error_handler.c \
	index_utils.c \
	input_handler.c \
	push_operations.c \
	push_swap.c \
	reverse_operations.c \
	rotate_operations.c \
	rotation_applier.c \
	rotation_type_checker.c \
	small_sort_handler.c \
	sort_handler.c \
	stack_utils.c \
	swap_operations.c \
	validation_handler.c \

BONUS_SRC = checker.c \
	checker_utils.c \

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
BONUS_SRCS = $(addprefix $(SRC_DIR)/checker/, $(BONUS_SRC))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_DIR)/, $(BONUS_SRC:.c=.o))

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(OBJS) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
