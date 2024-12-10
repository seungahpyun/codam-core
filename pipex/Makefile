NAME = pipex
BONUS = pipex_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror # -fsanitize=address -g

SRCS_DIR = srcs/
OBJS_DIR = objs/
MAND_DIR = $(SRCS_DIR)mandatory/
BONUS_DIR = $(SRCS_DIR)bonus/
INCLUDES = -I includes/ -I libft/get_next_line -I libft/libft
LIBFT_DIR = libft/libft/
GNL_DIR = libft/get_next_line/

MAND_SRCS = main.c \
	check_args.c \
	execute.c \
	init.c \
	utils.c \
	cmd_parser.c \
	cmd_utils.c \
	parse_utils.c

MAND_SRCS_PATH = $(addprefix $(MAND_DIR), $(MAND_SRCS))
MAND_OBJS = $(addprefix $(OBJS_DIR), $(MAND_SRCS:.c=.o))

BONUS_SRCS = main_bonus.c \
	execute_bonus.c \
	heredoc_bonus.c \
	init_bonus.c \
	pipes_bonus.c \
	utils_bonus.c \
	cmd_parser_bonus.c \
	cmd_utils_bonus.c \
	parse_utils_bonus.c

BONUS_SRCS_PATH = $(addprefix $(BONUS_DIR), $(BONUS_SRCS))
BONUS_OBJS = $(addprefix $(OBJS_DIR), $(BONUS_SRCS:.c=.o))

GNL_SRCS = get_next_line.c
GNL_SRCS_PATH = $(addprefix $(GNL_DIR), $(GNL_SRCS))
GNL_OBJS = $(addprefix $(OBJS_DIR), $(GNL_SRCS:.c=.o))

LIBFT = $(LIBFT_DIR)libft.a

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(LIBFT) $(MAND_OBJS)
	$(CC) $(CFLAGS) $(MAND_OBJS) $(LIBFT) -o $(NAME)

bonus: $(OBJS_DIR) $(BONUS)

$(BONUS): $(LIBFT) $(BONUS_OBJS) $(GNL_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(GNL_OBJS) $(LIBFT) -o $(BONUS)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJS_DIR)%.o: $(MAND_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)%.o: $(BONUS_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)%.o: $(GNL_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f $(BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
