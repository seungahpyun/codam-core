NAME = so_long
BONUS_NAME = so_long_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
LDFLAGS = -fsanitize=address

SRC_DIR = src/mandatory
BONUS_DIR = src/bonus
OBJ_DIR = obj
BONUS_OBJ_DIR = obj_bonus
LIB_DIR = lib
INC_DIR = include
MLX_DIR = $(LIB_DIR)/MLX42

MLX = $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS = -L/opt/homebrew/lib -ldl -lglfw -pthread -lm
MLX_INC = -I$(MLX_DIR)/include/MLX42

LIB = $(LIB_DIR)/libft.a

CORE_SRC	 = core/main.c core/utils.c init/game_init.c
GAMEPLAY_SRC = player/player.c
GRAPHICS_SRC = render/render.c render/render_background.c \
			   render/render_player.c render/render_objects.c \
			   render/texture.c
MAP_SRC 	 = map/map_parser.c map/validate_map.c \
			   map/map_memory.c map/map_allocation.c \
			   map/map_path_check.c map/validate_element.c

BONUS_CORE_SRC = core/main_bonus.c core/utils_bonus.c \
				 init/game_init_cleanup_bonus.c init/game_lifecycle_bonus.c
BONUS_GAME_SRC = player/player_bonus.c player/player_movement_bonus.c \
				 enemy/enemy_update_bonus.c enemy/enemy_bonus.c \
				 enemy/enemy_movement_bonus.c enemy/enemy_movement_utils_bonus.c \
				 enemy/enemy_sight_bonus.c
BONUS_GFX_SRC  = render/render_bonus.c render/render_player_init_bonus.c \
				 render/render_objects_bonus.c render/texture_bonus.c \
				 animation/player_animation_bonus.c animation/player_animation_init_bonus.c \
				 render/display_bonus.c render/render_enemies_bonus.c \
				 animation/enemy_animation_init_bonus.c animation/enemy_animation_bonus.c \
				 render/render_player_update_bonus.c render/render_enemies_utils_bonus.c
BONUS_MAP_SRC = map/map_parser_bonus.c map/validate_map_bonus.c \
				 map/map_memory_bonus.c map/map_path_check_bonus.c \
				 map/validate_element_bonus.c

SRCS = $(addprefix $(SRC_DIR)/, $(CORE_SRC) $(GAMEPLAY_SRC) $(GRAPHICS_SRC) $(MAP_SRC))
BONUS_SRCS = $(addprefix $(BONUS_DIR)/, $(BONUS_CORE_SRC) $(BONUS_GAME_SRC) $(BONUS_GFX_SRC) $(BONUS_MAP_SRC))

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)

INC = -I$(INC_DIR) -I$(LIB_DIR)/include $(MLX_INC)

GREEN = \033[0;32m
RESET = \033[0m

all: $(MLX) $(NAME)

bonus: $(MLX) $(BONUS_NAME)

$(MLX):
	@if [ ! -d "$(MLX_DIR)/build" ]; then \
		cmake $(MLX_DIR) -B $(MLX_DIR)/build -DCMAKE_BUILD_TYPE=Release && \
		cmake --build $(MLX_DIR)/build -j4; \
	fi

$(NAME): $(LIB) $(OBJS)
	@echo "$(GREEN)Linking $@...$(RESET)"
	@$(CC) $(OBJS) $(LIB) $(MLX) $(MLX_FLAGS) $(LDFLAGS) -o $@
	@echo "$(GREEN)Build complete: $@$(RESET)"

$(BONUS_NAME): $(LIB) $(BONUS_OBJS)
	@echo "$(GREEN)Linking $@...$(RESET)"
	@$(CC) $(BONUS_OBJS) $(LIB) $(MLX) $(MLX_FLAGS) $(LDFLAGS) -o $@
	@echo "$(GREEN)Build complete: $@$(RESET)"

$(LIB):
	@echo "$(GREEN)Building libft...$(RESET)"
	@make -C $(LIB_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

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
