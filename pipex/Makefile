NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_DIR = srcs/
SRCS = main.c \
	check_args.c \
	pipe_handler.c \
	utils.c
SRCS_PATH = $(addprefix $(SRCS_DIR), $(SRCS))

OBJS = $(SRCS_PATH:.c=.o)

INCLUDES = -I includes/

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
