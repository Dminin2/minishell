NAME = minishell

SRCS_DIR = srcs
OBJS_DIR = objs

READLINE_DIR = readline
EXECUTOR_DIR = executor
LEXER_DIR = lexer
PARSER_DIR = parser
EXPANDER_DIR = expander
REDIRECTION_DIR = redirection
ENV_DIR = env
UTILS_DIR = utils
BUILTINS_DIR = builtins

SRCS_MAIN = main.c
SRCS_READLINE = $(READLINE_DIR)/readline.c
SRCS_EXECUTOR = $(EXECUTOR_DIR)/execute.c \
	$(EXECUTOR_DIR)/process.c \
	$(EXECUTOR_DIR)/path.c \
	$(EXECUTOR_DIR)/pipe.c \
	$(EXECUTOR_DIR)/run_in_child.c \
	$(EXECUTOR_DIR)/run_in_parent.c \
	$(EXECUTOR_DIR)/execute_builtin.c \
	$(EXECUTOR_DIR)/stdio_fd.c \
	$(EXECUTOR_DIR)/free_pipes.c
SRCS_LEXER = $(LEXER_DIR)/tokenize.c \
	$(LEXER_DIR)/free_token.c
SRCS_PARSER = $(PARSER_DIR)/parse.c \
	$(PARSER_DIR)/parse_error.c \
	$(PARSER_DIR)/parse_redir.c \
	$(PARSER_DIR)/parse_cmd.c \
	$(PARSER_DIR)/free_pipeline_ir.c \
	$(PARSER_DIR)/free_redir.c
SRCS_EXPANDER = $(EXPANDER_DIR)/expand.c \
	$(EXPANDER_DIR)/build_cmd.c \
	$(EXPANDER_DIR)/remove_quote.c \
	$(EXPANDER_DIR)/expand_param.c \
	$(EXPANDER_DIR)/build_args.c \
	$(EXPANDER_DIR)/expand_utils.c \
	$(EXPANDER_DIR)/build_redir.c \
	$(EXPANDER_DIR)/free_pipeline.c \
	$(EXPANDER_DIR)/free_pipeline_ir_in_expander.c
SRCS_REDIRECTION = $(REDIRECTION_DIR)/redirect.c \
	$(REDIRECTION_DIR)/heredoc.c
SRCS_ENV = $(ENV_DIR)/env_init.c \
	$(ENV_DIR)/env_utils.c \
	$(ENV_DIR)/search_env.c \
	$(ENV_DIR)/free_env.c \
	$(ENV_DIR)/pack_env.c \
	$(ENV_DIR)/env_operation.c
SRCS_UTILS = $(UTILS_DIR)/free.c \
	$(UTILS_DIR)/exit.c \
	$(UTILS_DIR)/close.c \
	$(UTILS_DIR)/list.c \
	$(UTILS_DIR)/string.c
SRCS_BUILTINS = $(BUILTINS_DIR)/builtin_pwd.c \
	$(BUILTINS_DIR)/builtin_echo.c \
	$(BUILTINS_DIR)/builtin_cd.c \
	$(BUILTINS_DIR)/builtin_exit.c \
	$(BUILTINS_DIR)/builtin_exit_utils.c \
	$(BUILTINS_DIR)/builtin_utils.c \
	$(BUILTINS_DIR)/builtin_env.c \
	$(BUILTINS_DIR)/builtin_export.c \
	$(BUILTINS_DIR)/builtin_export_args.c \
	$(BUILTINS_DIR)/builtin_export_no_args.c \
	$(BUILTINS_DIR)/builtin_export_utils.c \
	$(BUILTINS_DIR)/builtin_unset.c \


# debug用
DEBUG_DIR = debug
SRCS_DEBUG = $(DEBUG_DIR)/print_pipeline_ir.c \
	$(DEBUG_DIR)/print_token.c \
	$(DEBUG_DIR)/print_pipeline.c \
	$(DEBUG_DIR)/print_redir_lst.c \
	$(DEBUG_DIR)/print_env_lst.c \
	$(DEBUG_DIR)/print_status.c \
	$(DEBUG_DIR)/print_line.c


SRCS = $(SRCS_MAIN) \
$(SRCS_READLINE) \
$(SRCS_LEXER) \
$(SRCS_PARSER) \
$(SRCS_EXPANDER) \
$(SRCS_REDIRECTION) \
$(SRCS_EXECUTOR) \
$(SRCS_ENV) \
$(SRCS_UTILS) \
$(SRCS_DEBUG) \
$(SRCS_BUILTINS)


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
	mkdir -p $(OBJS_DIR)/$(EXPANDER_DIR)
	mkdir -p $(OBJS_DIR)/$(REDIRECTION_DIR)
	mkdir -p $(OBJS_DIR)/$(ENV_DIR)
	mkdir -p $(OBJS_DIR)/$(UTILS_DIR)
	mkdir -p $(OBJS_DIR)/$(DEBUG_DIR)
	mkdir -p $(OBJS_DIR)/$(BUILTINS_DIR)

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

debug:
	$(MAKE) all CFLAGS="$(CFLAGS) -DDEBUG"

.PHONY: all clean fclean re debug
