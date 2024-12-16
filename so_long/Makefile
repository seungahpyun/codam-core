NAME		= so_long
BONUS_NAME	= so_long_bonus

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# Directories
SRC_DIR		= src
BONUS_DIR	= src_bonus
OBJ_DIR		= obj
BONUS_OBJ_DIR	= obj_bonus
LIB_DIR		= lib
INC_DIR		= include
MLX_DIR		= $(LIB_DIR)/MLX42

# MLX42 settings
MLX			= $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS	= -ldl -lglfw -pthread -lm
# Linux: -ldl -lglfw -pthread -lm
# MacOS: -framework Cocoa -framework OpenGL -framework IOKit
MLX_INC		= -I$(MLX_DIR)/include/MLX42

# Library
LIB			= $(LIB_DIR)/libft.a

# Source files for each directory
CORE_FILES	= main.c game_lifecycle.c utils.c
GAMEPLAY_FILES	= player.c enemy.c
GRAPHICS_FILES	= animation.c display.c render.c texture.c
MAP_FILES	= map_memory.c parse_map.c path_check.c validate_element.c validate_map.c

# Full source file paths
CORE_SRCS	= $(addprefix $(SRC_DIR)/core/, $(CORE_FILES))
GAMEPLAY_SRCS	= $(addprefix $(SRC_DIR)/gameplay/, $(GAMEPLAY_FILES))
GRAPHICS_SRCS	= $(addprefix $(SRC_DIR)/graphics/, $(GRAPHICS_FILES))
MAP_SRCS	= $(addprefix $(SRC_DIR)/map/, $(MAP_FILES))

# Combine all sources
SRCS		= $(CORE_SRCS) $(GAMEPLAY_SRCS) $(GRAPHICS_SRCS) $(MAP_SRCS)

# Object files
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Bonus sources and objects (if needed)
BONUS_SRCS	= $(SRCS:$(SRC_DIR)/%=$(BONUS_DIR)/%)
BONUS_OBJS	= $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)

# Include paths
INC			= -I$(INC_DIR) -I$(LIB_DIR)/include -I$(MLX_DIR)/include/MLX42

# Colors for output
GREEN		= \033[0;32m
RESET		= \033[0m

all: $(MLX) $(NAME)

bonus: $(MLX) $(BONUS_NAME)

# MLX42 compilation
$(MLX):
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(NAME): $(LIB) $(OBJS)
	@echo "$(GREEN)Linking $@...$(RESET)"
	@$(CC) $(OBJS) $(LIB) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)Build complete: $(NAME)$(RESET)"

$(BONUS_NAME): $(LIB) $(BONUS_OBJS)
	@echo "$(GREEN)Linking $@...$(RESET)"
	@$(CC) $(BONUS_OBJS) $(LIB) $(MLX) $(MLX_FLAGS) -o $(BONUS_NAME)
	@echo "$(GREEN)Build complete: $(BONUS_NAME)$(RESET)"

$(LIB):
	@echo "$(GREEN)Building libft...$(RESET)"
	@make -C $(LIB_DIR)

# Create object files for main program
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Create object files for bonus
$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@echo "$(GREEN)Cleaning object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@make -C $(LIB_DIR) clean
	@rm -rf $(MLX_DIR)/build

fclean: clean
	@echo "$(GREEN)Cleaning executables...$(RESET)"
	@$(RM) $(NAME) $(BONUS_NAME)
	@make -C $(LIB_DIR) fclean

re: fclean all

bonus_re: fclean bonus

.PHONY: all bonus clean fclean re bonus_re
