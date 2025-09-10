NAME = minishell

SRCS_DIR = srcs
OBJS_DIR = objs

READLINE_DIR = readline
EXECUTOR_DIR = executor
LEXER_DIR = lexer
PARSER_DIR = parser
UTILS_DIR = utils

SRCS_MAIN = main.c
SRCS_READLINE = $(READLINE_DIR)/readline.c
SRCS_EXECUTOR = $(EXECUTOR_DIR)/execute.c \
	$(EXECUTOR_DIR)/process.c \
	$(EXECUTOR_DIR)/path.c
SRCS_LEXER = $(LEXER_DIR)/tokenize.c
SRCS_PARSER = $(PARSER_DIR)/parse.c \
	$(PARSER_DIR)/parse_error.c \
	$(PARSER_DIR)/parse_redir.c \
	$(PARSER_DIR)/parse_cmd.c
SRCS_UTILS = $(UTILS_DIR)/free.c \
	$(UTILS_DIR)/exit.c

# debug用
DEBUG_DIR = debug
SRCS_DEBUG = $(DEBUG_DIR)/print_pipeline.c \
	$(DEBUG_DIR)/print_token.c


SRCS = $(SRCS_MAIN) \
$(SRCS_READLINE) \
$(SRCS_LEXER) \
$(SRCS_PARSER) \
$(SRCS_UTILS) \
$(SRCS_DEBUG)

# $(SRCS_EXECUTOR) \

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

INCLUDES = includes

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a
LIBFT_INCLUDES = $(LIBFT_DIR)/$(INCLUDES)


CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
RM_DIR = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -lreadline -o $(NAME)

$(LIBFT_A):
	make -C $(LIBFT_DIR)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)/$(READLINE_DIR)
	mkdir -p $(OBJS_DIR)/$(EXECUTOR_DIR)
	mkdir -p $(OBJS_DIR)/$(LEXER_DIR)
	mkdir -p $(OBJS_DIR)/$(PARSER_DIR)
	mkdir -p $(OBJS_DIR)/$(UTILS_DIR)
	mkdir -p $(OBJS_DIR)/$(DEBUG_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -I$(LIBFT_INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM_DIR) $(OBJS_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
