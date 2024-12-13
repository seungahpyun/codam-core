NAME		= so_long
BONUS_NAME	= so_long_bonus

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
MLX_FLAGS	= -lmlx -framework OpenGL -framework AppKit
RM			= rm -f

# Directories
SRC_DIR		= src
BONUS_DIR	= src_bonus
OBJ_DIR		= obj
BONUS_OBJ_DIR	= obj_bonus
LIB_DIR		= lib
INC_DIR		= include

# Library
LIB			= $(LIB_DIR)/libft.a

# Source files for each directory
CORE_FILES	= main.c game_lifecycle.c utils.c
GAMEPLAY_FILES	= player.c enemy.c
GRAPHICS_FILES	= animation.c display.c render.c texture.c
MAP_FILES	= map_memory.c parse_map.c path_check.c validate_elements.c validate_map.c

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
INC			= -I$(INC_DIR) -I$(LIB_DIR)/include

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(OBJS) $(LIB) $(MLX_FLAGS) -o $(NAME)

$(BONUS_NAME): $(LIB) $(BONUS_OBJS)
	$(CC) $(BONUS_OBJS) $(LIB) $(MLX_FLAGS) -o $(BONUS_NAME)

$(LIB):
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
	$(RM) -r $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@make -C $(LIB_DIR) clean

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)
	@make -C $(LIB_DIR) fclean

re: fclean all

bonus_re: fclean bonus

.PHONY: all bonus clean fclean re bonus_re
