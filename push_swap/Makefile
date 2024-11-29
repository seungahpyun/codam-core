CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = push_swap
BONUS = checker

SRC_DIR = srcs
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

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
	sort_helpers.c \
	stack_utils.c \
	swap_operations.c \
	validation_handler.c \

BONUS_SRC = checker.c

COMMON_SRC = cost_calculator_a.c \
	cost_calculator_b.c \
	error_handler.c \
	index_utils.c \
	input_handler.c \
	push_operations.c \
	reverse_operations.c \
	rotate_operations.c \
	rotation_applier.c \
	rotation_type_checker.c \
	small_sort_handler.c \
	sort_handler.c \
	sort_helpers.c \
	stack_utils.c \
	swap_operations.c \
	validation_handler.c \

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
BONUS_SRCS = $(addprefix $(SRC_DIR)/checker/, $(BONUS_SRC))
COMMON_SRCS = $(addprefix $(SRC_DIR)/, $(COMMON_SRC))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_DIR)/checker/, $(BONUS_SRC:.c=.o))
COMMON_OBJS = $(addprefix $(OBJ_DIR)/, $(COMMON_SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(COMMON_OBJS) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(COMMON_OBJS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR)/checker/%.o: $(SRC_DIR)/checker/%.c | $(OBJ_DIR)/checker
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/checker:
	mkdir -p $(OBJ_DIR)/checker

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
