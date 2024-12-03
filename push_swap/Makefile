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
	sort_handler.c \
	sort_helpers.c \
	stack_utils.c \
	swap_operations.c \
	validation_handler.c

BONUS_SRC = checker.c
GNL_SRC = get_next_line.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
BONUS_SRCS = $(addprefix $(SRC_DIR)/checker/, $(BONUS_SRC))
GNL_SRCS = $(addprefix $(SRC_DIR)/checker/get_next_line/, $(GNL_SRC))

OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_DIR)/checker/, $(BONUS_SRC:.c=.o))
GNL_OBJS = $(addprefix $(OBJ_DIR)/checker/get_next_line/, $(GNL_SRC:.c=.o))
SHARED_OBJS = $(filter-out $(OBJ_DIR)/push_swap.o, $(OBJS))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(SHARED_OBJS) $(BONUS_OBJS) $(GNL_OBJS)
	$(CC) $(CFLAGS) $(SHARED_OBJS) $(BONUS_OBJS) $(GNL_OBJS) $(LIBFT) -o $(BONUS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR)/checker/%.o: $(SRC_DIR)/checker/%.c | $(OBJ_DIR)/checker
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(SRC_DIR)/checker/get_next_line -c $< -o $@

$(OBJ_DIR)/checker/get_next_line/%.o: $(SRC_DIR)/checker/get_next_line/%.c | $(OBJ_DIR)/checker/get_next_line
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(SRC_DIR)/checker/get_next_line -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/checker:
	mkdir -p $(OBJ_DIR)/checker

$(OBJ_DIR)/checker/get_next_line:
	mkdir -p $(OBJ_DIR)/checker/get_next_line

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
