# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 16:09:47 by aomatsud          #+#    #+#              #
#    Updated: 2025/10/31 15:13:06 by hmaruyam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

LIBFT_DIR = libft
LIBFT_SRCS = ft_isalpha.c	\
ft_isdigit.c \
ft_isalnum.c \
ft_isascii.c \
ft_isprint.c \
ft_strlen.c \
ft_memset.c \
ft_bzero.c \
ft_memcpy.c \
ft_memmove.c \
ft_strlcpy.c \
ft_strlcat.c \
ft_toupper.c \
ft_tolower.c \
ft_strchr.c \
ft_strrchr.c \
ft_strncmp.c \
ft_memchr.c \
ft_memcmp.c \
ft_strnstr.c \
ft_atoi.c \
ft_calloc.c \
ft_strdup.c \
ft_substr.c \
ft_strjoin.c \
ft_strtrim.c \
ft_split.c \
ft_itoa.c \
ft_strmapi.c \
ft_striteri.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_lstnew_bonus.c \
ft_lstadd_front_bonus.c \
ft_lstsize_bonus.c \
ft_lstlast_bonus.c \
ft_lstadd_back_bonus.c \
ft_lstdelone_bonus.c \
ft_lstclear_bonus.c \
ft_lstiter_bonus.c \
ft_lstmap_bonus.c
LIBFT_OBJS = $(addprefix $(OBJS_DIR)/$(LIBFT_DIR)/, $(LIBFT_SRCS:.c=.o))


FT_PRINTF_DIR = ft_printf
FT_PRINTF_SRCS = ft_printf.c \
print_char_string_percent.c \
print_decimal.c \
print_hexadecimal.c \
put_fd_utils.c
FT_PRINTF_OBJS = $(addprefix $(OBJS_DIR)/$(FT_PRINTF_DIR)/, $(FT_PRINTF_SRCS:.c=.o))

FT_DPRINTF_DIR = ft_dprintf
FT_DPRINTF_SRCS = ft_dprintf.c \
dprint_char_string_percent.c \
dprint_decimal.c \
dprint_hexadecimal.c \
dput_fd_utils.c
FT_DPRINTF_OBJS = $(addprefix $(OBJS_DIR)/$(FT_DPRINTF_DIR)/, $(FT_DPRINTF_SRCS:.c=.o))

FT_DPRINTF_BUF_DIR = ft_dprintf_buf
FT_DPRINTF_BUF_SRCS = ft_dprintf_buf.c \
dprintf_buffer.c \
dprint_char_string_percent_buf.c \
dprint_decimal_buf.c \
dprint_unsigned_buf.c \
dprint_hexadecimal_buf.c
FT_DPRINTF_BUF_OBJS = $(addprefix $(OBJS_DIR)/$(FT_DPRINTF_BUF_DIR)/, $(FT_DPRINTF_BUF_SRCS:.c=.o))

GNL_DIR = get_next_line
GNL_SRCS = get_next_line.c \
get_next_line_utils.c
GNL_OBJS = $(addprefix $(OBJS_DIR)/$(GNL_DIR)/, $(GNL_SRCS:.c=.o))

SRCS_DIR = srcs
SRCS = $(LIBFT_SRCS) $(FT_PRINTF_SRCS) $(FT_DPRINTF_SRCS) $(FT_DPRINTF_BUF_SRCS) $(GNL_SRCS)

OBJS_DIR = objs
OBJS = $(LIBFT_OBJS) $(FT_PRINTF_OBJS) $(FT_DPRINTF_OBJS) $(FT_DPRINTF_BUF_OBJS) $(GNL_OBJS)

INCLUDES = includes

CC = cc
CFLAGS = -Wall -Wextra -Werror

AR = ar rcs
RM = rm -rf

all:$(NAME)

$(NAME):$(OBJS)
	@$(AR) $(NAME) $(OBJS)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/$(LIBFT_DIR)
	@mkdir -p $(OBJS_DIR)/$(FT_PRINTF_DIR)
	@mkdir -p $(OBJS_DIR)/$(FT_DPRINTF_DIR)
	@mkdir -p $(OBJS_DIR)/$(FT_DPRINTF_BUF_DIR)
	@mkdir -p $(OBJS_DIR)/$(GNL_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJS_DIR)

fclean:clean
	@$(RM) $(NAME)

re:fclean all

.PHONY: all clean fclean re bonus
