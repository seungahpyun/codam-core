# Program names
NAME = so_long
BONUS_NAME = so_long_bonus

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
LDFLAGS = -fsanitize=address

# Directories
SRC_DIR = src/mandatory
BONUS_DIR = src/bonus
OBJ_DIR = obj
BONUS_OBJ_DIR = obj_bonus
LIB_DIR = lib
INC_DIR = include
MLX_DIR = $(LIB_DIR)/MLX42

# MLX42 settings
MLX = $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS = -ldl -lglfw -pthread -lm
MLX_INC = -I$(MLX_DIR)/include/MLX42

# Library
LIB = $(LIB_DIR)/libft.a

# Source files for mandatory part
CORE_SRC	 = core/main.c core/game_init.c core/utils.c
GAMEPLAY_SRC = gameplay/player.c
GRAPHICS_SRC = graphics/render.c graphics/texture.c
MAP_SRC		 = map/map_parser.c map/map_validator.c \
			   map/map_memory.c map/path_check.c map/validate_element.c

# Source files for bonus part
BONUS_CORE_SRC = core/main_bonus.c core/game_lifecycle_bonus.c \
                 core/game_init_cleanup_bonus.c core/utils_bonus.c
BONUS_GAME_SRC = gameplay/player_bonus.c gameplay/player_movement_bonus.c \
                 gameplay/enemy_update_bonus.c gameplay/enemy_bonus.c
BONUS_GFX_SRC =  graphics/render_bonus.c graphics/render_player_bonus.c \
                 graphics/render_objects_bonus.c graphics/texture_bonus.c \
                 graphics/animation_bonus.c graphics/animation_init_bonus.c \
                 graphics/display_bonus.c
BONUS_MAP_SRC =  map/parse_map_bonus.c map/validate_map_bonus.c \
                 map/map_memory_bonus.c map/path_check_bonus.c \
                 map/validate_element_bonus.c

# Combine all sources
SRCS = $(addprefix $(SRC_DIR)/, $(CORE_SRC) $(GAMEPLAY_SRC) $(GRAPHICS_SRC) $(MAP_SRC))
BONUS_SRCS = $(addprefix $(BONUS_DIR)/, $(BONUS_CORE_SRC) $(BONUS_GAME_SRC) $(BONUS_GFX_SRC) $(BONUS_MAP_SRC))

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)

# Include paths
INC = -I$(INC_DIR) -I$(LIB_DIR)/include $(MLX_INC)

# Colors for output
GREEN = \033[0;32m
RESET = \033[0m

# Main targets
all: $(MLX) $(NAME)

bonus: $(MLX) $(BONUS_NAME)

# MLX build
$(MLX):
	@if [ ! -d "$(MLX_DIR)/build" ]; then \
		cmake $(MLX_DIR) -B $(MLX_DIR)/build && \
		cmake --build $(MLX_DIR)/build -j4; \
	fi

# Main program build
$(NAME): $(LIB) $(OBJS)
	@echo "$(GREEN)Linking $@...$(RESET)"
	@$(CC) $(OBJS) $(LIB) $(MLX) $(MLX_FLAGS) $(LDFLAGS) -o $@
	@echo "$(GREEN)Build complete: $@$(RESET)"

# Bonus program build
$(BONUS_NAME): $(LIB) $(BONUS_OBJS)
	@echo "$(GREEN)Linking $@...$(RESET)"
	@$(CC) $(BONUS_OBJS) $(LIB) $(MLX) $(MLX_FLAGS) $(LDFLAGS) -o $@
	@echo "$(GREEN)Build complete: $@$(RESET)"

# Build libft
$(LIB):
	@echo "$(GREEN)Building libft...$(RESET)"
	@make -C $(LIB_DIR)

# Object file creation rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Cleaning rules
clean:
	@echo "$(GREEN)Cleaning object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@make -C $(LIB_DIR) clean

fclean: clean
	@echo "$(GREEN)Cleaning executables...$(RESET)"
	@$(RM) $(NAME) $(BONUS_NAME)
	@make -C $(LIB_DIR) fclean
	@rm -rf $(MLX_DIR)/build

re: fclean all

bonus_re: fclean bonus

.PHONY: all bonus clean fclean re bonus_re
