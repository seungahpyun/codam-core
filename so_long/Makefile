NAME = so_long
BONUS_NAME = so_long_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
LDFLAGS = -fsanitize=address
RM = rm -f

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
# Linux: -ldl -lglfw -pthread -lm
# MacOS: -framework Cocoa -framework OpenGL -framework IOKit
MLX_INC = -I$(MLX_DIR)/include/MLX42

# Library
LIB = $(LIB_DIR)/libft.a

# Source files for mandatory part
CORE_SRC = core/main.c core/game_init.c core/utils.c
GAMEPLAY_SRC = gameplay/player.c
GRAPHICS_SRC = graphics/render.c graphics/texture.c
MAP_SRC = map/map_parser.c map/map_validator.c map/map_memory.c map/path_check.c map/validate_element.c

# Source files for bonus part
BONUS_CORE_SRC = core/main_bonus.c core/game_init_bonus.c core/utils_bonus.c
BONUS_GAMEPLAY_SRC = gameplay/player_bonus.c gameplay/enemy_bonus.c
BONUS_GRAPHICS_SRC = graphics/render_bonus.c graphics/texture_bonus.c \
					graphics/animation_bonus.c graphics/display_bonus.c
BONUS_MAP_SRC = map/map_parser_bonus.c map/map_validator_bonus.c map/map_utils_bonus.c

# Combine all sources
SRCS = $(addprefix $(SRC_DIR)/, $(CORE_SRC) $(GAMEPLAY_SRC) $(GRAPHICS_SRC) $(MAP_SRC))
BONUS_SRCS = $(addprefix $(BONUS_DIR)/, $(BONUS_CORE_SRC) $(BONUS_GAMEPLAY_SRC) \
			$(BONUS_GRAPHICS_SRC) $(BONUS_MAP_SRC))

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)

# Include paths
INC = -I$(INC_DIR) -I$(LIB_DIR)/include $(MLX_INC)

# Colors for output
GREEN = \033[0;32m
RESET = \033[0m

all: $(MLX) $(NAME)

bonus: $(MLX) $(BONUS_NAME)

$(MLX):
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build
	@make -C $(MLX_DIR)/build -j4

$(NAME): $(LIB) $(OBJS)
	@echo "$(GREEN)Linking $@...$(RESET)"
	@$(CC) $(OBJS) $(LIB) $(MLX) $(MLX_FLAGS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Build complete: $(NAME)$(RESET)"

$(BONUS_NAME): $(LIB) $(BONUS_OBJS)
	@echo "$(GREEN)Linking $@...$(RESET)"
	@$(CC) $(BONUS_OBJS) $(LIB) $(MLX) $(MLX_FLAGS) $(LDFLAGS) -o $(BONUS_NAME)
	@echo "$(GREEN)Build complete: $(BONUS_NAME)$(RESET)"

$(LIB):
	@echo "$(GREEN)Building libft...$(RESET)"
	@make -C $(LIB_DIR)

# Create object files for mandatory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Create object files for bonus
$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

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
