NAME = minishell

SRCS_DIR = srcs
OBJS_DIR = objs

READLINE_DIR = readline

SRCS_MAIN = main.c
SRCS_READLINE = $(READLINE_DIR)/readline.c


SRCS = $(SRCS_MAIN) \
$(SRCS_READLINE)

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

INCLUDES = includes

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
RM_DIR = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)/$(READLINE_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM_DIR) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
